//
//  BaseOperation.h
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import <Foundation/Foundation.h>

@interface BaseOperation : NSOperation

@property (nonatomic, assign) SEL successSelector;
@property (nonatomic, assign) SEL failureSelector;
@property (nonatomic, assign) SEL progressSelector;
@property (nonatomic, assign) SEL cancelSelector;

@property (nonatomic, copy) void (^successBlock)();
@property (nonatomic, copy) void (^failureBlock)();
@property (nonatomic, copy) void (^progressBlock)();
@property (nonatomic, copy) void (^cancelBlock)();

- (void) notifyOnSuccess;
- (void) notifyOnFailure;
- (void) notifyOnProgress;
- (void) notifyOnCancel;

@end
