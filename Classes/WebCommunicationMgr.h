//
//  WebCommunicationMgr.h
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import <Foundation/Foundation.h>

@interface WebCommunicationMgr : NSObject

+ (WebCommunicationMgr*)instance;
- (void)googleRequestWithParams:(NSDictionary*)params withSuccess:(void (^)(id))successBlock withFailure:(void (^)(id))failureBlock;

@end
