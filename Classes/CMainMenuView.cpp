//
//  CMainMenuView.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#include "CMainMenuView.h"

CMainMenuView::CMainMenuView(void)
{
    
}

CMainMenuView::~CMainMenuView(void)
{
    
}

void CMainMenuView::OnUIEventPerform(const std::string &_command, i32 _x, i32 _y)
{
    std::cout<<_command<<std::endl;
    std::cout<<"x: "<<_x<<" y: "<<_y<<std::endl;
}