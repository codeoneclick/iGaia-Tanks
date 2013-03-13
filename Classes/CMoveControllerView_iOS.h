//
//  CMoveControllerView_iOS.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/13/13.
//
//

#include <UIKit/UIKit.h>
#include "CMoveControllerCallback.h"

@interface CMoveControllerView_iOS : UIView

- (void)AddEventListener:(CMoveControllerCallback_INTERFACE*)_listener;
- (void)RemoveEventListener:(CMoveControllerCallback_INTERFACE*)_listener;

@end
