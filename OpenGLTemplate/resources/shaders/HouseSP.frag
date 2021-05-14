#version 400 core

out vec4 vOutputColour;
in vec4 p;
in vec3 n;
in vec2 vTexCoord;
in float visibility;
vec3 fogC = vec3(0.5f, 0.5f, 0.5f);

struct Light{
vec4 Lposition;
vec3 Lambient;
vec3 Ldiffuse;
vec3 Lspecular;
vec3 Ldirection;

float Exp;
float Cutoff;
};

struct Material
{
	vec3 Mambient;
	vec3 Mdiffuse;
	vec3 Mspecular;
	float Mshininess;
};

uniform Light spotlight1;
uniform Light spotlight2;
uniform Light spotlight3;
uniform Light spotlight4;
uniform Light spotlight5;
uniform Light spotlight11;
uniform Material material2;
uniform sampler2D sampler0; 
uniform bool bUseTexture; 
uniform bool fog;

vec3 BPSLM(Light spotlight, vec4 p, vec3 n){
vec3 s = normalize(vec3(spotlight.Lposition - p));
float angle = acos(dot(-s, spotlight.Ldirection));
float cutoff = radians(clamp(spotlight.Cutoff, 0.f, 1.f));
vec3 ambient = spotlight.Lambient * material2.Mambient;

if (angle < cutoff){
float SpotFactor = pow(dot(-s, spotlight.Ldirection), spotlight.Exp);
vec3 v = normalize(-p.xyz);
vec3 h = normalize(v + s);
float sDotN = max(dot(s, n), 0.f);
vec3 diffuse = spotlight.Ldiffuse * material2.Mdiffuse * sDotN;
vec3 specular = vec3(0.f);
	if(sDotN > 0.f){
	specular = spotlight.Lspecular * material2.Mspecular * pow(max(dot(h, n), 0.f), material2.Mshininess);
	}

return ambient + SpotFactor * (diffuse * specular);
}
else
	return ambient;
}

void main(){
	
	vec3 vtColour = BPSLM(spotlight1, p, normalize(n)) + BPSLM(spotlight2, p, normalize(n)) + BPSLM(spotlight3, p, normalize(n)) + BPSLM(spotlight4, p, normalize(n)) + BPSLM(spotlight5, p, normalize(n))+ BPSLM(spotlight11, p, normalize(n));

// Get the texel colour from the texture sampler
		vec4 vTexColour = texture(sampler0, vTexCoord);	

		if (bUseTexture)
			vOutputColour = vTexColour*vec4(vtColour, 1.0f);	
		else
			vOutputColour = vec4(vtColour, 1.0f);

		if(fog)
			vOutputColour = mix(vec4(fogC, 1.0), vOutputColour, visibility);
}