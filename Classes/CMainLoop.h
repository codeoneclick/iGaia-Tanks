//
//  CMainLoop_iOS.h
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#ifndef CMainLoop_h
#define CMainLoop_h

#include "HCommon.h"
#include "CMainLoopUpdateCallback.h"

void ConnectToMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener);
void DisconnectFromMainLoop(CMainLoopUpdateCallback_INTERFACE* _listener);

#ifndef __APPLE__

void Run(void);

#endif

#endif 
