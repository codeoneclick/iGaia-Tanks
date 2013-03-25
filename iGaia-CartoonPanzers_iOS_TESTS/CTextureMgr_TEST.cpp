//
//  CTextureMgr_TEST.c
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "gtest/gtest.h"
#include "CTextureMgr.h"
#include "CTexture.h"

TEST(CTextureMgr, LoadCorrectFileSync)
{
    CTextureMgr* textureMgr = new CTextureMgr();
    CTexture* texture = static_cast<CTexture*>(textureMgr->StartLoadOperation("tank_medium.pvr", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
    EXPECT_NE(texture, nullptr);
}

TEST(CTextureMgr, LoadSameCorrectFileSync)
{
    CTextureMgr* textureMgr = new CTextureMgr();
    CTexture* texture_first = static_cast<CTexture*>(textureMgr->StartLoadOperation("tank_medium.pvr", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
    EXPECT_NE(texture_first, nullptr);
    for(ui32 i = 0; i < 999; ++i)
    {
        CTexture* texture_same = static_cast<CTexture*>(textureMgr->StartLoadOperation("tank_medium.pvr", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
        EXPECT_EQ(texture_same, texture_first);
    }
}

TEST(CTextureMgr, LoadWrongFileSync)
{
    CTextureMgr* textureMgr = new CTextureMgr();
    CTexture* texture = static_cast<CTexture*>(textureMgr->StartLoadOperation("wrong.file", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
    EXPECT_EQ(texture, nullptr);
}

TEST(CTextureMgr, LoadSameWrongFileSync)
{
    CTextureMgr* textureMgr = new CTextureMgr();
    for(ui32 i = 0; i < 999; ++i)
    {
        CTexture* texture = static_cast<CTexture*>(textureMgr->StartLoadOperation("wrong.file", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
        EXPECT_EQ(texture, nullptr);
    }
}
