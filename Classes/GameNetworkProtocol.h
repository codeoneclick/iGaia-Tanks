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
    virtual void* Get_DeserializePtr(void) = 0;
    virtual void* Get_SerealizePtr(void) = 0;
};

class CPacketMessageIdDeserializer : public CPacket
{
public:
    int m_iMessageId;
    CPacketMessageIdDeserializer(void){};
    ~CPacketMessageIdDeserializer(void){};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketMessageIdDeserializer) - sizeof(int); };
    void* Get_DeserializePtr(void) { return &m_iMessageId; }
    void* Get_SerealizePtr(void) { return NULL; }
};

class CPacketPingSerializer : public CPacket
{
public:
    mutable int m_iMessageId;
    int m_iTime;
    CPacketPingSerializer(void):m_iMessageId(k_NETWORK_PROTOCOL_PING){};
    ~CPacketPingSerializer(void) {};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketPingSerializer) - sizeof(int); };
    void* Get_DeserializePtr(void) { return NULL; }
    void* Get_SerealizePtr(void) { return static_cast<void*>(&m_iMessageId); }
};

class CPacketPingDeserializer : public CPacket
{
public:
    int m_iTime;
    CPacketPingDeserializer(void){};
    ~CPacketPingDeserializer(void){};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketPingDeserializer) - sizeof(int); };
    void* Get_DeserializePtr(void) { return &m_iTime; }
    void* Get_SerealizePtr(void) { return NULL; }
};

class CPacketUserSerializer : public CPacket
{
public:
    mutable int m_iMessageId;
    std::string m_sName;
    int m_iSkillLight;
    int m_iSkillMedium;
    int m_iSkillHeavy;
    CPacketUserSerializer(void):m_iMessageId(k_NETWORK_PROTOCOL_USER){};
    ~CPacketUserSerializer(void){};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketUserSerializer) - sizeof(int); };
};

class CPacketUserDeserializer : public CPacket
{
public:
    std::string m_sName;
    int m_iSkillLight;
    int m_iSkillMedium;
    int m_iSkillHeavy;
    CPacketUserDeserializer(void){};
    ~CPacketUserDeserializer(void){};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketUserDeserializer) - sizeof(int); };
};

class CPacketPositionSerializer : public CPacket
{
public:
    mutable int m_iMessageId;
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    CPacketPositionSerializer(void):m_iMessageId(k_NETWORK_PROTOCOL_POSITION){};
    ~CPacketPositionSerializer(void){};
    unsigned int Get_MessageSize(void) { return sizeof(CPacketPositionSerializer) - sizeof(int); };
    void* Get_DeserializePtr(void) { return NULL; }
    void* Get_SerealizePtr(void) { return static_cast<void*>(&m_iMessageId); }
};

class CPacketPositionDeserializer : CPacket
{
public:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    CPacketPositionDeserializer(void){};
    ~CPacketPositionDeserializer(void){};
    unsigned int Get_MessageSize(void){ return sizeof(CPacketPositionDeserializer) - sizeof(int); };
    void* Get_DeserializePtr(void) { return &m_vPosition; }
    void* Get_SerealizePtr(void) { return NULL; }
};


#endif





