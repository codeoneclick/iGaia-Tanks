//
//  WebCommunicationMgr.m
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import "WebCommunicationMgr.h"
#import "GoogleGetCityLocationRequest.h"

static WebCommunicationMgr* gInstance;

@interface WebCommunicationMgr()
{
    NSOperationQueue* operationsQueue;
}
@end

@implementation WebCommunicationMgr

+ (WebCommunicationMgr*)instance
{
	if (gInstance == nil)
		gInstance = [[WebCommunicationMgr alloc] init];
	
	return gInstance;
}

- (id)init
{
    self = [super init];
    if (self)
    {
        operationsQueue = [[NSOperationQueue alloc] init];
        [operationsQueue setMaxConcurrentOperationCount:10];
    }
    return self;
}

- (void)googleRequestWithParams:(NSDictionary*)params withSuccess:(void (^)(id))successBlock withFailure:(void (^)(id))failureBlock
{
    GoogleGetCityLocationRequest* request = [[GoogleGetCityLocationRequest alloc] initWithParams:params];
    __weak __block BaseWebRequestOperation* blockRequest = request;
    
    [request setSuccessBlock:^{
        successBlock(blockRequest.data);
    }];
    
    [request setFailureBlock:^{
         failureBlock(nil);
     }];

    [request setSuccessBlock:successBlock];
    [request setFailureBlock:failureBlock];
    [operationsQueue addOperation:request];
}

@end
