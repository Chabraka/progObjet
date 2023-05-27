#version 330 core

in vec4 vFragPosition;
in vec4 vFragNormal;
in vec2 vFragTexCoord;

out vec3 fFragColor;

// uniform sampler2D uTexture0;
// uniform sampler2D uTexture1;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(){
	// vec3 wi = normalize(uLightDir_vs);
	// vec3 w0 =normalize(-vFragPosition.xyz);
	// return uLightIntensity*(uKd*(dot(vFragNormal.xyz, wi))+uKs*pow(dot(wi, w0), uShininess));

	vec3 Li = uLightIntensity;
    vec3 N = normalize(vFragNormal.xyz);
    vec3 w0 = normalize(-vFragPosition.xyz);
    vec3 wi = normalize(uLightDir_vs);
    vec3 halfVector = (w0 + wi)/2.f;

    return Li*(uKd*dot(wi, N) + uKs* pow(dot(halfVector, N), uShininess));
}

void main(){
	fFragColor = blinnPhong();
	// fFragColor = vec3(normalize(vFragNormal)*0.8);
}
