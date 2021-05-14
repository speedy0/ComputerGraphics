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

uniform Light spotlight6;
uniform Material material3;
uniform sampler2D sampler0; 
uniform bool bUseTexture; 
uniform bool fog;
uniform bool Dynamic;
uniform bool discarding;
uniform float t;
vec3 vtColour;

vec3 BPSLM(Light spotlight, vec4 p, vec3 n){
vec3 s = normalize(vec3(spotlight.Lposition - p));
float angle = acos(dot(-s, spotlight.Ldirection));
float cutoff = radians(clamp(spotlight.Cutoff, 0.f, 1.f));
vec3 ambient = spotlight.Lambient * material3.Mambient;

if (angle < cutoff){
float SpotFactor = pow(dot(-s, spotlight.Ldirection), spotlight.Exp);
vec3 v = normalize(-p.xyz);
vec3 h = normalize(v + s);
float sDotN = max(dot(s, n), 0.f);
vec3 diffuse = spotlight.Ldiffuse * material3.Mdiffuse * sDotN;
vec3 specular = vec3(0.f);
	if(sDotN > 0.f){
	specular = spotlight.Lspecular * material3.Mspecular * pow(max(dot(h, n), 0.f), material3.Mshininess);
	}

return ambient + SpotFactor * (diffuse * specular);
}
else
	return ambient;
}

void main(){

	if(Dynamic == true){
		vtColour = BPSLM(spotlight6, p, normalize(n)) * (0.5 + 0.5*sin(t));
	}
	else{
		vtColour = BPSLM(spotlight6, p, normalize(n));
	}
	

// Get the texel colour from the texture sampler
		vec4 vTexColour = texture(sampler0, vTexCoord);

		if(discarding){
			if(vTexColour.r < fract(t/15))
				discard;
		}

		if (bUseTexture)
			vOutputColour = vTexColour*vec4(vtColour, 1.0f);	
		else
			vOutputColour = vec4(vtColour, 1.0f);

		if(fog)
			vOutputColour = mix(vec4(fogC, 1.0), vOutputColour, visibility);
}