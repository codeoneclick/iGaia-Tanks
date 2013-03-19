//
//  CRotateControllerView_iOS.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/19/13.
//
//

#include <UIKit/UIKit.h>
#include "CRotateControllerCallback.h"

@interface CRotateControllerView_iOS : UIView

- (void)AddEventListener:(CRotateControllerCallback_INTERFACE*)_listener;
- (void)RemoveEventListener:(CRotateControllerCallback_INTERFACE*)_listener;

@end
