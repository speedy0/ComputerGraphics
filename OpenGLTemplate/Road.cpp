#include "Road.h"
#define _USE_MATH_DEFINES
#include <math.h>



CRoad::CRoad()
{
	m_vertexCount = 0;
}

CRoad::~CRoad()
{
	//FreeGPU();
}

// Performs the calculation for CatmullRom spline.
glm::vec3 CRoad::Interpolate(glm::vec3& p0, glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	glm::vec3 a = p1;
	glm::vec3 b = 0.5f * (-p0 + p2);
	glm::vec3 c = 0.5f * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3);
	glm::vec3 d = 0.5f * (-p0 + 3.0f * p1 - 3.0f * p2 + p3);

	return a + b * t + c * t2 + d * t3;
}

//Sets control points and up vectors. 
void CRoad::SetCP()
{
	m_controlPoints.push_back(glm::vec3(-552, 1, -105));
	m_controlPoints.push_back(glm::vec3(-552, 1, 262));
	m_controlPoints.push_back(glm::vec3(-498, 1, 353));
	m_controlPoints.push_back(glm::vec3(-438, 1, 262));
	m_controlPoints.push_back(glm::vec3(-438, 1, -105));
	m_controlPoints.push_back(glm::vec3(-438, 1, -453));
	m_controlPoints.push_back(glm::vec3(-495, 1, -548));
	m_controlPoints.push_back(glm::vec3(-552, 1, -453));
}

// Determine lengths along the control points, which is the set of control points forming the closed curve
void CRoad::ComputeLengthsAlongControlPoints()
{
	int M = (int)m_controlPoints.size();

	float fAccumulatedLength = 0.0f;
	m_distances.push_back(fAccumulatedLength);
	for (int i = 1; i < M; i++) {
		fAccumulatedLength += glm::distance(m_controlPoints[i - 1], m_controlPoints[i]);
		m_distances.push_back(fAccumulatedLength);
	}

	// Get the distance from the last point to the first
	fAccumulatedLength += glm::distance(m_controlPoints[M - 1], m_controlPoints[0]);
	m_distances.push_back(fAccumulatedLength);
}

// Return the points and upvectors based on a distance d along the control polygon
bool CRoad::Sample(float d, glm::vec3& p, glm::vec3& up)
{
	if (d < 0)
		return false;

	int M = (int)m_controlPoints.size();
	if (M == 0)
		return false;


	float fTotalLength = m_distances[m_distances.size() - 1];

	// The the current length along the control polygon; handle the case where we've looped around the track
	float fLength = d - (int)(d / fTotalLength) * fTotalLength;

	// Find the current segment
	int j = -1;
	for (int i = 0; i < (int)m_distances.size() - 1; i++) {
		if (fLength >= m_distances[i] && fLength < m_distances[i + 1]) {
			j = i; // found it!
			break;
		}
	}

	if (j == -1)
		return false;

	// Interpolate on current segment -- get t
	float fSegmentLength = m_distances[j + 1] - m_distances[j];
	float t = (fLength - m_distances[j]) / fSegmentLength;

	// Get the indices of the four points along the control polygon for the current segment
	int iPrev = ((j - 1) + M) % M;
	int iCur = j;
	int iNext = (j + 1) % M;
	int iNextNext = (j + 2) % M;

	// Interpolate to get the point (and upvector)
	p = Interpolate(m_controlPoints[iPrev], m_controlPoints[iCur], m_controlPoints[iNext], m_controlPoints[iNextNext], t);
	if (m_controlUpVectors.size() == m_controlPoints.size())
		up = glm::normalize(Interpolate(m_controlUpVectors[iPrev], m_controlUpVectors[iCur], m_controlUpVectors[iNext], m_controlUpVectors[iNextNext], t));

	return true;
}


// Sample a set of control points using an open Catmull-Rom spline, to produce a set of iNumSamples that are (roughly) equally spaced
void CRoad::UniformlySampleControlPoints(int numSamples)
{
	glm::vec3 p, up;

	// Compute the lengths of each segment along the control polygon, and the total length
	ComputeLengthsAlongControlPoints();
	float fTotalLength = m_distances[m_distances.size() - 1];

	// The spacing will be based on the control polygon
	float fSpacing = fTotalLength / numSamples;

	// Call PointAt to sample the spline, to generate the points
	for (int i = 0; i < numSamples; i++) {
		Sample(i * fSpacing, p, up);
		m_centrelinePoints.push_back(p);
		if (m_controlUpVectors.size() > 0)
			m_centrelineUpVectors.push_back(up);

	}

	// Repeat once more for truly equidistant points
	m_controlPoints = m_centrelinePoints;
	m_controlUpVectors = m_centrelineUpVectors;
	m_centrelinePoints.clear();
	m_centrelineUpVectors.clear();
	m_distances.clear();
	ComputeLengthsAlongControlPoints();
	fTotalLength = m_distances[m_distances.size() - 1];
	fSpacing = fTotalLength / numSamples;
	for (int i = 0; i < numSamples; i++) {
		Sample(i * fSpacing, p, up);
		m_centrelinePoints.push_back(p);
		if (m_controlUpVectors.size() > 0)
			m_centrelineUpVectors.push_back(up);
	}
}


