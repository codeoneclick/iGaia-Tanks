//
//  GameNetworkProtocol.h
//  iGaia
//
//  Created by sergey sergeev on 8/14/12.
//
//

#ifndef iGaia_GameNetworkProtocol_h
#define iGaia_GameNetworkProtocol_h

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define k_NETWORK_PROTOCOL_NONE 0
#define k_NETWORK_PROTOCOL_PING 1
#define k_NETWORK_PROTOCOL_USER 2
#define k_NETWORK_PROTOCOL_POSITION 3

class CPacket
{
public:
    CPacket(void){};
    virtual ~CPacket(void){};
    virtual unsigned int Get_MessageSize(void) = 0;
};

class CPacketMessageIdDeserializer
{
public:
    int m_iMessageId;
    CPacketMessageIdDeserializer(void){};
    ~CPacketMessageIdDeserializer(void){};
};

class CPacketPingSerializer : public CPacket
{
public:
    const int m_iMessageId;
    int m_iTime;
    CPacketPingSerializer(void):m_iMessageId(k_NETWORK_PROTOCOL_PING){};
    ~CPacketPingSerializer(void) {};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketPingSerializer); };
};

class CPacketPingDeserializer
{
public:
    int m_iTime;
    CPacketPingDeserializer(void){};
    ~CPacketPingDeserializer(void){};
};

class CPacketUserSerializer : public CPacket
{
public:
    const int m_iMessageId;
    std::string m_sName;
    int m_iSkillLight;
    int m_iSkillMedium;
    int m_iSkillHeavy;
    CPacketUserSerializer(void):m_iMessageId(k_NETWORK_PROTOCOL_USER){};
    ~CPacketUserSerializer(void){};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketUserSerializer); };
};

class CPacketUserDeserializer
{
public:
    std::string m_sName;
    int m_iSkillLight;
    int m_iSkillMedium;
    int m_iSkillHeavy;
    CPacketUserDeserializer(void){};
    ~CPacketUserDeserializer(void){};
};

class CPacketPositionSerializer : public CPacket
{
public:
    const int m_iMessageId;
    glm::vec3 m_vPosition;
    CPacketPositionSerializer(void):m_iMessageId(k_NETWORK_PROTOCOL_POSITION){};
    ~CPacketPositionSerializer(void){};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketPositionSerializer); };
};

class CPacketPositionDeserializer
{
public:
    glm::vec3 m_vPosition;
    CPacketPositionDeserializer(void){};
    ~CPacketPositionDeserializer(void){};
};


#endif





