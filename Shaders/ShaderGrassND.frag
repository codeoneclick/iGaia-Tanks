const char* ShaderGrassNDF = STRINGIFY(                                   
                                                    varying lowp    vec2   OUT_TexCoord;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                       
void main(void)
{
    gl_FragColor = vec4(1.0, 0.0, 0.0, texture2D(EXT_TEXTURE_01, OUT_TexCoord).a);
}
);
