const char* ShaderPostBloomCombineF = STRINGIFY(

                                                   varying mediump vec3   OUT_View;
                                                   varying mediump vec3   OUT_Light;
                                                   varying mediump vec3   OUT_Normal;                                     
                                                   varying mediump vec2   OUT_TexCoord;
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    mediump float fBloomIntensity = 1.25;
    mediump float fBaseIntensity = 1.0;
    
    mediump float fBloomSaturation = 1.0;
    mediump float fBaseSaturation = 1.0;
    
    mediump vec4 vBloomColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    mediump vec4 vBaseColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord);
    
    mediump float fSaturationBloom = dot(vBloomColor.xyz, vec3(0.3, 0.59, 0.11));
    mediump vec4 vBloomSaturationColor = mix(vec4(fSaturationBloom,fSaturationBloom,fSaturationBloom, 1.0), vBloomColor, fBloomSaturation) * fBloomIntensity;
    
    mediump float fSaturationBase = dot(vBaseColor.xyz, vec3(0.3, 0.59, 0.11));
    mediump vec4 vBaseSaturationColor = mix(vec4(fSaturationBase,fSaturationBase,fSaturationBase, 1.0), vBaseColor, fBaseSaturation) * fBaseIntensity;
    
    vBaseSaturationColor *= (1.0 - vBloomSaturationColor);
                             
    mediump vec4 vColor = vBaseSaturationColor + vBloomSaturationColor;
    gl_FragColor = vColor;
}
);
