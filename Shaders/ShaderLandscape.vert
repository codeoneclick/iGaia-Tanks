const char* ShaderLandscapeV = STRINGIFY(
                                                    
                                        attribute vec3 IN_SLOT_Position;
                                        attribute vec2 IN_SLOT_TexCoord;
                                        attribute vec4 IN_SLOT_Normal;
                                        attribute vec4 IN_SLOT_Tangent;
                                                    
                                        varying vec3   OUT_Light;                                  
                                        varying vec2   OUT_TexCoord;
                                        varying float  OUT_Clip;
                                                   
                                        uniform vec3   EXT_View;
                                        uniform vec3   EXT_Light;
                                        uniform vec4   EXT_Clip_Plane;
                                                    
                                        uniform mat4   EXT_MATRIX_Projection;
                                        uniform mat4   EXT_MATRIX_View;                                          
                                        uniform mat4   EXT_MATRIX_World;
                                        uniform mat4   EXT_MATRIX_WVP;
                                       
void main(void)
{
    vec4 vPosition = vec4(IN_SLOT_Position, 1.0);
    gl_Position = EXT_MATRIX_WVP * vPosition;
    
    vec3 vNormal = IN_SLOT_Normal.xyz / 127.0 - 1.0;
    vec3 vTangent = IN_SLOT_Tangent.xyz / 127.0 - 1.0;
    vec3 vBinormal = cross(vNormal, vTangent);
    
    mat3 mTangentSpace = mat3(vTangent.x, vBinormal.x, vNormal.x,
                              vTangent.y, vBinormal.y, vNormal.y,
                              vTangent.z, vBinormal.z, vNormal.z);

    vec3 vLightDirection = vec3(vPosition) - EXT_Light;
    OUT_Light = normalize(mTangentSpace * vLightDirection);
    
    OUT_TexCoord = IN_SLOT_TexCoord;
    OUT_Clip = dot(vPosition.xyz, EXT_Clip_Plane.xyz) + EXT_Clip_Plane.w;
}
);
