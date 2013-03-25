//
//  CCollisionMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CCollisionMgr.h"


CCollisionMgr::CCollisionMgr(void)
{
    m_box2dWorld = nullptr;
}

CCollisionMgr::~CCollisionMgr()
{
    delete m_box2dWorld;
}

void CCollisionMgr::Set_CollisionBounds(const glm::vec2 &_maxBound, const glm::vec2 &_minBound)
{
    assert(m_box2dWorld == nullptr);
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	m_box2dWorld = new b2World(gravity);
	m_box2dWorld->SetContinuousPhysics(true);
    m_box2dWorld->SetContactListener(this);
    
	b2BodyDef boundBodyDefinition;
	boundBodyDefinition.position.Set(0, 0);
	b2Body* boundBody = m_box2dWorld->CreateBody(&boundBodyDefinition);
    
	b2EdgeShape boundBox;
	boundBox.Set(b2Vec2(_minBound.x, _minBound.y), b2Vec2(_maxBound.x, _minBound.y));
	boundBody->CreateFixture(&boundBox, 0);
	boundBox.Set(b2Vec2(_minBound.x, _maxBound.y), b2Vec2(_maxBound.x, _maxBound.y));
	boundBody->CreateFixture(&boundBox, 0);
	boundBox.Set(b2Vec2(_minBound.x, _maxBound.y), b2Vec2(_minBound.x, _minBound.y));
	boundBody->CreateFixture(&boundBox, 0);
	boundBox.Set(b2Vec2(_maxBound.x, _maxBound.y), b2Vec2(_maxBound.x, _minBound.y));
	boundBody->CreateFixture(&boundBox, 0);
}

void CCollisionMgr::AddCollisionEventListener(CCollisionCallback_INTERFACE *_listener, bool _isStatic)
{
    assert(_listener != nullptr);
    assert(_listener->Get_Commands() != nullptr);
    assert(m_box2dWorld != nullptr);
    m_collidersContainer.insert(_listener);

    _listener->Get_Box2dBodyDefinition()->type = _isStatic == true ? b2_staticBody : b2_dynamicBody;
	_listener->Get_Box2dBodyDefinition()->position.Set(_listener->Get_Commands()->DispatchCenterDidRetrive().x, _listener->Get_Commands()->DispatchCenterDidRetrive().z);
	_listener->Get_Box2dBodyDefinition()->userData = _listener;
    _listener->Set_Box2dBody(m_box2dWorld->CreateBody(_listener->Get_Box2dBodyDefinition()));
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(( _listener->Get_Commands()->DispatchMaxboundDidRetrive().x - _listener->Get_Commands()->DispatchMinboundDidRetrive().x) / 2.0f,
                        (_listener->Get_Commands()->DispatchMaxboundDidRetrive().z - _listener->Get_Commands()->DispatchMinboundDidRetrive().z) / 2.0f);
	_listener->Get_Box2dBody()->CreateFixture(&dynamicBox, 1);
}

void CCollisionMgr::RemoveCollisionEventListener(CCollisionCallback_INTERFACE *_listener)
{
    assert(_listener != nullptr);
    assert(_listener->Get_Commands() != nullptr);
    m_collidersContainer.erase(_listener);
}

void CCollisionMgr::OnUpdate(f32 _deltatime)
{
    if(m_box2dWorld == nullptr)
    {
        return;
    }

    for(std::set<CCollisionCallback_INTERFACE*>::iterator iterator = m_collidersContainer.begin(); iterator !=  m_collidersContainer.end(); ++iterator)
    {
        CCollisionCallback_INTERFACE* listener = (*iterator);

        assert(listener != nullptr);
        assert(listener->Get_Commands() != nullptr);

        listener->Get_Commands()->DispatchPositionDidChange(glm::vec3(
                                                                      listener->Get_Box2dBody()->GetPosition().x,
                                                                      0.0f,
                                                                      listener->Get_Box2dBody()->GetPosition().y));
        listener->Get_Commands()->DispatchRotationDidChange(listener->Get_Box2dBody()->GetAngle());
    }
}

void CCollisionMgr::BeginContact(b2Contact* contact)
{
    CCollisionCallback_INTERFACE* bodyUserData_01 = static_cast<CCollisionCallback_INTERFACE*>(contact->GetFixtureA()->GetBody()->GetUserData());
    CCollisionCallback_INTERFACE* bodyUserData_02 = static_cast<CCollisionCallback_INTERFACE*>(contact->GetFixtureB()->GetBody()->GetUserData());
       
    if(bodyUserData_01 != nullptr)
    {
        bodyUserData_02->Get_Commands()->DispatchDidCollide(bodyUserData_01);
    }
    
    if(bodyUserData_02 != nullptr)
    {
        bodyUserData_01->Get_Commands()->DispatchDidCollide(bodyUserData_02);
    }
}

void CCollisionMgr::EndContact(b2Contact* contact)
{

}

