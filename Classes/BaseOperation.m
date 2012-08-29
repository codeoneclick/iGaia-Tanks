//
//  BaseOperation.m
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import "BaseOperation.h"

@interface BaseOperation()
@property (nonatomic, assign) BOOL finished;
@property (nonatomic, assign) BOOL executing;
@end

@implementation BaseOperation

@synthesize finished;
@synthesize executing;

@synthesize successBlock;
@synthesize failureBlock;
@synthesize progressBlock;
@synthesize cancelBlock;

- (id) init
{
	if ((self = [super init]))
	{
		self.finished  = NO;
		self.executing = NO;
	}
	return self;
}


- (void) dealloc
{
	self.successBlock  = nil;
	self.failureBlock  = nil;
	self.progressBlock = nil;
	self.cancelBlock   = nil;
}

- (BOOL) isEqualToOperation: (BaseOperation*) operation
{
	return [self isEqual: operation];
}

- (void) start
{
	if (![self isCancelled]) 
	{
        [self willChangeValueForKey: @"isExecuting"];
        self.executing = YES;
        
		[NSThread detachNewThreadSelector: @selector(main) 
                                 toTarget: self 
                               withObject: nil];
        
		[self didChangeValueForKey:  @"isExecuting"];
    } 
    else 
	{
        [self willChangeValueForKey: @"isFinished"];
        self.finished = YES;
		[self didChangeValueForKey:  @"isFinished"];
    }
}

- (void) main
{
    @autoreleasepool
    {
        if ([self respondsToSelector: @selector(run)])
            [self performSelector: @selector(run)];
	
        [self willChangeValueForKey: @"isFinished"];
        [self willChangeValueForKey: @"isExecuting"];
    
        self.finished  = YES;
        self.executing = NO;
	
        [self didChangeValueForKey: @"isExecuting"];
        [self didChangeValueForKey: @"isFinished"];  
	}
}

- (BOOL) isExecuting
{
	return self.executing;
}

- (BOOL) isFinished
{
	return self.finished;
}

- (BOOL) isConcurrent
{
	return YES;
}

- (void)notifyOnSuccess:(NSMutableData*)data
{
    self.successBlock(data);
}

- (void)notifyOnFailure:(NSError*)error
{
    self.failureBlock(error);
}

- (void)notifyOnProgress:(NSData*)data
{
    self.progressBlock(data);
}

- (void) notifyOnCancel
{
    self.cancelBlock();
}


@end
