const char* ShaderPostBloomExtractF = STRINGIFY(

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
    mediump float fBloomTreshHold = 0.2;
    mediump vec4 vColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
    vColor = clamp((vColor - fBloomTreshHold) / (1.0 - fBloomTreshHold), 0.0, 1.0);
    gl_FragColor = vColor;
}
);
