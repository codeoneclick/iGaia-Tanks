const char* ShaderPostEdgeDetectF = STRINGIFY(                                    
                                                   varying highp vec2   OUT_TexCoord;
                                                   varying highp vec4   OUT_TexCoord_01;
                                                   varying highp vec4   OUT_TexCoord_02;
                                                   varying highp vec4   OUT_TexCoord_03;
                                                   varying highp vec4   OUT_TexCoord_04;

                                                   uniform sampler2D EXT_TEXTURE_01;
                                                   uniform sampler2D EXT_TEXTURE_02;
                                                   uniform sampler2D EXT_TEXTURE_03;
                                                   uniform sampler2D EXT_TEXTURE_04;
                                       
void main(void)
{
    lowp float fEdgeAmount = 0.0;
    lowp vec4 vExludeColor = texture2D(EXT_TEXTURE_02, OUT_TexCoord);
    if(vExludeColor.r == 1.0 && vExludeColor.g == 0.0 && vExludeColor.b == 0.0)
    {
        fEdgeAmount = 0.0;
    }
    else
    {
        lowp vec4 n1 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.xy);
        lowp vec4 n2 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_01.zw);
        lowp vec4 n3 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.xy);
        lowp vec4 n4 = texture2D(EXT_TEXTURE_02, OUT_TexCoord_02.zw);

        lowp vec4 vDelta = abs(n1 - n2) + abs(n3 - n4);
        fEdgeAmount = clamp(dot(vDelta.xyz, vec3(1.0)), 0.0, 1.0);
    }
    
    gl_FragColor = mix(texture2D(EXT_TEXTURE_01, OUT_TexCoord), vec4(0.1, 0.1, 0.1, 1.0), fEdgeAmount);
}
);
