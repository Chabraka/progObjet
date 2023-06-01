#version 330 core

in vec4 vFragPosition;
in vec4 vFragNormal;
in vec2 vFragTexCoord;

out vec3 fFragColor;


uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 sunPosition;
uniform vec3 uLightIntensity;

vec3 blinnPhong(){

    float d= distance(vFragPosition.xyz, sunPosition);
	vec3 Li = uLightIntensity/(d*d);
    vec3 N = normalize(vFragNormal.xyz);
    vec3 w0 = normalize(-vFragPosition.xyz);
    vec3 wi = normalize(sunPosition-vFragPosition.xyz);
    vec3 halfVector = (w0 + wi)/2.f;

    return Li*(uKd*dot(wi, N) + uKs* pow(dot(halfVector, N), uShininess));
}

void main(){
	fFragColor = blinnPhong();
	// fFragColor = vec3(normalize(vFragNormal)*0.8);
}
