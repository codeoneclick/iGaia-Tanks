//
//  CGameMenuUI.m
//  iGaia
//
//  Created by sergey sergeev on 7/5/12.
//
//

#include <QuartzCore/QuartzCore.h>
#import "CGameMenuUI.h"
#include "CGameSceneMgr.h"
#include "CGameInGameScene.h"
#include "CGameMainMenuScene.h"

@implementation CGameMenuUI
@synthesize m_pInfoLabel;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        UIButton* pUnloadButton = [[UIButton alloc] initWithFrame:CGRectMake(8, 56, 128, 32)];
        [pUnloadButton setBackgroundColor:[UIColor blackColor]];
        [pUnloadButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [pUnloadButton addTarget:self action:@selector(OnUnloadScenePress:) forControlEvents:UIControlEventTouchUpInside];
        pUnloadButton.layer.cornerRadius = 8;
        pUnloadButton.clipsToBounds = YES;
        [pUnloadButton setTitle:@"UNLOAD" forState:UIControlStateNormal];
        [self addSubview:pUnloadButton];
        
        UIButton* pLoadButton = [[UIButton alloc] initWithFrame:CGRectMake(8, 96, 128, 32)];
        [pLoadButton setBackgroundColor:[UIColor blackColor]];
        [pLoadButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [pLoadButton addTarget:self action:@selector(OnLoadScenePress:) forControlEvents:UIControlEventTouchUpInside];
        pLoadButton.layer.cornerRadius = 8;
        pLoadButton.clipsToBounds = YES;
        [pLoadButton setTitle:@"LOAD" forState:UIControlStateNormal];
        [self addSubview:pLoadButton];
        
        UIButton* pLightButton = [[UIButton alloc] initWithFrame:CGRectMake(480 - 136, 56, 128, 32)];
        [pLightButton setBackgroundColor:[UIColor blackColor]];
        [pLightButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [pLightButton addTarget:self action:@selector(OnLoadLight:) forControlEvents:UIControlEventTouchUpInside];
        pLightButton.layer.cornerRadius = 8;
        pLightButton.clipsToBounds = YES;
        [pLightButton setTitle:@"LIGHT" forState:UIControlStateNormal];
        [self addSubview:pLightButton];
        
        UIButton* pMediumButton = [[UIButton alloc] initWithFrame:CGRectMake(480 - 136, 96, 128, 32)];
        [pMediumButton setBackgroundColor:[UIColor blackColor]];
        [pMediumButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [pMediumButton addTarget:self action:@selector(OnLoadMedium:) forControlEvents:UIControlEventTouchUpInside];
        pMediumButton.layer.cornerRadius = 8;
        pMediumButton.clipsToBounds = YES;
        [pMediumButton setTitle:@"MEDIUM" forState:UIControlStateNormal];
        [self addSubview:pMediumButton];
        
        UIButton* pHeavyButton = [[UIButton alloc] initWithFrame:CGRectMake(480 - 136, 136, 128, 32)];
        [pHeavyButton setBackgroundColor:[UIColor blackColor]];
        [pHeavyButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [pHeavyButton addTarget:self action:@selector(OnLoadHeavy:) forControlEvents:UIControlEventTouchUpInside];
        pHeavyButton.layer.cornerRadius = 8;
        pHeavyButton.clipsToBounds = YES;
        [pHeavyButton setTitle:@"HEAVY" forState:UIControlStateNormal];
        [self addSubview:pHeavyButton];
        
        m_pInfoLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 480, 32)];
        [m_pInfoLabel setBackgroundColor:[UIColor blackColor]];
        [m_pInfoLabel setTextColor:[UIColor whiteColor]];
        [self addSubview:m_pInfoLabel];
    }
    return self;
}

- (void)OnUnloadScenePress:(UIButton*)sender
{
    CGameMainMenuScene* pScene = static_cast<CGameMainMenuScene*>(CGameSceneMgr::Instance()->Get_Scene());
    if(pScene == NULL)
    {
        return;
    }
    
    pScene->Unload();
    SAFE_DELETE(pScene);
    CGameSceneMgr::Instance()->Set_Scene(NULL);
}

- (void)OnLoadScenePress:(UIButton*)sender
{
    if(CGameSceneMgr::Instance()->Get_Scene() != NULL)
    {
        return;
    }
    
    CGameMainMenuScene* pScene = new CGameMainMenuScene();
    CGameSceneMgr::Instance()->Set_Scene(pScene);
    pScene->Load();
}

- (void)OnLoadLight:(UIButton*)sender
{
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    if(pScene != NULL && pScene->Get_MainCharacterController() != NULL)
    {
        ICharacterController* pController = pScene->Get_MainCharacterController();
        pController->Set_Body(ICharacterController::E_CHARACTER_PART_TYPE_LIGHT);
        pController->Set_Tower(ICharacterController::E_CHARACTER_PART_TYPE_LIGHT);
        pController->Set_Track(ICharacterController::E_CHARACTER_PART_TYPE_LIGHT);
    }
}

- (void)OnLoadMedium:(UIButton*)sender
{
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    if(pScene != NULL && pScene->Get_MainCharacterController() != NULL)
    {
        pScene->Get_MainCharacterController()->Set_Body(ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM);
        pScene->Get_MainCharacterController()->Set_Tower(ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM);
        pScene->Get_MainCharacterController()->Set_Track(ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM);
    }
}

- (void)OnLoadHeavy:(UIButton*)sender
{
    IGameScene* pScene = CGameSceneMgr::Instance()->Get_Scene();
    if(pScene != NULL && pScene->Get_MainCharacterController() != NULL)
    {
        pScene->Get_MainCharacterController()->Set_Body(ICharacterController::E_CHARACTER_PART_TYPE_HEAVY);
        pScene->Get_MainCharacterController()->Set_Tower(ICharacterController::E_CHARACTER_PART_TYPE_HEAVY);
        pScene->Get_MainCharacterController()->Set_Track(ICharacterController::E_CHARACTER_PART_TYPE_HEAVY);
    }
}


@end
