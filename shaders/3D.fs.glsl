#version 330

in vec3 vPosition;

out vec3 fFragColor;
uniform vec3 uColor;

void main() {
    fFragColor = uColor;
    gl_FragDepth = gl_FragCoord.z;
}