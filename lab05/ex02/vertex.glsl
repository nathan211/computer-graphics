varying vec3 normal; 
void main() {
 normal = normalize(gl_NormalMatrix * gl_Normal);
 gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}