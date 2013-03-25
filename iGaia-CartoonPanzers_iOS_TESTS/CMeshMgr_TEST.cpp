//
//  CMeshMgr_TEST.c
//  iGaia
//
//  Created by Sergey Sergeev on 3/11/13.
//
//

#include "gtest/gtest.h"
#include "CMeshMgr.h"
#include "CMesh.h"

TEST(CMeshMgr, LoadCorrectFileSync)
{
    CMeshMgr* meshMgr = new CMeshMgr();
    CMesh* mesh = static_cast<CMesh*>(meshMgr->StartLoadOperation("tank_heavy_body.mdl", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
    EXPECT_NE(mesh, nullptr);
}

TEST(CMeshMgr, LoadSameCorrectFileSync)
{
    CMeshMgr* meshMgr = new CMeshMgr();
    CMesh* mesh_first = static_cast<CMesh*>(meshMgr->StartLoadOperation("tank_heavy_body.mdl", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
    EXPECT_NE(mesh_first, nullptr);
    for(ui32 i = 0; i < 999; ++i)
    {
        CMesh* mesh_same = static_cast<CMesh*>(meshMgr->StartLoadOperation("tank_heavy_body.mdl", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
        EXPECT_EQ(mesh_same, mesh_first);
    }
}

TEST(CMeshMgr, LoadWrongFileSync)
{
    CMeshMgr* meshMgr = new CMeshMgr();
    CMesh* mesh = static_cast<CMesh*>(meshMgr->StartLoadOperation("wrong.file", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
    EXPECT_EQ(mesh, nullptr);
}

TEST(CMeshMgr, LoadSameWrongFileSync)
{
    CMeshMgr* meshMgr = new CMeshMgr();
    for(ui32 i = 0; i < 999; ++i)
    {
        CMesh* mesh = static_cast<CMesh*>(meshMgr->StartLoadOperation("wrong.file", E_RESOURCE_LOAD_THREAD_SYNC, nullptr));
        EXPECT_EQ(mesh, nullptr);
    }
}
