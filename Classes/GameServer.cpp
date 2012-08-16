//
//  GameServer.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#include "GameServer.h"

void* GameServerThread(void *_pParam)
{
    GameServer* pInstance = static_cast<GameServer*>(_pParam);
    while (true)
    {
        pInstance->Update();
    }
}

GameServer::GameServer(void)
{
    m_iSocketId = 0;
}

GameServer::~GameServer(void)
{
    closesocket(m_iSocketId);
}

void GameServer::Start(void)
{
#ifdef OS_IPHONE
    if ((m_iSocketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        std::cout<<"[GameServer::Start] Creating Socket Error"<<std::endl;
    }
    struct sockaddr_in server_addr;
    struct hostent *server;
    server = gethostbyname("127.0.0.1");
    if (server == NULL)
    {
        std::cout<<"[GameServer::Start] Host Error"<<std::endl;
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(56756);
    
    if (bind(m_iSocketId, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
    {
        std::cout<<"[GameServer::Start] Socket Bind Error"<<std::endl;
    }
    listen(m_iSocketId, 4);
#endif
    
    pthread_create(&m_iThread, NULL, GameServerThread, (void*)this);
}

void GameServer::Stop(void)
{
    closesocket(m_iSocketId);
}

void GameServer::Update(void)
{
#ifdef OS_IPHONE
    struct sockaddr_in client_addr;
    socklen_t clint_length;
    clint_length = sizeof(client_addr);
    int iSokectId = accept(m_iSocketId, (struct sockaddr*)&client_addr, &clint_length);
    if (iSokectId < 0)
    {
        std::cout<<"[GameServer::Update] Socket Accept Error"<<std::endl;
    }
    else
    {
        GameClientHandler* pClientHandler = new GameClientHandler();
        m_lGameClientHandlers.push_back(pClientHandler);
        pClientHandler->Create(iSokectId);
    }
    usleep(1000);
#endif
}


