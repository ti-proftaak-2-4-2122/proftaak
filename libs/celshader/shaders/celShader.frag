#version 330

in vec3 position;
in vec4 color;
in vec3 normal;

uniform vec3 lightPosition = vec3(1.0);

uniform bool useColor = false;
uniform bool useColorMult = false;
uniform vec4 colorMult = vec4(1.0);

void main()
{
	vec4 out_color = vec4(1.0);
	if(useColor)
		out_color *= color;
	if(useColorMult)
		out_color *= colorMult;

	vec3 nn = normalize(normal);
	vec3 light_dir = normalize(position - lightPosition);
	vec3 eye_dir = normalize(-position);
	vec3 reflect_dir = normalize(reflect(light_dir, nn));

	float spec = max(dot(reflect_dir, eye_dir), 0.0);
	float diffuse = max(dot(-light_dir, nn), 0.0);

	float intensity = 0.6 * diffuse + 0.4 * spec;

	if (intensity > 0.9) {
		intensity = 1.1;
	}
	else if (intensity > 0.5) {
		intensity = 0.7;
	}
	else {
		intensity = 0.5;
	}

	gl_FragColor = out_color * intensity;
}