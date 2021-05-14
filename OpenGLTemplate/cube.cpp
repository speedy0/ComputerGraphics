#include "cube.h"

CCube::CCube() {}
CCube::~CCube() 
{
	Release();
}

void CCube::Create(string file1, string file2, float size) {
	m_text1.Load(file1);
	m_text1.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	m_text1.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_text1.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_text1.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	m_text2.Load(file2);
	m_text2.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	m_text2.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_text2.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_text2.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	m_vbo.Create();
	m_vbo.Bind();
	
	glm::vec3 CubeVertices[24] = {
		// Front face
		glm::vec3(size, size, size), glm::vec3(size, -size, size), glm::vec3(-size, size, size), glm::vec3(-size, -size, size),
		// Back face
		glm::vec3(-size, size, -size), glm::vec3(-size, -size, -size), glm::vec3(size, size, -size), glm::vec3(size, -size, -size),
		// Left face
		glm::vec3(-size, size, size), glm::vec3(-size, -size, size), glm::vec3(-size, size, -size), glm::vec3(-size, -size, -size),
		// Right face
		glm::vec3(size, size, -size), glm::vec3(size, -size, -size), glm::vec3(size, size, size), glm::vec3(size, -size, size),
		// Top face
		glm::vec3(-size, size, -size), glm::vec3(size, size, -size), glm::vec3(-size, size, size), glm::vec3(size, size, size),
		// Bottom face
		glm::vec3(size, -size, -size), glm::vec3(-size, -size, -size), glm::vec3(size, -size, size), glm::vec3(-size, -size, size),
	};
	
	glm::vec2 TexCoords[4] = {
		glm::vec2(0.f, 1.f), glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f)
	};

	glm::vec3 Normals[6] = {
	glm::vec3(0, 0, 1), //Front side
	glm::vec3(0, 0, -1), //Back side
	glm::vec3(1, 0, 0), //Left side
	glm::vec3(-1, 0, 0), //Right side
	glm::vec3(0, -1, 0), //Top side
	glm::vec3(0, -1, 0) //Bottom side
	};
	
	for (unsigned i = 0; i < 24; i++) {
		m_vbo.AddData(&CubeVertices[i], sizeof(glm::vec3));
		m_vbo.AddData(&TexCoords[i % 4], sizeof(glm::vec2));
		m_vbo.AddData(&Normals[i / 4], sizeof(glm::vec3));
	}

	//Upload the data to GPU
	m_vbo.UploadDataToGPU(GL_STATIC_DRAW);
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);

	//Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	//Texture coordinates:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	//Normal Vectors:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CCube::Render()
{
	glDisable(GL_CULL_FACE);
	glBindVertexArray(m_vao);
	for (unsigned i = 0; i < 6; i++) {
		if (i == 0) {
			m_text2.Bind();
			glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
		}
		else {
			m_text1.Bind();
			glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
		}
	}
}

void CCube::Release() {
	m_text1.Release();
	m_text2.Release();
	glDeleteVertexArrays(1, &m_vao);
	m_vbo.Release();
}