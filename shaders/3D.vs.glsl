#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;
//layout(location = 1) in vec3 aVertexTex;

out vec3 vFragPosition;
out vec3 vFragColor;
// out vec3 vFragTex;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

void main() {
    vFragColor = aVertexColor;
    // vFragPosition = aVertexPosition;
    // vFragTex = aVertexTex;

    vec4 vertexPos = vec4(aVertexPosition, 1);
    vFragPosition = vec3(uMVMatrix * vertexPos);

    gl_Position = uMVPMatrix * vertexPos;
}
