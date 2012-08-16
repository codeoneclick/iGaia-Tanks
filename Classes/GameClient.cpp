//
//  GameClient.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameClient.h"

void* GameClientThread(void *_pParam)
{
    GameClient* pInstance = static_cast<GameClient*>(_pParam);
    while (true)
    {
        pInstance->Update();
    }
}

GameClient::GameClient(void)
{
    m_iSocketId = 0;
}

GameClient::~GameClient(void)
{
    closesocket(m_iSocketId);
}

void GameClient::Start(void)
{
#ifdef OS_IPHONE
    if ((m_iSocketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        std::cout<<"[GameClient::Start] Creating Socket Error"<<std::endl;
    }
    struct sockaddr_in server_addr;
    struct hostent *server;
    server = gethostbyname("127.0.0.1");
    if (server == NULL)
    {
        std::cout<<"[GameClient::Start] Host Error"<<std::endl;
    }

    bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(56756);
    
    if (connect(m_iSocketId,(struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        std::cout<<"[GameClient::Start] Socket Connect Error"<<std::endl;
    }
#endif
    pthread_mutex_init(&m_iMutex, NULL);
    pthread_create(&m_iThread, NULL, GameClientThread, (void*)this);
}

void GameClient::Stop(void)
{
    closesocket(m_iSocketId);
}

void GameClient::Send_Position(const glm::vec3 &_vPosition)
{
    CPacketPositionSerializer* pPacket = new CPacketPositionSerializer();
    pPacket->m_vPosition = _vPosition;
    pPacket->m_vRotation = glm::vec3(30.0f, 90.0f, 180.0f);
    pthread_mutex_lock(&m_iMutex);
    m_lPacketContainer.push_back(pPacket);
    pthread_mutex_unlock(&m_iMutex);
}

void GameClient::Update(void)
{
    pthread_mutex_lock(&m_iMutex);
#ifdef OS_IPHONE
    for(unsigned int index = 0; index < m_lPacketContainer.size(); ++index)
    {
        CPacket* pPacket = m_lPacketContainer[index];
        int iPreMessageSize = pPacket->Get_MessageSize();
        int iSendMessageSize = write(m_iSocketId,pPacket->Get_SerealizePtr(), iPreMessageSize);
        if(iSendMessageSize < 0)
        {
            std::cout<<"[GameClient::Update] Socket Write Error"<<std::endl;
        }
        delete pPacket;
    }
    m_lPacketContainer.clear();
#endif
    pthread_mutex_unlock(&m_iMutex);
#ifdef OS_IPHONE
    usleep(1000);
#endif
}



