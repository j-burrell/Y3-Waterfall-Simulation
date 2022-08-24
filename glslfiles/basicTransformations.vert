#version 150

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

in  vec3 in_Position;  // Position coming in
in  vec3 in_Normal;    // vertex normal coming in
out vec3 ex_Normal;    // normal exiting to the fragment shader.

void main(void)
{
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(in_Position, 1.0);
	
	ex_Normal = NormalMatrix * in_Normal;
}