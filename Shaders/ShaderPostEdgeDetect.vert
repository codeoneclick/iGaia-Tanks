const char* ShaderPostEdgeDetectV = STRINGIFY(
                                                   
                                                   attribute vec3 IN_SLOT_Position;
                                                   attribute vec2 IN_SLOT_TexCoord;
                                                                                        
                                                   varying vec2   OUT_TexCoord;
                                                   varying vec4   OUT_TexCoord_01;
                                                   varying vec4   OUT_TexCoord_02;
                                                   varying vec4   OUT_TexCoord_03;
                                                   varying vec4   OUT_TexCoord_04;
                                       
void main(void)
{
    OUT_TexCoord = IN_SLOT_TexCoord;
    
    highp vec2 vEdgeOffset = vec2(1.0 / 480.0, 1.0 / 320.0);
    OUT_TexCoord_01.xy = IN_SLOT_TexCoord + vec2(-1.0, -1.0) * vEdgeOffset;
    OUT_TexCoord_01.zw = IN_SLOT_TexCoord + vec2( 1.0,  1.0) * vEdgeOffset;
    OUT_TexCoord_02.xy = IN_SLOT_TexCoord + vec2(-1.0,  1.0) * vEdgeOffset;
    OUT_TexCoord_02.zw = IN_SLOT_TexCoord + vec2( 1.0, -1.0) * vEdgeOffset;
    OUT_TexCoord = IN_SLOT_TexCoord;
    
    gl_Position = vec4(IN_SLOT_Position, 1.0);
}
);
