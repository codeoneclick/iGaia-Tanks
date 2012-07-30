const char* ShaderPostPlaneF = STRINGIFY(                                  
                                       varying highp   vec2   OUT_TexCoord;
                                       uniform sampler2D EXT_TEXTURE_01;
                                       
void main(void)
{
    gl_FragColor = texture2D(EXT_TEXTURE_01, OUT_TexCoord);
}
);