void CRoad::CreateCL()
{
	// Call Set Control Points
	SetCP();

	// Call UniformlySampleControlPoints with the number of samples required
	UniformlySampleControlPoints(50);

	// Create a VAO called m_vaoCentreline and a VBO to get the points onto the graphics card
	glGenVertexArrays(1, &m_vaoCentreline);
	glBindVertexArray(m_vaoCentreline);

	CVertexBufferObject vbo;
	vbo.Create();
	vbo.Bind();

	glm::vec2 texCoord1(0.5f, 0.5f);
	glm::vec2 texCoord2(0.5, 1.f);
	glm::vec3 normal(0, 1, 0);
	for (unsigned int i = 0; i < m_centrelinePoints.size(); i++) {
			vbo.AddData(&m_centrelinePoints[i], sizeof(glm::vec3));
			vbo.AddData(&texCoord2, sizeof(glm::vec2));
			vbo.AddData(&normal, sizeof(glm::vec3));
	}
	vbo.AddData(&m_centrelinePoints[0], sizeof(glm::vec3));
	vbo.AddData(&texCoord1, sizeof(glm::vec2));
	vbo.AddData(&normal, sizeof(glm::vec3));

	vbo.UploadDataToGPU(GL_STATIC_DRAW);
	//attribute locations
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
	//Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	//Up Vectors positions
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	//Texture coordinates:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec3)));
	//normal positions:
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CRoad::CreateOffsetCurves()
{
	// Compute the offset curves, one left, and one right.  Store the points in m_leftOffsetPoints and m_rightOffsetPoints respectively

	// Generate two VAOs called m_vaoLeftOffsetCurve and m_vaoRightOffsetCurve, each with a VBO, and get the offset curve points on the graphics card
	// Note it is possible to only use one VAO / VBO with all the points instead.

	//Left side:
	glGenVertexArrays(1, &m_vaoLeftOffsetCurve);
	glBindVertexArray(m_vaoLeftOffsetCurve);
	CVertexBufferObject lfvbo;
	lfvbo.Create();
	lfvbo.Bind();

	glm::vec2 Coords(0.f, 0.f);
	glm::vec3 Normal(0.f, 1.f, 0.f);

	for (unsigned i = 0; i < m_centrelinePoints.size(); i++) {
		glm::vec3 pNext;

		if (i != m_centrelinePoints.size() - 1) {
			pNext = m_centrelinePoints[i + 1];
		}
		else {
			pNext = m_centrelinePoints[0];
		}

		glm::vec3 T = glm::normalize(pNext - m_centrelinePoints[i]);
		glm::vec3 N = glm::normalize(glm::cross(T, glm::vec3(0, 1, 0)));
		glm::vec3 B = glm::normalize(glm::cross(N, T));

		float width = 75.f;
		glm::vec3 left = m_centrelinePoints[i] - (width / 2) * N;

		m_leftOffsetPoints.push_back(left);
			lfvbo.AddData(&m_leftOffsetPoints[i], sizeof(glm::vec3));
			lfvbo.AddData(&Coords, sizeof(glm::vec2));
			lfvbo.AddData(&Normal, sizeof(glm::vec3));
	}
	lfvbo.AddData(&m_leftOffsetPoints[0], sizeof(glm::vec3));
	lfvbo.AddData(&Coords, sizeof(glm::vec2));
	lfvbo.AddData(&Normal, sizeof(glm::vec3));

	lfvbo.UploadDataToGPU(GL_STATIC_DRAW);

	GLsizei Istride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);

	//vertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Istride, 0);
	//Textures:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Istride, (void*)sizeof(glm::vec3));
	//Normals:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Istride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	//Right Side:
	glGenVertexArrays(1, &m_vaoRightOffsetCurve);
	glBindVertexArray(m_vaoRightOffsetCurve);

	CVertexBufferObject rvbo;

	rvbo.Create();
	rvbo.Bind();

	glm::vec2 Rcoords = glm::vec2(0.f, 0.f);
	glm::vec3 Rnormal = glm::vec3(0.f, 1.f, 0.f);

	for (unsigned i = 0; i < m_centrelinePoints.size(); i++) {
		glm::vec3 pNext;

		if (i != m_centrelinePoints.size() - 1) {
			pNext = m_centrelinePoints[i + 1];
		}
		else {
			pNext = m_centrelinePoints[0];
		}

		glm::vec3 T = glm::normalize(pNext - m_centrelinePoints[i]);
		glm::vec3 N = glm::normalize(glm::cross(T, glm::vec3(0, 1, 0)));
		glm::vec3 B = glm::normalize(glm::cross(N, T));

		float width = 75.f;
		glm::vec3 right = m_centrelinePoints[i] + (width / 2) * N;

		m_rightOffsetPoints.push_back(right);

			rvbo.AddData(&m_rightOffsetPoints[i], sizeof(glm::vec3));
			rvbo.AddData(&Rcoords, sizeof(glm::vec2));
			rvbo.AddData(&Rnormal, sizeof(glm::vec3));
	}
	rvbo.AddData(&m_rightOffsetPoints[0], sizeof(glm::vec3));
	rvbo.AddData(&Rcoords, sizeof(glm::vec2));
	rvbo.AddData(&Rnormal, sizeof(glm::vec3));

	rvbo.UploadDataToGPU(GL_STATIC_DRAW);

	GLsizei rstride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
	//Vertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, rstride, 0);
	//Textures
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, rstride, (void*)sizeof(glm::vec3));
	//Normals:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, rstride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CRoad::RenderCL()
{
	// Bind the VAO m_vaoCentreline and render it
	glBindVertexArray(m_vaoCentreline);
	glDrawArrays(GL_POINTS, 0, m_centrelinePoints.size());
	//glDrawArrays(GL_LINE_LOOP, 0, m_centrelinePoints.size());

}

