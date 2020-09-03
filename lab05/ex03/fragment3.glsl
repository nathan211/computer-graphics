uniform vec3 lightPosition; 
uniform vec3 ambientColor; 
uniform vec3 diffuseColor; 
uniform vec3 specularColor; 
uniform float Ka; 
uniform float Kd; 
uniform float Ks; 
uniform float shininess; 
varying vec3 N; 
varying vec3 v; 
void main (void) {
 vec3 L = normalize(lightPosition.xyz - v); 
 vec3 E = normalize(-v); 
 vec3 R = normalize(-reflect(L,N)); 
 vec4 Iamb = vec4(ambientColor, 1.0);
 vec4 Idiff = vec4(diffuseColor * max(dot(N, L), 0.0), 1.0);
 vec4 Ispec = vec4(specularColor * pow(max(dot(R, E),0.0), shininess);
 gl_FragColor = Ka * Iamb + Kd * Idiff + Ks * Ispec;
}