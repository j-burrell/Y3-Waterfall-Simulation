#version 430

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;  //inverse transpose of the 3x3 bit of modelview matrix
uniform vec4 SpotLightPos;  // light position
uniform vec4 SpotLightDir;  //light direction

in  vec3 in_Position;  // Position coming in
in  vec3 in_Normal;    // vertex normal used for lighting
out vec3 ex_Normal;    // exiting normal transformed by the normal matrix

out vec3 ex_SpotLightDir; //light direction vector
out vec3 ex_SpotLightPos; //light position vector
out vec3 ex_PositionEye; //vertex position in eye space (i.e. after ModelView but not projection)

void main(void)
{
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(in_Position, 1.0);
	
	ex_Normal = NormalMatrix*in_Normal; 

	ex_PositionEye = vec3((ModelViewMatrix * vec4(in_Position, 1.0)));

	ex_SpotLightPos = vec3(ViewMatrix*SpotLightPos);
	ex_SpotLightDir = vec3(ViewMatrix*SpotLightDir);
}
