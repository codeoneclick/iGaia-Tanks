const char* ShaderParticleNDF = STRINGIFY(
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   varying highp vec2 OUT_TexCoord;
                                                   varying lowp  vec4 OUT_Color;
                                       
void main(void)
{
    gl_FragColor = vec4(1.0, 0.0, 0.0, texture2D(EXT_TEXTURE_01, OUT_TexCoord).a) * OUT_Color;
}
);
