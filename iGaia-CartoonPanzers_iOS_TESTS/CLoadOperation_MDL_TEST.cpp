//
//  CLoadOperation_MDL_TEST.c
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "gtest/gtest.h"
#include "CLoadOperation_MDL.h"

TEST(CLoadOperation_MDL, CorrectFile)
{
    CLoadOperation_MDL* operation = new CLoadOperation_MDL();
    operation->Load("tank_heavy_body.mdl");
    EXPECT_TRUE(operation->Get_Status() == E_PARSER_STATUS_DONE);
    delete operation;
}

TEST(CLoadOperation_MDL, WrongFile)
{
    CLoadOperation_MDL* operation = new CLoadOperation_MDL();
    operation->Load("wrong.file");
    EXPECT_TRUE(operation->Get_Status() == E_PARSER_STATUS_ERROR);
    delete operation;
}

