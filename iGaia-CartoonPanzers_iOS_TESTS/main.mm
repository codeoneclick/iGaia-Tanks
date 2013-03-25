//
//  main.m
//  iGaia_TESTS
//
//  Created by Sergey Sergeev on 3/11/13.
//
//
#include "gtest/gtest.h"

int main(int argc, char *argv[])
{
    @autoreleasepool
    {
        ::testing::InitGoogleTest(&argc, argv);
        int result = RUN_ALL_TESTS();
        return result;
    }
}

