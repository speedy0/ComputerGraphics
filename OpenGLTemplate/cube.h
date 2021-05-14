#pragma once
#include "Common.h"
#include  "Texture.h"
#include "VertexBufferObject.h"

class CCube {
public:
	CCube();
	~CCube();
	
	void Create(string file1, string file2, float size);
	void Render();
	void Release();
private:
	GLuint m_vao;
	CVertexBufferObject m_vbo;
	CTexture m_text1;
	CTexture m_text2;
};