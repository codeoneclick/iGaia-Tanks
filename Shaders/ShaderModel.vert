const char* ShaderModelV = STRINGIFY(
                                                    attribute vec3 IN_SLOT_Position;
                                                    attribute vec2 IN_SLOT_TexCoord;
                                                    attribute vec4 IN_SLOT_Normal;
                                                    attribute vec4 IN_SLOT_Tangent;
                                                    
                                                    varying vec3   OUT_Light;
                                                    varying vec3   OUT_Normal;                                     
                                                    varying vec2   OUT_TexCoord;
                                                    
                                                    uniform vec3   EXT_Light;
                                                    uniform vec2   EXT_Texcoord_Offset;
                                                    
                                                    uniform mat4   EXT_MATRIX_Projection;
                                                    uniform mat4   EXT_MATRIX_View;                                          
                                                    uniform mat4   EXT_MATRIX_World;
void main(void)
{
    vec4 vPosition = EXT_MATRIX_World * vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_Projection * EXT_MATRIX_View * vPosition;
    
    OUT_Normal = IN_SLOT_Normal.xyz / 127.0 - 1.0;

    OUT_Light = normalize(EXT_Light - vec3(vPosition));
    OUT_TexCoord = vec2(IN_SLOT_TexCoord.x + EXT_Texcoord_Offset.x, IN_SLOT_TexCoord.y + EXT_Texcoord_Offset.y);
}
);
