const char* ShaderLandscapeNDV = STRINGIFY(  
                                              
                                              attribute vec3 IN_SLOT_Position;
                                              attribute vec2 IN_SLOT_TexCoord;
                                              attribute vec4 IN_SLOT_Normal;
                                              attribute vec4 IN_SLOT_Tangent;
                                               
                                              varying float  OUT_Clip;
                                              uniform vec4   EXT_Clip_Plane;
                                              
                                              varying vec4   OUT_Color;
                                              
                                              uniform mat4   EXT_MATRIX_Projection;
                                              uniform mat4   EXT_MATRIX_View;                                          
                                              uniform mat4   EXT_MATRIX_World;
                                              uniform mat4   EXT_MATRIX_MVP;
                                       
void main(void)
{
    vec4 vWorldPosition = vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_MVP * vWorldPosition;
    
    vec3 vNormal = IN_SLOT_Normal.xyz / 127.0 - 1.0;
    
    vNormal = normalize(mat3(EXT_MATRIX_World) * vNormal);
    OUT_Color.rgb = (vNormal + 1.0) / 2.0;
    OUT_Color.a = 1.0;
    OUT_Clip = dot(vWorldPosition.xyz, EXT_Clip_Plane.xyz) + EXT_Clip_Plane.w;
}
);
