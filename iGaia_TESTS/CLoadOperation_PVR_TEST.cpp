//
//  CLoadOperation_PVR_TEST.c
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "gtest/gtest.h"
#include "CLoadOperation_PVR.h"

TEST(CLoadOperation_PVR, CorrectFile)
{
    CLoadOperation_PVR* operation = new CLoadOperation_PVR();
    operation->Load("tank_medium.pvr");
    EXPECT_TRUE(operation->Get_Status() == E_PARSER_STATUS_DONE);
    delete operation;
}

TEST(CLoadOperation_PVR, WrongFile)
{
    CLoadOperation_PVR* operation = new CLoadOperation_PVR();
    operation->Load("wrong.file");
    EXPECT_TRUE(operation->Get_Status() == E_PARSER_STATUS_ERROR);
    delete operation;
}
