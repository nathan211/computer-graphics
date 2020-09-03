uniform vec3 shade; 
varying float noise; 
void main() {
 gl_FragColor = vec4(shade * clamp(noise, 0.0, 1.0 ), 1.0 );
}