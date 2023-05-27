#version 330

in vec3 vFragTex;

out vec3 fFragTex;
uniform sampler2D uTexture;

void main() {
    fFragTex = texture(uTexture, vFragTex.xy).xyz;
    gl_FragDepth = gl_FragCoord.z;
}
