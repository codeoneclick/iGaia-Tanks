const char* ShaderLandscapeEdgesF = STRING_SHADER(                                  
                                                  varying highp vec2   OUT_TexCoord;
                                                  uniform highp vec2   EXT_Texcoord_Offset;
                                                  uniform sampler2D EXT_TEXTURE_01;
                                                  uniform sampler2D EXT_TEXTURE_02;
                                                  uniform sampler2D EXT_TEXTURE_03;
void main(void)
{
    lowp vec4 vMaskColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord);
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord * 16.0) * vMaskColor.r;
}
);
