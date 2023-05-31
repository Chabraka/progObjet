#version 330

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec2 vFragTex;

out vec3 fFragTex;
uniform sampler2D uTexture;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

// void main() {
//     fFragTex = texture(uTexture, vFragTex.xy).xyz;
//     gl_FragDepth = gl_FragCoord.z;
// }

vec3 blinnPhong(){

    float d= distance(vFragPosition.xyz, uLightPos_vs);
	vec3 Li = uLightIntensity/(d*d);
    vec3 N = normalize(vFragNormal.xyz);
    vec3 w0 = normalize(-vFragPosition.xyz);
    vec3 wi = normalize(uLightPos_vs-vFragPosition.xyz);
    vec3 halfVector = (w0 + wi)/2.f;

    return Li*(uKd*dot(wi, N) + uKs* pow(dot(halfVector, N), uShininess));
}

void main(){
    fFragTex = texture(uTexture, vFragTex).xyz;
	fFragTex = blinnPhong();
    gl_FragDepth = gl_FragCoord.z;
	// fFragColor = vec3(normalize(vFragNormal)*0.8);
}