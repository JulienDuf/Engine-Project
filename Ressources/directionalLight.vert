#version 330 core

uniform mat4 MVPMatrix; // Model, View and projection (a.k.a Transformation, Camera and Projection)
uniform mat4 biasMVPMatrix; // MVP Matrix with the bias Matrix.

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec4 shadowPosition;

void main () {

    gl_Position = MVPMatrix * vec4(vertexPosition, 1);

    fragTexCoord = vertexTexCoord;
    fragNormal = vertexNormal;
    fragVert = vertexPosition;

    shadowPosition = biasMVPMatrix * vec4(vertexPosition, 1);
}