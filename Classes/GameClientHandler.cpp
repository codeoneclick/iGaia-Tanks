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
#ifndef WIN32
    close(m_iSocketId);
#else
    closesocket(m_iSocketId);
#endif
}

void GameClientHandler::Create(int _iSocketId)
{
    m_iSocketId = _iSocketId;
    pthread_create(&m_iThread, NULL, GameServerClientHandlerThread, (void*)this);
}

void GameClientHandler::Update(void)
{
#ifndef WIN32
    CPacketMessageIdDeserializer pPacketMessageId;
    int iPreMessageSize = pPacketMessageId.Get_MessageSize();
    int iRecvMessageSize = read(m_iSocketId, pPacketMessageId.Get_DeserializePtr(), iPreMessageSize);
    if (iRecvMessageSize < 0)
    {
        std::cout<<"[GameServer::Update] Socket Read Error"<<std::endl;
    }
    else
    {
        std::cout<<"[GameServer::Update] Socket Message with Message Id: "<<pPacketMessageId.m_iMessageId<<std::endl;
        
        switch (pPacketMessageId.m_iMessageId)
        {
            case k_NETWORK_PROTOCOL_POSITION:
            {
                CPacketPositionDeserializer pPacketPosition;
                int iMessageSize = pPacketPosition.Get_MessageSize();
                int iLengthPosition = read(m_iSocketId, pPacketPosition.Get_DeserializePtr(), iMessageSize);
                if (iLengthPosition < 0)
                {
                    std::cout<<"[GameServer::Update] Socket Read Error Position Message"<<std::endl;
                }
                else
                {
                     std::cout<<"[GameServer::Update] Socket Message with Position Message: "<<pPacketPosition.m_vPosition.x<<","<<pPacketPosition.m_vPosition.z<<std::endl;
                     std::cout<<"[GameServer::Update] Socket Message with Rotation Message: "<<pPacketPosition.m_vRotation.x<<","<<pPacketPosition.m_vRotation.y<<","<<pPacketPosition.m_vRotation.z<<std::endl;
                }
            }
                break;
                
            default:
                break;
        }
    }
    usleep(1000);
#endif
}