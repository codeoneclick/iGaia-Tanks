//
//  BaseWebRequestOperation.m
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import "BaseWebRequestOperation.h"
#import "JSONKit.h"

@interface BaseWebRequestOperation()

@property (nonatomic, assign) BOOL requestCompleted;
@property (nonatomic, assign) BOOL requestFailed;
@property (nonatomic, retain) NSURLConnection* connection;

- (id <NSObject>)parseData:(NSData*)data;
- (NSError*)processData:(id)data;

@end

@implementation BaseWebRequestOperation

@synthesize requestCompleted;
@synthesize requestFailed;

@synthesize url;
@synthesize method;
@synthesize params;
@synthesize error;

@synthesize data;
@synthesize connection;


- (id)init
{
	if ((self = [super init]))
	{
		self.requestCompleted = NO;
		self.requestFailed    = NO;
        
        method = k_METHOD_POST;
	}
	return self;
}


- (void)dealloc
{
	self.url   = nil;
	self.error = nil;
    
	self.data = nil;
    self.connection = nil;
}

- (void)run
{
    id request = nil;

    if([self.method isEqualToString:k_METHOD_POST])
    {
        request = [[NSMutableURLRequest alloc] initWithURL: self.url];
        [request setHTTPBody: self.params];
        [request setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
        [request setHTTPMethod:self.method];
    }
    else if([self.method isEqualToString:k_METHOD_GET])
    {
        request = [[NSURLRequest alloc]  initWithURL:self.url cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:60]; 
    }
    
    if (request)
    {
        self.data = [[NSMutableData alloc] init];
        self.connection = [NSURLConnection connectionWithRequest:request delegate:self];
        [self.connection scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        [self.connection start];
    }
    
    do 
    {        
		[[NSRunLoop currentRunLoop] runMode: NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]]; 
		if ([self isCancelled])
		{
            if (connection != nil)
            {
                [connection cancel];
                self.connection = nil;
            }
            self.data = nil;
			break;
		}
	} 
	while(!requestFailed && !requestCompleted);
    
    if ([self isCancelled])
    {
        return;
    }
    
    if (self.requestFailed)
    {
        [self notifyOnFailure:self.error];
    }
    else if (self.requestCompleted)
	{
		NSData* rawData = [NSData dataWithData:self.data];
		id <NSObject> parsedData = [self parseData: rawData];
		
		if (!parsedData && rawData)
		{
			self.error = [NSError errorWithDomain:@"Error ! Data parsing failure." code:1 userInfo:nil];
			[self notifyOnFailure:self.error];
		}
		else
		{
			id processError = [self processData: parsedData];
			if (!processError)
            {
				[self notifyOnSuccess:self.data];
            }
			else
			{                
                self.error = processError;
				[self notifyOnFailure:self.error];
			}
		}
	}
}

- (id <NSObject>)parseData:(NSData*)_data
{
    id parsedData = [_data objectFromJSONData];
    NSLog(@"Response data for url: %@ \n %@ \n", self.url, parsedData);
    return parsedData;
}


- (NSError*)processData:(id)data
{
	return [NSError errorWithDomain:@"GeneralError" code:0 userInfo:nil];
}

- (void)connection:(NSURLConnection*)connection didReceiveResponse:(NSURLResponse*)response 
{
    [self.data setLength:0];
    NSHTTPURLResponse* httpResponse = (NSHTTPURLResponse*)response;
    NSInteger statusCode = [httpResponse statusCode];
    NSLog(@"Response status code for url: %@ = %d", self.url, statusCode);
    
    if (statusCode >= 400)
    {
        self.requestFailed    = YES;
        self.requestCompleted = NO;
        self.error            = [NSError errorWithDomain:[NSString stringWithFormat:@"Error ! Response status code : %i.", statusCode] code:statusCode userInfo:nil];
        self.connection       = nil;
    }
}

-(void)connection:(NSURLConnection*)connection didReceiveData:(NSData*)_data
{
    [self.data appendData:_data];
}


-(void)connectionDidFinishLoading:(NSURLConnection*)_connection
{
    BOOL failed = (self.data == nil || [self.data length] == 0);
    
    self.requestFailed = failed;
    self.requestCompleted = !failed;
    self.connection = nil;
}

- (void)connection:(NSURLConnection*)connection didFailWithError:(NSError*)aerror 
{
    NSLog(@"Request failed with error: %@ = %@", self.url, aerror);
    self.requestFailed = YES;
    self.connection = nil;
}


@end
