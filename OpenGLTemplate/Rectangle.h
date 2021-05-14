#pragma once
#include "Common.h"
#include  "Texture.h"
#include "VertexBufferObject.h"

class GGrassPatch {
public:
	GGrassPatch();
	~GGrassPatch();

	void Create(string file1, string file2, float width, float height, float volume);
	void Render();
	void Release();
private:
	GLuint m_vao;
	CVertexBufferObject m_vbo;
	CTexture m_text1;
	CTexture m_text2;
}; 
