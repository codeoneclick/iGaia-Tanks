//
//  BaseWebRequestOperation.h
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import "BaseOperation.h"

static NSString* k_METHOD_POST = @"POST";
static NSString* k_METHOD_GET = @"GET";

@interface BaseWebRequestOperation : BaseOperation

@property (nonatomic, retain) NSString* method;
@property (nonatomic, retain) NSURL* url;
@property (nonatomic, retain) NSData* params;
@property (nonatomic, retain) NSMutableData* data;
@property (nonatomic, retain) id <NSObject> error;

@end
