// Fragment Shader

#version 430

out vec4 out_Color;            //colour for the pixel

uniform vec4 light_ambient;    //ambient light 
uniform vec4 light_diffuse;    //diffuse property for the light

uniform vec4 material_ambient; //ambient property for material
uniform vec4 material_diffuse; //diffuse property for the material

uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;

in vec3 ex_LightPos;  //light direction arriving from the vertex
in  vec3 ex_Normal;  //normal arriving from the vertex
in vec3 ex_PositionEye;

void main(void)
{
	float dist,att;

	vec4 color = light_ambient * material_ambient;

	vec3 n, L;
	float NdotL;
	
	dist = length(ex_LightPos - ex_PositionEye);
	n = normalize(ex_Normal);
	L = normalize(ex_LightPos - ex_PositionEye);


	NdotL = max(dot(n, L),0.0);
	
	
	if(NdotL > 0.0)
	{
		att = min(1.0 / (constantAttenuation +
                linearAttenuation * dist +
                quadraticAttenuation * dist * dist),1);
		//att = 1.0;

		color += att*(light_diffuse * material_diffuse * NdotL);
	}

	//out_Color = color;

	//Distance Attenuation / Fog
	float fogStart = -10.0;
	float fogEnd = -70.0;
	float fogFactor = (fogEnd-ex_PositionEye.z)/(fogEnd-fogStart);
	fogFactor = clamp(fogFactor,0.0,1.0);
	vec4 fogColor = vec4(1.0,0.0,0.0,1.0);
	out_Color = mix(fogColor,color, fogFactor);
}