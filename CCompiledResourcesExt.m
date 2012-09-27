#import "CCompiledResources.h"

/*{%LOAD_TEMPLATE_M%}
+ (UIImage*)SANITISED_FILENAME_image
 {
    return [UIImage imageNamed:@"ORIGINAL_FILENAME"];
 }
 
{%LOAD_TEMPLATE_M END%}*/

/*{%IMAGELOADERS_M START%}*/
+ (UIImage*)Default_png_image
 {
    return [UIImage imageNamed:@"Default.png"];
 }
 
+ (UIImage*)icon_png_image
 {
    return [UIImage imageNamed:@"icon.png"];
 }
 
/*{%IMAGELOADERS_M END%}*/
