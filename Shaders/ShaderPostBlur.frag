const char* ShaderPostBlurF = STRINGIFY(

                                                   varying mediump vec3   OUT_View;
                                                   varying mediump vec3   OUT_Light;
                                                   varying mediump vec3   OUT_Normal;                                     
                                                   varying mediump vec2   OUT_TexCoord;
                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    mediump float fBlurDistance = 0.003;
    mediump vec4 vColor;
	vColor  = texture2D(EXT_TEXTURE_01, vec2(OUT_TexCoord.x + fBlurDistance, OUT_TexCoord.y + fBlurDistance));
	vColor += texture2D(EXT_TEXTURE_01, vec2(OUT_TexCoord.x - fBlurDistance, OUT_TexCoord.y - fBlurDistance));
	vColor += texture2D(EXT_TEXTURE_01, vec2(OUT_TexCoord.x + fBlurDistance, OUT_TexCoord.y - fBlurDistance));
	vColor += texture2D(EXT_TEXTURE_01, vec2(OUT_TexCoord.x - fBlurDistance, OUT_TexCoord.y + fBlurDistance));

    vColor = vColor / 4.0; 
    gl_FragColor = vColor;
}
);
