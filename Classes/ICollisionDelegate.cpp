//
//  ICollisionDelegate.cpp
//  iGaia
//
//  Created by sergey sergeev on 8/7/12.
//
//

#include "ICollisionDelegate.h"

ICollisionDelegate::ICollisionDelegate(void)
{
    m_eDelegateType = E_DELEGATE_TYPE_COLLISION;
    m_sColliderIdStr = "none";
    m_pBox2dBody = NULL;
}

ICollisionDelegate::~ICollisionDelegate(void)
{
    
}

void ICollisionDelegate::Set_OriginPosition(const glm::vec3 &vPosition)
{
    if(m_pBox2dBody != NULL)
    {
        m_pBox2dBody->SetTransform(b2Vec2(vPosition.x, vPosition.z),m_pBox2dBody->GetAngle());
    }
}

b2Vec2 ICollisionDelegate::_Get_LateralVelocity(void)
{
    b2Vec2 currentRightNormal = m_pBox2dBody->GetWorldVector(b2Vec2(1,0));
    return b2Dot( currentRightNormal, m_pBox2dBody->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 ICollisionDelegate::_Get_ForwardVelocity(void)
{
    b2Vec2 currentForwardNormal = m_pBox2dBody->GetWorldVector( b2Vec2(0,1) );
    return b2Dot( currentForwardNormal, m_pBox2dBody->GetLinearVelocity() ) * currentForwardNormal;
}

void ICollisionDelegate::_UpdateFriction(void)
{
    /*float maxLateralImpulse = 2.5f;
    b2Vec2 impulse = m_pBox2dBody->GetMass() * -_Get_LateralVelocity();
    if ( impulse.Length() > maxLateralImpulse )
        impulse *= maxLateralImpulse / impulse.Length();
    m_pBox2dBody->ApplyLinearImpulse( impulse, m_pBox2dBody->GetWorldCenter() );
    
    m_pBox2dBody->ApplyAngularImpulse( 0.1f * m_pBox2dBody->GetInertia() * -m_pBox2dBody->GetAngularVelocity() );
    
    b2Vec2 currentForwardNormal = _Get_ForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2.0f * currentForwardSpeed;
    m_pBox2dBody->ApplyForce( dragForceMagnitude * currentForwardNormal, m_pBox2dBody->GetWorldCenter() );*/
}

void ICollisionDelegate::_UpdateDrive(int _iControlState)
{
    b2Vec2 vMoveVelocity = m_pBox2dBody->GetLinearVelocity();
    float fTurnVelocity = m_pBox2dBody->GetAngularVelocity();
    switch(_iControlState)
    {
        case 1:
            vMoveVelocity.y += 1.0f;
            fTurnVelocity *= 0.8f;
            break;
        case 2:
            vMoveVelocity.y -= 1.0f;
            fTurnVelocity *= 0.8f;
            break;
        default:
            return;
    }
    m_pBox2dBody->SetLinearVelocity(vMoveVelocity);
    m_pBox2dBody->SetAngularVelocity(fTurnVelocity);
    
    /*float desiredSpeed = 0;
    switch(_iControlState)
    {
        case 1:
            desiredSpeed = 100.0f;
            break;
        case 2:
            desiredSpeed = -50.0f;
            break;
        default:
            return;
    }
    
    b2Vec2 currentForwardNormal = m_pBox2dBody->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot( _Get_ForwardVelocity(), currentForwardNormal );
    
    float force = 0;
    if ( desiredSpeed > currentSpeed )
    {
        force = 150.0f;
    }
    else if ( desiredSpeed < currentSpeed )
        force = -150.0f;
    else
        return;
    m_pBox2dBody->ApplyForce( force * currentForwardNormal, m_pBox2dBody->GetWorldCenter() );*/
}

void ICollisionDelegate::_UpdateTurn(int _iControlState)
{
    float fTurnVelocity = m_pBox2dBody->GetAngularVelocity();
    switch(_iControlState)
    {
        case 1:
            fTurnVelocity += 0.1f;
            break;
        case 2:
            fTurnVelocity -= 0.1f;
            break;
        default:
            return;
    }
    m_pBox2dBody->SetAngularVelocity(fTurnVelocity);
    /*float desiredTorque = 0;
    switch (_iControlState)
    {
        case 1:
            desiredTorque = 150;
            break;
        case 2:
            desiredTorque = -150;
            break;
        default:
            break;
    }
    m_pBox2dBody->ApplyTorque( desiredTorque );*/
}
