#version 400 core

// Layout of vertex attributes in VBO
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inCoord;

// Vertex colour output to fragment shader using Gouraud (interpolated)
out vec2 vTexCoord; // Texture coordinate

// Entry point
void main()
{
gl_Position = vec4(inPosition, 1.0);

vTexCoord = inCoord;
}