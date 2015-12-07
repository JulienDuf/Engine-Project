#version 330 core

uniform sampler2D tex;
uniform sampler2D shadowMap;

uniform mat4 transform;

uniform struct Light {
    vec3 position;
    vec3 intensities;

}   directionalLight;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;
in vec4 shadowPosition;

out vec4 finalColor;

void main () {

    vec2 poissonDisk[4] = vec2[](
        vec2( -0.94201624, -0.39906216 ),
        vec2( 0.94558609, -0.76890725 ),
        vec2( -0.094184101, -0.92938870 ),
        vec2( 0.34495938, 0.29387760 ));

    vec3 normal = normalize(transpose(inverse(mat3(transform))) * fragNormal);
    vec4 surfaceColor = texture(tex, fragTexCoord);

    vec3 surfaceToLight = normalize(directionalLight.position.xyz);

    float surfaceShadow = texture(shadowMap, shadowPosition.xy).z;

    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));

    float bias = 0.005 * tan(acos(diffuseCoefficient));
    bias = clamp(bias, 0, 0.01);

    float visibility = 1.0;

    for (int i=0;i<4;i++){
        if ( texture( shadowMap, shadowPosition.xy + poissonDisk[i]/700.0 ).z  <  shadowPosition.z-bias ){
            visibility-=0.2;
        }
     }

   /* if (surfaceShadow < shadowPosition.z - bias)
        visibility = 0.5;*/

    vec3 diffuse = visibility * diffuseCoefficient * surfaceColor.rgb * directionalLight.intensities;

    finalColor = vec4(diffuse, surfaceColor.a);
}