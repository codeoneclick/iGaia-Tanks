//
//  CMainMenuView.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#ifndef CMainMenuView_h
#define CMainMenuView_h

#include "HCommon.h"
#include "IUIView.h"
#include "CUIEventCallback.h"

class CMainMenuView :
public IUIView_INTERFACE,
public CUIEventCallback_INTERFACE
{
private:

protected:

    void OnUIEventPerform(const std::string& _command, i32 _x, i32 _y);

public:
    
	CMainMenuView(void);
	~CMainMenuView(void);

};

#endif 
