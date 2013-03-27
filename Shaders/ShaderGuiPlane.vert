const char* ShaderGuiPlaneV = STRING_SHADER(
                                       
                                       attribute vec3 IN_SLOT_Position;
                                       attribute vec2 IN_SLOT_TexCoord;
                                       attribute vec3 IN_SLOT_Normal;
                                       attribute vec4 IN_SLOT_Color;

                                       varying vec2   OUT_TexCoord;
                                       
                                       uniform mat4   EXT_MATRIX_Projection;
                                       uniform mat4   EXT_MATRIX_View;                                          
                                       uniform mat4   EXT_MATRIX_World;
                                       uniform vec2   EXT_VECTOR_Translation;
                                       
void main(void)
{
    OUT_TexCoord = IN_SLOT_TexCoord;
    gl_Position = vec4(vec3(IN_SLOT_Position.x + EXT_VECTOR_Translation.x, IN_SLOT_Position.y + EXT_VECTOR_Translation.y, IN_SLOT_Position.z), 1.0);
}
);
