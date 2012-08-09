//
//  GoogleGetCityLocationRequest.h
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import "BaseWebRequestOperation.h"

@interface GoogleGetCityLocationRequest : BaseWebRequestOperation
@property (nonatomic, strong) id data;
- (id)initWithParams:(NSDictionary*)params;
@end
