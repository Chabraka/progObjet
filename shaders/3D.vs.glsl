#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

// out vec3 vFragPosition;
out vec3 vPosition;
out vec3 vFragColor;

// uniform mat4 uModelMatrix;
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

void main() {
    vFragColor = aVertexColor;
    // vFragPosition = aVertexPosition;

    vec4 vertexPos = vec4(aVertexPosition, 1);
    vPosition = vec3(uMVMatrix * vertexPos);

    //gl_Position = vec4((uModelMatrix * vec4(aVertexPosition,1)).xyz, 1);
    gl_Position = uMVPMatrix * vertexPos;
}
