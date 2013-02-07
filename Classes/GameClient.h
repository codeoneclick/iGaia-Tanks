//
//  GameClient.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameClient__
#define __iGaia__GameClient__

#include "HCommon.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "GameNetworkProtocol.h"

class GameClient
{
protected:
    int m_iSocketId;
    pthread_t m_iThread;
    pthread_mutex_t m_iMutex;
    std::vector<CPacket*> m_lPacketContainer;
    friend void* GameClientThread(void *_pParam);
public:
    GameClient(void);
    ~GameClient(void);
    void Start(void);
    void Stop(void);
    void Update(void);
    
    void Send_Position(const glm::vec3& _vPosition);
};

#endif /* defined(__iGaia__GameClient__) */
