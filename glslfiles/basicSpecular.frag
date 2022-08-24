// Fragment Shader

#version 430

out vec4 out_Color;					 //colour for the pixel

uniform vec4 light_ambient;			 //ambient light 
uniform vec4 light_diffuse;          //diffuse property for the light
uniform vec4 light_specular;		 //specular property for the light

uniform vec4 material_ambient;       //ambient property for material
uniform vec4 material_diffuse;       //diffuse property for the material
uniform vec4 material_specular;      //specular property for the material
uniform float material_shininess;    //shininess exponent for specular highlight

in vec3 ex_LightPos;                 //light direction arriving from the vertex
in vec3 ex_Normal;                   //normal arriving from the vertex
in vec3 ex_PositionEye;

void main(void)
{
	// Ambient element.
	vec4 color = light_ambient * material_ambient;

	vec3 n, L;
	float NdotL;
	
	n = normalize(ex_Normal);
	L = normalize(ex_LightPos - ex_PositionEye);

	vec3 v = normalize(-ex_PositionEye);
	vec3 r = normalize(-reflect(L, n));
	
	float RdotV = max(0.0, dot(r, v));

	NdotL = max(dot(n, L),0.0);

	if(NdotL > 0.0)
	{
		color += (light_diffuse * material_diffuse * NdotL);	//Diffuse element.
		color += light_specular * material_specular * pow(RdotV, material_shininess);//Specular element.
	}
	
	out_Color = color;
}