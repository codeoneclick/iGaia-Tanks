//
//  GameClientHandler.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameClientHandler.h"

void* GameServerClientHandlerThread(void *_pParam)
{
    GameClientHandler* pInstance = static_cast<GameClientHandler*>(_pParam);
    while (true)
    {
        pInstance->Update();
    }
}

GameClientHandler::GameClientHandler(void)
{
    m_iSocketId = 0;
}

GameClientHandler::~GameClientHandler(void)
{
    close(m_iSocketId);
}

void GameClientHandler::Create(int _iSocketId)
{
    m_iSocketId = _iSocketId;
    pthread_create(&m_iThread, NULL, GameServerClientHandlerThread, (void*)this);
}

void GameClientHandler::Update(void)
{
    char pBuffer[256];
    bzero(pBuffer,256);
        
    int iLength = read(m_iSocketId, pBuffer, 255);
    if (iLength < 0)
    {
        std::cout<<"[GameServer::Update] Socket Read Error"<<std::endl;
    }
    else
    {
        std::cout<<"[GameServer::Update] Socket Message : "<<pBuffer<<std::endl;
    }
    sleep(1);
}