#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 2) in vec2 aVertexTex;
layout(location = 3) in vec3 aVertexNormal;

out vec3 vFragPosition;
out vec2 vFragTex;
out vec3 vFragNormal;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

void main() {
    vFragPosition = aVertexPosition;
    vFragNormal = aVertexNormal;
    vFragTex = aVertexTex;

    vec4 vertexPos = vec4(aVertexPosition, 1);
    vFragPosition = vec3(uMVMatrix * vertexPos);

    gl_Position = uMVPMatrix * vertexPos;
}
