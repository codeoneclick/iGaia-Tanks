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
    CPacketMessageIdDeserializer* pPacketMessageId = new CPacketMessageIdDeserializer();
    int iLength = read(m_iSocketId, pPacketMessageId, 4);
    if (iLength < 0)
    {
        std::cout<<"[GameServer::Update] Socket Read Error"<<std::endl;
    }
    else
    {
        std::cout<<"[GameServer::Update] Socket Message with Message Id: "<<pPacketMessageId->m_iMessageId<<std::endl;
        
        switch (pPacketMessageId->m_iMessageId)
        {
            case k_NETWORK_PROTOCOL_POSITION:
            {
                CPacketPositionDeserializer* pPacketPosition = new CPacketPositionDeserializer();
                int iLengthPosition = read(m_iSocketId, pPacketPosition, sizeof(CPacketPositionDeserializer));
                if (iLengthPosition < 0)
                {
                    std::cout<<"[GameServer::Update] Socket Read Error Position Message"<<std::endl;
                }
                else
                {
                     std::cout<<"[GameServer::Update] Socket Message with Position Message: "<<pPacketPosition->m_vPosition.x<<","<<pPacketPosition->m_vPosition.z<<std::endl;
                }
                delete pPacketPosition;
            }
                break;
                
            default:
                break;
        }
    }
    delete pPacketMessageId;
    
    
    /*char pBuffer[sizeof(SPacket)];
    bzero(pBuffer,sizeof(SPacket));
    
    int iLength = read(m_iSocketId, pBuffer, 255);
    SPacket* packet = static_cast<SPacket*>((void*)pBuffer);
    if (iLength < 0)
    {
        std::cout<<"[GameServer::Update] Socket Read Error"<<std::endl;
    }
    else
    {
        std::cout<<"[GameServer::Update] Socket Message : "<<packet->vPosition.x<<std::endl;
    }*/
    usleep(15);
}