#version 400 core

uniform struct Matrices
{
	mat4 projMatrix;
	mat4 modelViewMatrix; 
	mat3 normalMatrix;
} matrices;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 inNormal;

out vec4 p;
out vec3 n;
out vec2 vTexCoord;
out float visibility;

void main(){
	gl_Position = matrices.projMatrix * matrices.modelViewMatrix * vec4(inPosition, 1.0);

	n = normalize(matrices.normalMatrix * inNormal);
	p = matrices.modelViewMatrix * vec4(inPosition, 1.f);

	vTexCoord = inCoord;

	float distanceC = length(p.xyz);
	visibility = exp(-0.00199 * distanceC);
	visibility = clamp(visibility, 0, 1);
}