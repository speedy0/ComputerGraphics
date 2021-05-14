#pragma once
#include "Common.h"
#include  "Texture.h"
#include "VertexBufferObject.h"

class CPentahedron {
public:
	CPentahedron();
	~CPentahedron();

	void Create(string file, float size);
	void Render();
	void Release();
private:
	GLuint m_vao;
	CVertexBufferObject m_vbo;
	CTexture m_text;
};