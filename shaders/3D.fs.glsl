#version 330

in vec3 vFragTex;

// out vec3 fFragTex;
out vec3 fFragColor;
uniform vec3 uColor;
// uniform sampler2D uTexture;

void main() {
    // fFragTex = vFragTex;
    fFragColor = uColor;
    // fFragTex = texture(uTexture, vFragTex.xy).xyz;
    gl_FragDepth = gl_FragCoord.z;
}
