const char* ShaderParticleV = STRINGIFY(
                                                    attribute vec3 IN_SLOT_Position;
                                                    attribute vec2 IN_SLOT_TexCoord;
                                                    attribute vec4 IN_SLOT_Color;
                                                                                     
                                                    varying vec2   OUT_TexCoord;
                                                    varying vec4   OUT_Color;
                                                    
                                                    uniform mat4   EXT_MATRIX_Projection;
                                                    uniform mat4   EXT_MATRIX_View;                                          
                                                    uniform mat4   EXT_MATRIX_World;
void main(void)
{
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    OUT_TexCoord = IN_SLOT_TexCoord;
    OUT_Color = IN_SLOT_Color / 127.0 - 1.0;
}
);
