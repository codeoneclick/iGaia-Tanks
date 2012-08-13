//
//  GameServer.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameServer__
#define __iGaia__GameServer__

#include <iostream>
#include "stdlib.h"
#include <vector.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include "GameClientHandler.h"

class GameServer
{
protected:
    int m_iSocketId;
    std::vector<GameClientHandler*> m_lGameClientHandlers;
    pthread_t m_iThread;
    friend void* GameServerThread(void *_pParam);
public:
    GameServer(void);
    ~GameServer(void);
    void Start(void);
    void Stop(void);
    void Update(void);
};

#endif /* defined(__iGaia__GameServer__) */
