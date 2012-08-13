//
//  GameClient.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameClient__
#define __iGaia__GameClient__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class GameClient
{
protected:
    int m_iSocketId;
    pthread_t m_iThread;
    friend void* GameClientThread(void *_pParam);
public:
    GameClient(void);
    ~GameClient(void);
    void Start(void);
    void Stop(void);
    void Update(void);
};

#endif /* defined(__iGaia__GameClient__) */
