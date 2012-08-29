//
//  BaseOperation.h
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import <Foundation/Foundation.h>

@interface BaseOperation : NSOperation

@property (nonatomic, copy) void (^successBlock)();
@property (nonatomic, copy) void (^failureBlock)();
@property (nonatomic, copy) void (^progressBlock)();
@property (nonatomic, copy) void (^cancelBlock)();

- (void)notifyOnSuccess:(NSMutableData*)data;
- (void)notifyOnFailure:(NSError*)error;
- (void)notifyOnProgress:(NSData*)data;
- (void)notifyOnCancel;

@end
