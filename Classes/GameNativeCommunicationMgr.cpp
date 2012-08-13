//
//  GameNativeCommunicationMgr.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameNativeCommunicationMgr.h"

GameNativeCommunicationMgr* GameNativeCommunicationMgr::m_pInstance = NULL;

GameNativeCommunicationMgr* GameNativeCommunicationMgr::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new GameNativeCommunicationMgr();
    }
    return m_pInstance;
}

GameNativeCommunicationMgr::GameNativeCommunicationMgr(void)
{
    m_pGameServer = NULL;
    m_pGameClient = NULL;
}

GameNativeCommunicationMgr::~GameNativeCommunicationMgr(void)
{
    
}

void GameNativeCommunicationMgr::CreateGameServer(void)
{
    m_pGameServer = new GameServer();
    m_pGameServer->Start();
}

void GameNativeCommunicationMgr::ConnectToGameServer(void)
{
    m_pGameClient = new GameClient();
    m_pGameClient->Start();
}

void GameNativeCommunicationMgr::ConnectToSDBServer(void)
{
    
}

void GameNativeCommunicationMgr::ConnectToLobbyServer(void)
{
    
}

void GameNativeCommunicationMgr::Update(void)
{
    /*if(m_pGameServer != NULL)
    {
        m_pGameServer->Update();
    }
    if(m_pGameClient != NULL)
    {
        m_pGameClient->Update();
    }*/
}
