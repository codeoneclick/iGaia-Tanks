//
//  CLandscapeDecal.h
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#ifndef CLandscapeDecal_h
#define CLandscapeDecal_h

#include "CGameObject3d.h"

class CLandscapeDecal : public CGameObject3d
{
private:
    
    static glm::mat3x3 m_matrixTextureTranslation;
    static glm::mat3x3 m_matrixTextureScale;
    glm::mat3x3 m_matrixTextureRotation;
    glm::mat3x3 m_matrixTextureResult;
    
protected:

    ui32 m_width;
    ui32 m_height;
    i32 m_widthOffset;
    i32 m_heightOffset;
    
    glm::vec4 m_color;
    f32* m_heightmapData;
    ui32 m_heightmapWidth;
    ui32 m_heightmapHeight;

    void OnResourceLoaded(TSharedPtrResource _resource);

    void OnUpdate(f32 _deltatime);

    ui32 OnDrawIndex(void);
    void OnBind(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnDraw(E_RENDER_MODE_WORLD_SPACE _mode);
    void OnUnbind(E_RENDER_MODE_WORLD_SPACE _mode);
    
public:
    
    CLandscapeDecal(void);
    ~CLandscapeDecal(void);
    
    inline void Set_Color(const glm::vec4& _color)
    {
        m_color = _color;
    };

    inline void Set_HeightmapData(f32* _heightmapData)
    {
        m_heightmapData = _heightmapData;
    };

    inline void Set_HeightmapWidth(ui32 _heightmapWidth)
    {
        m_heightmapWidth = _heightmapWidth;
    };

    inline void Set_HeightmapHeight(ui32 _heightmapHeight)
    {
        m_heightmapHeight = _heightmapHeight;
    };

    void Load(CResourceMgrsFacade* _resourceMgrsFacade, CShaderComposite* _shaderComposite, const std::string& _filename);
};

#endif 
