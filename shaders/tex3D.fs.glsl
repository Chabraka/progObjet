#version 330

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec2 vFragTex;

out vec3 fFragTex;
uniform sampler2D uTexture;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uSunPosition;
uniform vec3 uSunIntensity;

uniform vec3 uWalkerPosition;
uniform vec3 uWalkerIntensity;

// void main() {
//     fFragTex = texture(uTexture, vFragTex.xy).xyz;
//     gl_FragDepth = gl_FragCoord.z;
// }

vec3 blinnPhong(vec3 lightPos, vec3 lightIntensity){

    float d= distance(vFragPosition.xyz, lightPos);
	vec3 Li = lightIntensity/(d*d);
    vec3 N = normalize(vFragNormal.xyz);
    vec3 w0 = normalize(-vFragPosition.xyz);
    vec3 wi = normalize(lightPos-vFragPosition.xyz);
    vec3 halfVector = (w0 + wi)/2.f;

	// return N;

	// return d*uKd*dot(wi, N) + uKs* pow(dot(halfVector, N), uShininess);

    //return Li*(uKd*dot(wi, N) + uKs* pow(dot(halfVector, N), uShininess));

    return 0.2 + max(Li*(uKd*dot(wi, N) + uKs* pow(dot(halfVector, N), uShininess)), 0.0) * 0.8;
}

void main(){
    fFragTex = texture(uTexture, vFragTex).xyz;
	fFragTex *= (blinnPhong(uSunPosition, uSunIntensity) + blinnPhong(uWalkerPosition, uWalkerIntensity));
    gl_FragDepth = gl_FragCoord.z;
	// fFragColor = vec3(normalize(vFragNormal)*0.8);
}