const char* ShaderDecalF = STRINGIFY(                                    
                                                    varying highp   vec3   OUT_Position;
                                                    uniform highp   vec3   EXT_Center;
                                                    uniform highp   float  EXT_Angle;
                                                    uniform lowp    vec4   EXT_Color;
                                                    uniform sampler2D EXT_TEXTURE_01;
                                                    uniform mediump mat3   EXT_MATRIX_TEXTURE;                                
void main(void)
{
    highp float fRadius = 2.0;
    highp vec3 UVector = vec3(1.0, 0.0, 0.0) / (fRadius);
    highp vec3 VVector = vec3(0.0, 0.0, 1.0) / (fRadius);
    highp vec2 vTexCoord;
    vTexCoord.x = dot(OUT_Position - EXT_Center, UVector);
    vTexCoord.y = dot(OUT_Position - EXT_Center, VVector);
    
    /*highp mat3 mRotationMatrix = mat3(cos(EXT_Angle), -sin(EXT_Angle), 0.0,
                                     sin(EXT_Angle),  cos(EXT_Angle), 0.0,
                                     0.0           ,  0.0           , 1.0);
    
    highp mat3 mTranslationMatrix = mat3(1.0, 0.0, 0.5,
                                        0.0, 1.0, 0.5,
                                        0.0, 0.0, 1.0);
    
    highp mat3 mScaleMatrix = mat3(0.5, 0.0, 0.0,
                                  0.0, 0.5, 0.0,
                                  0.0, 0.0, 1.0);*/
    
    highp vec3 vTransformTexCoord = vec3(vTexCoord.x, vTexCoord.y, 1.0);
    
    vTransformTexCoord = vTransformTexCoord * EXT_MATRIX_TEXTURE;
    lowp vec4 vColor = texture2D(EXT_TEXTURE_01, vTransformTexCoord.xy);
    gl_FragColor = vColor.a * EXT_Color;
}
);
