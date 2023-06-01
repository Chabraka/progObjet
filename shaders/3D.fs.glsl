#version 330

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec3 vFragTex;

out vec3 fFragColor;
uniform vec3 uColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

void main() {
    fFragColor = uColor;
    gl_FragDepth = gl_FragCoord.z;
}
