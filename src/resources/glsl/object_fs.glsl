#version 440

in vec4 vs_position;
in vec3 vs_color;
in vec3 vs_normal;

out vec4 gl_FragColor;

void main()
{
	float ambientStrength = 0.5;
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	vec3 lightPos = vec3(0.0, 0.0, 10.0);
	
	vec3 ambient = ambientStrength * lightColor;
  	
	// diffuse 
	vec3 norm = normalize(vs_normal);
	vec3 lightDir = normalize(lightPos - vs_color);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular lighting        
	float specularStrength = 0.5;
	vec3 viewDir = normalize(lightPos - vs_position.xyz);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  
        
   

	vec3 result = (ambient + diffuse + specular) * vs_color;
	gl_FragColor = vec4(result, 1.0);
}