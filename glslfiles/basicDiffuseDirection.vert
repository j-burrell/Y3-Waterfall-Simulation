#version 430

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;  //inverse transpose of the 3x3 bit of modelview matrix
uniform vec4 LightDir;  // light position

in  vec3 in_Position;  // Position coming in
in  vec3 in_Normal;    // vertex normal used for lighting
out vec3 ex_Normal;    // exiting normal transformed by the normal matrix

out vec3 ex_LightDir; //light direction vector in eye space (assuming it doesn't undergo other transformations)

void main(void)
{
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(in_Position, 1.0);
	
	ex_Normal = NormalMatrix*in_Normal; 

	ex_LightDir = vec3(ViewMatrix*LightDir);
}