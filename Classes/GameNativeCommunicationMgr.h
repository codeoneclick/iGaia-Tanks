//
//  GameNativeCommunicationMgr.h
//  iGaia
//
//  Created by sergey sergeev on 8/13/12.
//
//

#ifndef __iGaia__GameNativeCommunicationMgr__
#define __iGaia__GameNativeCommunicationMgr__

#include "GameClient.h"
#include "GameServer.h"

class GameNativeCommunicationMgr
{
protected:
    static GameNativeCommunicationMgr* m_pInstance;
    GameServer* m_pGameServer;
    GameClient* m_pGameClient;
public:
    GameNativeCommunicationMgr(void);
    ~GameNativeCommunicationMgr(void);
    static GameNativeCommunicationMgr* Instance(void);
    void Update(void);
    void CreateGameServer(void);
    void ConnectToGameServer(void);
    void ConnectToSDBServer(void);
    void ConnectToLobbyServer(void);
    GameClient* Get_GameClient(void) { return m_pGameClient; }
};

#endif /* defined(__iGaia__GameNativeCommunicationMgr__) */
