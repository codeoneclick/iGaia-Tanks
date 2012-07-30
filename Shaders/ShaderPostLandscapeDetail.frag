const char* ShaderPostLandscapeDetailF = STRINGIFY(

                                                   varying highp vec2 OUT_SplattingTexCoord;                                     
                                                   varying highp vec2 OUT_TexCoord;
uniform lowp sampler2D EXT_TEXTURE_01;
uniform lowp sampler2D EXT_TEXTURE_02;
uniform lowp sampler2D EXT_TEXTURE_03;
uniform lowp sampler2D EXT_TEXTURE_04;
uniform lowp sampler2D EXT_TEXTURE_05;
uniform lowp sampler2D EXT_TEXTURE_06;
uniform lowp sampler2D EXT_TEXTURE_07;
uniform lowp sampler2D EXT_TEXTURE_08;
                                       
void main(void)
{
    lowp vec4 vSplattingColor = texture2D(EXT_TEXTURE_07, OUT_SplattingTexCoord);
    
    lowp vec4 vDiffuseColor = vec4(0.0, 0.0, 0.0, 1.0);

    if(vSplattingColor.x > 0.0)
    {
        vDiffuseColor = vDiffuseColor + texture2D(EXT_TEXTURE_01, OUT_TexCoord) * vSplattingColor.x;
    }
    if(vSplattingColor.y > 0.0)
    {
        vDiffuseColor = vDiffuseColor + texture2D(EXT_TEXTURE_02, OUT_TexCoord) * vSplattingColor.y;
    }
    if(vSplattingColor.z > 0.0)
    {
        vDiffuseColor = vDiffuseColor + texture2D(EXT_TEXTURE_03, OUT_TexCoord) * vSplattingColor.z;
    }

    gl_FragColor = vDiffuseColor;
}
);
