#version 330 core

uniform mat4 depthMatrix;

layout(location = 0) in vec3 vertex_position;

void main() {

    gl_Position = depthMatrix * vec4(vertex_position, 1);
}