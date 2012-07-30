const char* ShaderSkyboxF = STRINGIFY(                                  
                                                  varying highp vec2   OUT_TexCoord;
                                                  uniform sampler2D EXT_TEXTURE_01;
void main(void)
{
    gl_FragColor = mix(texture2D(EXT_TEXTURE_01, OUT_TexCoord), vec4(1.0, 1.0, 1.0, 1.0), 1.2 - OUT_TexCoord.y);
}
);
