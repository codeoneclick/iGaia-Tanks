const char* ShaderParticleF = STRINGIFY(                                  
                                                    varying highp    vec2   OUT_TexCoord;
                                                    varying lowp     vec4   OUT_Color;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                       
void main(void)
{
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord) * OUT_Color;
}
);
