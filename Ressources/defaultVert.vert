#version 150

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 camera;

in vec3 vert;
in vec2 vertTexCoord;
in vec3 vertNormal;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main() {
    // Pass some variables to the fragment shader
    fragTexCoord = vertTexCoord;
    fragNormal = vertNormal;
    fragVert = vert;

    gl_Position =  projection * camera * transform * vec4(vert, 1);
}
