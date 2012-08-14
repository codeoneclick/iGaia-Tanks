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
    close(m_iSocketId);
}

void GameClient::Start(void)
{
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
    pthread_create(&m_iThread, NULL, GameClientThread, (void*)this);
}

void GameClient::Stop(void)
{
    close(m_iSocketId);
}

void GameClient::Send_Position(const glm::vec3 &_vPosition)
{
    CPacketPositionSerializer* pPacket = new CPacketPositionSerializer();
    pPacket->m_vPosition = _vPosition;
    m_lPacketContainer.push_back(pPacket);
}

void GameClient::Update(void)
{
    for(unsigned int index = 0; index < m_lPacketContainer.size(); ++index)
    {
        CPacket* pPacket = m_lPacketContainer[index];
        int iLength = write(m_iSocketId,pPacket, pPacket->Get_MessageSize());
        if(iLength < 0)
        {
            std::cout<<"[GameClient::Update] Socket Write Error"<<std::endl;
        }
        delete pPacket;
    }
    m_lPacketContainer.clear();
    /*char pBuffer[256];
    bzero(pBuffer,256);
    pBuffer[0] = 'c'; pBuffer[1] = 'o'; pBuffer[2] = 'd'; pBuffer[3] = 'e';
    SPacket packet;
    packet.vPosition = glm::vec3(128.0f, 128.0f, 128.0);
    int iLength = write(m_iSocketId,&packet, sizeof(SPacket));
    if(iLength < 0)
    {
        std::cout<<"[GameClient::Update] Socket Write Error"<<std::endl;
    }*/
    usleep(15);
}



