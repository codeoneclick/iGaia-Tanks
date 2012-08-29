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

@property (nonatomic, strong) NSString* method;
@property (nonatomic, strong) NSURL* url;
@property (nonatomic, strong) NSData* params;
@property (nonatomic, strong) NSMutableData* data;
@property (nonatomic, strong) NSError* error;

@end
