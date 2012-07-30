const char* ShaderPostBlurV = STRINGIFY(
                                                   
                                                   attribute vec3 IN_SLOT_Position;
                                                   attribute vec2 IN_SLOT_TexCoord;
                                                   attribute vec3 IN_SLOT_Normal;
                                                   
                                                   varying vec3   OUT_View;
                                                   varying vec3   OUT_Light;
                                                   varying vec3   OUT_Normal;                                     
                                                   varying vec2   OUT_TexCoord;
                                                   
                                                   uniform vec3   EXT_View;
                                                   uniform vec3   EXT_Light;
                                                   
                                                   uniform mat4   EXT_MATRIX_Projection;
                                                   uniform mat4   EXT_MATRIX_View;                                          
                                                   uniform mat4   EXT_MATRIX_World;
                                       
void main(void)
{
    OUT_TexCoord = IN_SLOT_TexCoord;
    gl_Position = vec4(IN_SLOT_Position, 1.0);
}
);
