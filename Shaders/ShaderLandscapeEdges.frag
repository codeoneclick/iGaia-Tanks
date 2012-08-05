const char* ShaderLandscapeEdgesF = STRINGIFY(                                  
                                                  varying highp vec2   OUT_TexCoord;
                                                  uniform highp vec2   EXT_Texcoord_Offset;
                                                  uniform sampler2D EXT_TEXTURE_01;
                                                  uniform sampler2D EXT_TEXTURE_02;
                                                  uniform sampler2D EXT_TEXTURE_03;
void main(void)
{
    lowp vec4 vMaskColor = texture2D(EXT_TEXTURE_03, OUT_TexCoord);
    lowp vec4 vEdgeColor_01 = texture2D(EXT_TEXTURE_01, OUT_TexCoord * 8.0) * vMaskColor.b;
    lowp vec4 vEdgeColor_02 = texture2D(EXT_TEXTURE_02, vec2(OUT_TexCoord.x * 8.0, OUT_TexCoord.y * 16.0) + EXT_Texcoord_Offset) * vMaskColor.g;
    vEdgeColor_02.a = vEdgeColor_02.a * 0.5;
    gl_FragColor = vEdgeColor_01 + vEdgeColor_02;
}
);
