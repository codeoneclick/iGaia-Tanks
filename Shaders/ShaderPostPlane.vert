const char* ShaderPostPlaneV = STRINGIFY(
                                       
                                       attribute vec3 IN_SLOT_Position;
                                       attribute vec2 IN_SLOT_TexCoord;
                                       attribute vec3 IN_SLOT_Normal;
                                       attribute vec4 IN_SLOT_Color;
                                                                         
                                       varying vec2   OUT_TexCoord;
                                       
                                       uniform mat4   EXT_MATRIX_Projection;
                                       uniform mat4   EXT_MATRIX_View;                                          
                                       uniform mat4   EXT_MATRIX_World;
                                       
void main(void)
{
    OUT_TexCoord = IN_SLOT_TexCoord;
    gl_Position = vec4(IN_SLOT_Position, 1.0);
}
);
