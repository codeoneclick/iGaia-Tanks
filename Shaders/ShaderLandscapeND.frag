const char* ShaderLandscapeNDF = STRINGIFY(                                    
                                                   varying lowp vec4   OUT_Color;
                                                   varying lowp float  OUT_Clip;
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    if(OUT_Clip < 0.0)
        discard;
    
    gl_FragColor = OUT_Color;
}
);
