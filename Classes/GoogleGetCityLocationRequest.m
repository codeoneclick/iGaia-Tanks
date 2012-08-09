//
//  GoogleGetCityLocationRequest.m
//  iGaia
//
//  Created by sergey sergeev on 8/9/12.
//
//

#import "GoogleGetCityLocationRequest.h"

static NSString* k_GOOGLE_MAP_URL = @"http://maps.google.com/maps/geo?";

@implementation GoogleGetCityLocationRequest

@synthesize data;

- (id)initWithParams:(NSDictionary *)params
{
    self = [super init];
    if (self)
    {
        self.method = k_METHOD_GET;
        
        NSMutableString* formattedStringForBody = [[NSMutableString alloc] initWithString:k_GOOGLE_MAP_URL];
        NSArray* array = [params allKeys];
        
        for (int i = ([array count] - 1); i >= 0 ; i--)
        {
            NSString* key = [array objectAtIndex:i];
            [formattedStringForBody appendString:[NSString stringWithFormat:@"%@=%@&", key, [params valueForKey:key]]];
        }
        [formattedStringForBody appendString:[NSString stringWithFormat:@"output=json"]];
        self.url = [NSURL URLWithString:[NSString stringWithString:formattedStringForBody]];
    }
    return self;
}


- (NSError*)processData:(id)_data
{
    if ([_data isKindOfClass:[NSArray class]])
    {
        NSMutableArray* array = [[NSMutableArray alloc] init];
        for (NSDictionary* json in _data)
        {
            NSLog(@"[GoogleGetCityLocationRequest] %@ \n", json);
        }
        self.data = array;
    }
    else
    {
        NSLog(@"[GoogleGetCityLocationRequest] %@ \n", _data);
        self.data = _data;
    }
    return nil;
}


@end
