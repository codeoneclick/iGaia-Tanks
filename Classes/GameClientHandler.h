//
//  GameClientHandler.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameClientHandler__
#define __iGaia__GameClientHandler__

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#ifdef OS_IPHONE
#include "stdlib.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#else
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>	
#endif
#include <pthread.h>
#include "GameNetworkProtocol.h"

class GameClientHandler
{
protected:
    CPacketMessageIdDeserializer* m_pPacketMessageIdDeserializer;
    CPacketPositionDeserializer* m_pPacketPositionDeserializer;
    
    int m_iSocketId;
    pthread_t m_iThread;
    friend void* GameServerClientHandlerThread(void *_pParam);
public:
    GameClientHandler(void);
    ~GameClientHandler(void);
    void Create(int _iSocketId);
    void Update(void);
};

#endif /* defined(__iGaia__GameClientHandler__) */