void CRoad::RenderOffsetCurves()
{
	// Bind the VAO m_vaoLeftOffsetCurve and render it
	glBindVertexArray(m_vaoLeftOffsetCurve);
	glDrawArrays(GL_LINE_STRIP, 0, m_leftOffsetPoints.size());

	// Bind the VAO m_vaoRightOffsetCurve and render it
	glBindVertexArray(m_vaoRightOffsetCurve);
	glDrawArrays(GL_LINE_STRIP, 0, m_rightOffsetPoints.size());
}

void CRoad::TRender(string directory, string filename)
{
	// Load the texture
	m_tex.Load(directory + filename, true);

	// Set parameters for texturing using sampler object
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void CRoad::CreateTrack()
{
	m_tex.Bind();
	// Generate a VAO called m_vaoTrack and a VBO to get the offset curve points and indices on the graphics card
	glGenVertexArrays(1, &m_vaoTrack);
	glBindVertexArray(m_vaoTrack);

	CVertexBufferObject trackvbo;
	trackvbo.Create();
	trackvbo.Bind();

	float textureRepeat = 1.f;

	glm::vec2 tCoord[4] =
	{
	glm::vec2(0.f, 0.f),
	glm::vec2(0.f, textureRepeat),
	glm::vec2(textureRepeat, 0.f),
	glm::vec2(textureRepeat, textureRepeat),
	};

	glm::vec3 normal(0.f, 1.f, 0.f);

	for (unsigned i = 0; i < m_centrelinePoints.size(); i++) {
			trackvbo.AddData(&m_leftOffsetPoints[i], sizeof(glm::vec3));
			trackvbo.AddData(&tCoord[i%2], sizeof(glm::vec2));
			trackvbo.AddData(&normal, sizeof(glm::vec3));
			trackvbo.AddData(&m_rightOffsetPoints[i], sizeof(glm::vec3));
			trackvbo.AddData(&tCoord[(i% 2) + 2], sizeof(glm::vec2));
			trackvbo.AddData(&normal, sizeof(glm::vec3));

			m_vertexCount += 2;
	}

	trackvbo.AddData(&m_leftOffsetPoints[0], sizeof(glm::vec3));
	trackvbo.AddData(&tCoord[0], sizeof(glm::vec2));
	trackvbo.AddData(&normal, sizeof(glm::vec3));
	trackvbo.AddData(&m_rightOffsetPoints[0], sizeof(glm::vec3));
	trackvbo.AddData(&tCoord[3], sizeof(glm::vec2));
	trackvbo.AddData(&normal, sizeof(glm::vec3));
	m_vertexCount += 2;

	trackvbo.UploadDataToGPU(GL_STATIC_DRAW);

	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);

	//Vertex Positions:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	//Texture Coordinates:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	//Normal Coordinates:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CRoad::RenderTrack()
{
	// Bind the VAO m_vaoTrack and render it
	glBindVertexArray(m_vaoTrack);
	m_tex.Bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexCount); //m_vertexCount); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int CRoad::CurrentLap(float d)
{

	return (int)(d / m_distances.back());

}

void CRoad::FreeGPU() {
	m_tex.Release();
	glDeleteVertexArrays(1, &m_vaoCentreline);
	glDeleteVertexArrays(1, &m_vaoLeftOffsetCurve);
	glDeleteVertexArrays(1, &m_vaoRightOffsetCurve);
	glDeleteVertexArrays(1, &m_vaoTrack);
}

glm::vec3 CRoad::_dummy_vector(0.0f, 0.0f, 0.0f);