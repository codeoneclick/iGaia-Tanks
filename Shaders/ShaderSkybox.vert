const char* ShaderSkyboxV = STRINGIFY(
                                                  attribute vec3 IN_SLOT_Position;
                                                  attribute vec2 IN_SLOT_TexCoord;
                                                  attribute vec3 IN_SLOT_Normal;
                                                                                   
                                                  varying vec2   OUT_TexCoord;
                                                  
                                                  uniform mat4   EXT_MATRIX_Projection;
                                                  uniform mat4   EXT_MATRIX_View;                                          
                                                  uniform mat4   EXT_MATRIX_World;
void main(void)
{
    OUT_TexCoord = IN_SLOT_TexCoord * 2.0;
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
}
);
