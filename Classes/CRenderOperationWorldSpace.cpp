//
//  CRenderOperationWorldSpace.cpp
//  iGaia
//
//  Created by Sergey Sergeev on 2/27/13.
//
//

#include "CRenderOperationWorldSpace.h"

CRenderOperationWorldSpace::CRenderOperationWorldSpace(ui32 _frameWidth, ui32 _frameHeight, E_RENDER_MODE_WORLD_SPACE _mode, const std::string& _name)
{
    m_frameWidth = _frameWidth;
    m_frameHeight = _frameHeight;
    
    ui32 textureHandle;
    
    glGenTextures(1, &textureHandle);
    glGenFramebuffers(1, &m_frameBufferHandle);
    glGenRenderbuffers(1, &m_depthBufferHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_frameWidth, m_frameHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, NULL);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureHandle, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferHandle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_frameWidth, m_frameHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferHandle);

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    m_operatingTexture = new CTexture(textureHandle, m_frameWidth, m_frameHeight);
    m_operatingTexture->Set_WrapMode(GL_CLAMP_TO_EDGE);

    m_mode = _mode;
}

CRenderOperationWorldSpace::~CRenderOperationWorldSpace(void)
{

}

void CRenderOperationWorldSpace::AddEventListener(CRenderCallback_INTERFACE *_listener)
{
    assert(_listener != nullptr);
    assert(_listener->Get_Commands() != nullptr);
    
    if(m_listeners.find(_listener->Get_Commands()->DispatchRenderDidDrawIndex()) != m_listeners.end())
    {
        m_listeners.find(_listener->Get_Commands()->DispatchRenderDidDrawIndex())->second.insert(_listener);
    }
    else
    {
        m_listeners[_listener->Get_Commands()->DispatchRenderDidDrawIndex()].insert(_listener);
    }
}

void CRenderOperationWorldSpace::RemoveEventListener(CRenderCallback_INTERFACE *_listener)
{
    assert(_listener != nullptr);
    assert(_listener->Get_Commands() != nullptr);
    
    if(m_listeners.find(_listener->Get_Commands()->DispatchRenderDidDrawIndex()) != m_listeners.end())
    {
        m_listeners.find(_listener->Get_Commands()->DispatchRenderDidDrawIndex())->second.erase(_listener);
    }
    else
    {
        m_listeners[_listener->Get_Commands()->DispatchRenderDidDrawIndex()].erase(_listener);
    }
}

void CRenderOperationWorldSpace::Bind(void)
{
    glDepthMask(GL_TRUE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
    glViewport(0, 0, m_frameWidth, m_frameHeight);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CRenderOperationWorldSpace::Unbind(void)
{

}

void CRenderOperationWorldSpace::Draw(void)
{
    for(std::map<ui32, std::set<CRenderCallback_INTERFACE*>>::iterator iterator_01 = m_listeners.begin(); iterator_01 != m_listeners.end(); ++iterator_01)
    {
        for(std::set<CRenderCallback_INTERFACE*>::iterator iterator_02 = (*iterator_01).second.begin(); iterator_02 !=  (*iterator_01).second.end(); ++iterator_02)
        {
            CRenderCallback_INTERFACE* listener = (*iterator_02);

            assert(listener != nullptr);
            assert(listener->Get_Commands() != nullptr);
            
            listener->Get_Commands()->DispatchRenderDidBind(m_mode);
            listener->Get_Commands()->DispatchRenderDidDraw(m_mode);
            listener->Get_Commands()->DispatchRenderDidUnbind(m_mode);
        }
    }
}
