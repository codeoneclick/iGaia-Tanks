const char* ShaderModelNDF = STRINGIFY(
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   varying highp vec2 OUT_TexCoord;
                                       
void main(void)
{
    gl_FragColor = vec4(0.0, 1.0, 0.0, texture2D(EXT_TEXTURE_01, OUT_TexCoord).a);
}
);
