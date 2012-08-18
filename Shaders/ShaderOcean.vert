const char* ShaderOceanV = STRINGIFY(
                                              
                                              attribute vec3 IN_SLOT_Position;
                                              attribute vec2 IN_SLOT_TexCoord;
                                              
                                              varying vec4   OUT_TexCoordProj;
                                              varying vec2   OUT_TexCoord;
                                              varying vec2   OUT_TexCoord_Anim_01;
                                              varying vec2   OUT_TexCoord_Anim_02;
                                              
                                              uniform float  EXT_Timer;
                                     
                                              uniform mat4   EXT_MATRIX_Projection;
                                              uniform mat4   EXT_MATRIX_View;                                          
                                              uniform mat4   EXT_MATRIX_World;
                                              uniform mat4   EXT_MATRIX_WVP;
                                    
void main(void)
{
    gl_Position = EXT_MATRIX_WVP * vec4(IN_SLOT_Position, 1.0);
    OUT_TexCoord = IN_SLOT_TexCoord;
    
    OUT_TexCoord_Anim_01 = vec2(IN_SLOT_TexCoord.x * 8.0 + sin(EXT_Timer) * 0.33,
								   IN_SLOT_TexCoord.y * 8.0 + cos(EXT_Timer) * 0.66);
	
	OUT_TexCoord_Anim_02 = vec2(IN_SLOT_TexCoord.x * 8.0 - sin(EXT_Timer) * 0.75,
								   IN_SLOT_TexCoord.y * 8.0 - cos(EXT_Timer) * 0.25);
    
    OUT_TexCoordProj = gl_Position;
}
);
