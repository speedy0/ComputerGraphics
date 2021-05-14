#include "CatmullRom.h"
#define _USE_MATH_DEFINES
#include <math.h>



CCatmullRom::CCatmullRom()
{
	m_vertexCount = 0;
	m_barrierVertexCount = 0;
}

CCatmullRom::~CCatmullRom()
{
	//FreeGPU();
}

// Perform Catmull Rom spline interpolation between four points, interpolating the space between p1 and p2
glm::vec3 CCatmullRom::Interpolate(glm::vec3& p0, glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	glm::vec3 a = p1;
	glm::vec3 b = 0.5f * (-p0 + p2);
	glm::vec3 c = 0.5f * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3);
	glm::vec3 d = 0.5f * (-p0 + 3.0f * p1 - 3.0f * p2 + p3);

	return a + b * t + c * t2 + d * t3;
}


void CCatmullRom::SetControlPoints()
{
	// Set control points (m_controlPoints) here, or load from disk

	// Optionally, set upvectors (m_controlUpVectors, one for each control point as well)
	
	//Start:
	m_controlPoints.push_back(glm::vec3(0, 100, 0));
	m_controlPoints.push_back(glm::vec3(0, 100, 50));
	m_controlPoints.push_back(glm::vec3(0, 100, 100));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	//180 Degree turn.
	m_controlPoints.push_back(glm::vec3(12, 100, 149));
	m_controlPoints.push_back(glm::vec3(28, 100, 196));
	m_controlPoints.push_back(glm::vec3(50, 100, 241));
	m_controlPoints.push_back(glm::vec3(85, 100, 276));
	m_controlPoints.push_back(glm::vec3(130, 100, 298));
	m_controlPoints.push_back(glm::vec3(177, 100, 314));
	m_controlPoints.push_back(glm::vec3(226, 100, 326));
	m_controlPoints.push_back(glm::vec3(276, 100, 326));
	m_controlPoints.push_back(glm::vec3(325, 100, 314));
	m_controlPoints.push_back(glm::vec3(372, 100, 298));
	m_controlPoints.push_back(glm::vec3(417, 100, 276));
	m_controlPoints.push_back(glm::vec3(452, 100, 241));
	m_controlPoints.push_back(glm::vec3(474, 100, 196));
	m_controlPoints.push_back(glm::vec3(490, 100, 149));
	m_controlPoints.push_back(glm::vec3(502, 100, 100));
	m_controlUpVectors.push_back(glm::vec3(0.05, 0.95, 0));
	m_controlUpVectors.push_back(glm::vec3(0.1, 0.9, 0));
	m_controlUpVectors.push_back(glm::vec3(0.15, 0.85, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	//Straight line
	m_controlPoints.push_back(glm::vec3(502, 100, 50));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	//Sharp left turn:
	m_controlPoints.push_back(glm::vec3(486, 100, 3));
	m_controlPoints.push_back(glm::vec3(464, 100, -42));
	m_controlPoints.push_back(glm::vec3(429, 100, -77));
	m_controlPoints.push_back(glm::vec3(384, 100, -99));
	m_controlPoints.push_back(glm::vec3(337, 100, -115));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 0.7, 0));
	//Straight line
	m_controlPoints.push_back(glm::vec3(287, 100, -115));
	m_controlPoints.push_back(glm::vec3(240, 84, -115));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	//Lowers down to go underneath the original track
	m_controlPoints.push_back(glm::vec3(205, 49, -115));
	m_controlPoints.push_back(glm::vec3(158, 33, -115));
	m_controlPoints.push_back(glm::vec3(108, 33, -115));
	m_controlPoints.push_back(glm::vec3(58, 33, -115));
	m_controlPoints.push_back(glm::vec3(8, 33, -115));
	m_controlPoints.push_back(glm::vec3(-42, 33, -115));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	//Road goes high into the sky to prepare for the loop.
	m_controlPoints.push_back(glm::vec3(-89, 49, -115));
	m_controlPoints.push_back(glm::vec3(-124, 84, -115));
	m_controlPoints.push_back(glm::vec3(-159, 119, -115));
	m_controlPoints.push_back(glm::vec3(-194, 154, -115));
	m_controlPoints.push_back(glm::vec3(-229, 189, -115));
	m_controlPoints.push_back(glm::vec3(-264, 224, -115));
	m_controlPoints.push_back(glm::vec3(-299, 259, -115));
	m_controlPoints.push_back(glm::vec3(-334, 294, -115));
	m_controlPoints.push_back(glm::vec3(-369, 329, -115));
	m_controlPoints.push_back(glm::vec3(-404, 364, -115));
	m_controlPoints.push_back(glm::vec3(-439, 399, -115));
	m_controlPoints.push_back(glm::vec3(-474, 434, -115));
	m_controlPoints.push_back(glm::vec3(-509, 469, -115));
	m_controlPoints.push_back(glm::vec3(-544, 504, -115));
	m_controlPoints.push_back(glm::vec3(-579, 539, -115));
	m_controlPoints.push_back(glm::vec3(-614, 574, -115));
	m_controlUpVectors.push_back(glm::vec3(0.1, 0.9, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(0.4, 0.6, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	//Loop 
	m_controlPoints.push_back(glm::vec3(-636, 618, -125));
	m_controlPoints.push_back(glm::vec3(-651, 664, -135));
	m_controlPoints.push_back(glm::vec3(-651, 713, -145));
	m_controlPoints.push_back(glm::vec3(-636, 759, -155));
	m_controlPoints.push_back(glm::vec3(-614, 803, -165));
	m_controlPoints.push_back(glm::vec3(-579, 838, -175));
	m_controlPoints.push_back(glm::vec3(-535, 860, -185));
	m_controlPoints.push_back(glm::vec3(-489, 875, -195));
	m_controlPoints.push_back(glm::vec3(-440, 875, -205));
	m_controlPoints.push_back(glm::vec3(-394, 860, -215));
	m_controlPoints.push_back(glm::vec3(-350, 838, -225));
	m_controlPoints.push_back(glm::vec3(-315, 803, -235));
	m_controlPoints.push_back(glm::vec3(-293, 759, -245));
	m_controlPoints.push_back(glm::vec3(-278, 713, -255));
	m_controlPoints.push_back(glm::vec3(-278, 664, -265));
	m_controlPoints.push_back(glm::vec3(-293, 618, -275));
	m_controlPoints.push_back(glm::vec3(-315, 574, -285));
	m_controlPoints.push_back(glm::vec3(-337, 530, -295));
	m_controlPoints.push_back(glm::vec3(-359, 486, -305));
	m_controlPoints.push_back(glm::vec3(-381, 442, -315));
	m_controlPoints.push_back(glm::vec3(-403, 398, -325));
	m_controlPoints.push_back(glm::vec3(-425, 354, -335));
	m_controlUpVectors.push_back(glm::vec3(0.75, 0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(0.95, 0.05, 0));
	m_controlUpVectors.push_back(glm::vec3(0.95, -0.05, 0));
	m_controlUpVectors.push_back(glm::vec3(0.75, -0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(0.66, -0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, -0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.33, -0.66, 0));
	m_controlUpVectors.push_back(glm::vec3(0.25, -0.75, 0));
	m_controlUpVectors.push_back(glm::vec3(0.05, -0.95, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.05, -0.95, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.25, -0.75, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.33, -0.66, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.5, -0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.66, -0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.75, -0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.95, -0.05, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.95, 0.05, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.75, 0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.66, 0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.66, 0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.66, 0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.66, 0.33, 0));
	//Larger Loop
	m_controlPoints.push_back(glm::vec3(-460, 319, -345));
	m_controlPoints.push_back(glm::vec3(-504, 297, -355));
	m_controlPoints.push_back(glm::vec3(-550, 282, -365));
	m_controlPoints.push_back(glm::vec3(-598, 270, -375));
	m_controlPoints.push_back(glm::vec3(-647, 270, -385));
	m_controlPoints.push_back(glm::vec3(-695, 282, -395));
	m_controlPoints.push_back(glm::vec3(-741, 297, -405));
	m_controlPoints.push_back(glm::vec3(-785, 319, -415));
	m_controlPoints.push_back(glm::vec3(-820, 354, -425));
	m_controlPoints.push_back(glm::vec3(-842, 398, -435));
	m_controlPoints.push_back(glm::vec3(-857, 444, -445));
	m_controlPoints.push_back(glm::vec3(-869, 492, -455));
	m_controlPoints.push_back(glm::vec3(-869, 541, -465));
	m_controlPoints.push_back(glm::vec3(-857, 589, -475));
	m_controlPoints.push_back(glm::vec3(-842, 635, -485));
	m_controlPoints.push_back(glm::vec3(-820, 679, -495));
	m_controlPoints.push_back(glm::vec3(-785, 714, -505));
	m_controlPoints.push_back(glm::vec3(-741, 736, -515));
	m_controlPoints.push_back(glm::vec3(-695, 751, -525));
	m_controlPoints.push_back(glm::vec3(-647, 763, -535));
	m_controlPoints.push_back(glm::vec3(-598, 763, -545));
	m_controlPoints.push_back(glm::vec3(-549, 763, -555));
	m_controlPoints.push_back(glm::vec3(-500, 763, -565));
	m_controlPoints.push_back(glm::vec3(-451, 763, -575));
	m_controlPoints.push_back(glm::vec3(-402, 763, -585));
	m_controlPoints.push_back(glm::vec3(-353, 763, -595));
	m_controlPoints.push_back(glm::vec3(-304, 763, -605));
	m_controlPoints.push_back(glm::vec3(-255, 763, -615));
	m_controlPoints.push_back(glm::vec3(-207, 751, -625));
	m_controlPoints.push_back(glm::vec3(-161, 736, -635));
	m_controlPoints.push_back(glm::vec3(-117, 714, -645));
	m_controlPoints.push_back(glm::vec3(-82, 679, -655));
	m_controlPoints.push_back(glm::vec3(-60, 635, -665));
	m_controlPoints.push_back(glm::vec3(-45, 589, -675));
	m_controlPoints.push_back(glm::vec3(-33, 541, -685));
	m_controlPoints.push_back(glm::vec3(-33, 492, -695));
	m_controlPoints.push_back(glm::vec3(-45, 444, -705));
	m_controlPoints.push_back(glm::vec3(-60, 398, -715));
	m_controlPoints.push_back(glm::vec3(-75, 352, -725));
	m_controlPoints.push_back(glm::vec3(-90, 306, -735));
	m_controlPoints.push_back(glm::vec3(-105, 260, -745));
	m_controlPoints.push_back(glm::vec3(-120, 214, -755));
	m_controlPoints.push_back(glm::vec3(-135, 168, -765));
	m_controlPoints.push_back(glm::vec3(-157, 124, -775));
	m_controlPoints.push_back(glm::vec3(-192, 89, -785));
	m_controlPoints.push_back(glm::vec3(-236, 67, -795));
	m_controlPoints.push_back(glm::vec3(-282, 52, -805));
	m_controlPoints.push_back(glm::vec3(-330, 40, -815));
	m_controlPoints.push_back(glm::vec3(-380, 40, -815));
	m_controlUpVectors.push_back(glm::vec3(-0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.33, 0.66, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.25, 0.75, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.2, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0.25, 0.75, 0));
	m_controlUpVectors.push_back(glm::vec3(0.33, 0.66, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.66, 0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(0.75, 0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(0.8, 0.2, 0));
	m_controlUpVectors.push_back(glm::vec3(1, 0, 0));
	m_controlUpVectors.push_back(glm::vec3(0.8, -0.2, 0));
	m_controlUpVectors.push_back(glm::vec3(0.75, -0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(0.66, -0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(0.5, -0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(0.33, -0.66, 0));
	m_controlUpVectors.push_back(glm::vec3(0.25, -0.75, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, -0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0.05, -0.95, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.05, -0.95, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.2, -0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.25, -0.75, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.33, -0.66, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.5, -0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.66, -0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.75, -0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.8, -0.2, 0));
	m_controlUpVectors.push_back(glm::vec3(-1, 0, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.8, 0.2, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.75, 0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.75, 0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.75, 0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.75, 0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.75, 0.25, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.66, 0.33, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.5, 0.5, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.33, 0.66, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.25, 0.75, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.20, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.05, 0.95, 0));
	//Preperation for a spiral journey towards the origin point
	m_controlPoints.push_back(glm::vec3(-427, 40, -799));
	m_controlPoints.push_back(glm::vec3(-472, 40, -777));
	m_controlPoints.push_back(glm::vec3(-507, 40, -742));
	m_controlPoints.push_back(glm::vec3(-529, 40, -697));
	m_controlPoints.push_back(glm::vec3(-545, 40, -650));
	m_controlPoints.push_back(glm::vec3(-545, 40, -600));
	m_controlPoints.push_back(glm::vec3(-507, 53, -570));
	m_controlPoints.push_back(glm::vec3(-471, 71, -540));
	m_controlPoints.push_back(glm::vec3(-443, 99, -510));
	m_controlPoints.push_back(glm::vec3(-415, 127, -480));
	m_controlPoints.push_back(glm::vec3(-387, 155, -450));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 0.9, 0));
	m_controlUpVectors.push_back(glm::vec3(0.15, 0.85, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0.25, 0.75, 0));
	m_controlUpVectors.push_back(glm::vec3(0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(0.3, 0.7, 0));
	m_controlUpVectors.push_back(glm::vec3(0.20, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0.1, 0.9, 0));
	m_controlUpVectors.push_back(glm::vec3(0.1, 0.9, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	//Beginning of the spirals ((142))
	m_controlPoints.push_back(glm::vec3(-351, 173, -420));
	m_controlPoints.push_back(glm::vec3(-313, 186, -390));
	m_controlPoints.push_back(glm::vec3(-273, 186, -360));
	m_controlPoints.push_back(glm::vec3(-233, 186, -330));
	m_controlPoints.push_back(glm::vec3(-195, 173, -300));
	m_controlPoints.push_back(glm::vec3(-157, 160, -270));
	m_controlPoints.push_back(glm::vec3(-119, 147, -240));
	m_controlPoints.push_back(glm::vec3(-81, 134, -210));
	m_controlPoints.push_back(glm::vec3(-43, 121, -180));
	m_controlPoints.push_back(glm::vec3(-5, 108, -150));
	m_controlPoints.push_back(glm::vec3(7, 98, -102));
	m_controlPoints.push_back(glm::vec3(7, 98, -52));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 0.9, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.2, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 0.9, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 0.9, 0));
}

// Determine lengths along the control points, which is the set of control points forming the closed curve
void CCatmullRom::ComputeLengthsAlongControlPoints()
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

// Return the point (and upvector, if control upvectors provided) based on a distance d along the control polygon
bool CCatmullRom::Sample(float d, glm::vec3& p, glm::vec3& up)
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
void CCatmullRom::UniformlySampleControlPoints(int numSamples)
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


void CCatmullRom::CreateCentreline()
{
	// Call Set Control Points
	SetControlPoints();

	// Call UniformlySampleControlPoints with the number of samples required
	UniformlySampleControlPoints(500); //200

	// Create a VAO called m_vaoCentreline and a VBO to get the points onto the graphics card
	glGenVertexArrays(1, &m_vaoCentreline);
	glBindVertexArray(m_vaoCentreline);

	CVertexBufferObject vbo;
	vbo.Create();
	vbo.Bind();

	glm::vec2 texCoord1(0.f, 0.f);
	glm::vec2 texCoord2(0.f, 0.f);
	for (unsigned int i = 0; i < 144 - 1; i++) {
		glm::vec3 normal(m_centrelineUpVectors[i]);

		if (i == m_centrelinePoints.size() - 1) {
			vbo.AddData(&m_centrelinePoints[0], sizeof(glm::vec3));
			vbo.AddData(&m_centrelineUpVectors[0], sizeof(glm::vec3));
			vbo.AddData(&texCoord1, sizeof(glm::vec2));
			vbo.AddData(&normal, sizeof(glm::vec3));
		}
			vbo.AddData(&m_centrelinePoints[i], sizeof(glm::vec3));
			vbo.AddData(&m_centrelineUpVectors[i], sizeof(glm::vec3));
			vbo.AddData(&texCoord2, sizeof(glm::vec2));
			vbo.AddData(&normal, sizeof(glm::vec3));
	}
	
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
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3)+sizeof(glm::vec3)));
	//normal positions:
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CCatmullRom::CreateOffsetCurves()
{
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
		glm::vec3 N = glm::normalize(glm::cross(T, m_centrelineUpVectors[i]));
		glm::vec3 B = glm::normalize(glm::cross(N, T));

		float width = 75.f;
		glm::vec3 left = m_centrelinePoints[i] - (width / 2) * N;

		m_leftOffsetPoints.push_back(left);
			lfvbo.AddData(&m_leftOffsetPoints[i], sizeof(glm::vec3));
			lfvbo.AddData(&Coords, sizeof(glm::vec2));
			lfvbo.AddData(&B, sizeof(glm::vec3));

			if (i == m_centrelinePoints.size() - 1) {
				lfvbo.AddData(&m_leftOffsetPoints[0], sizeof(glm::vec3));
				lfvbo.AddData(&Coords, sizeof(glm::vec2));
				lfvbo.AddData(&B, sizeof(glm::vec3));
			}
	}	

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
		glm::vec3 N = glm::normalize(glm::cross(T, m_centrelineUpVectors[i]));
		glm::vec3 B = glm::normalize(glm::cross(N, T));

		float width = 75.f;
		glm::vec3 right = m_centrelinePoints[i] + (width / 2) * N;

		m_rightOffsetPoints.push_back(right);

			rvbo.AddData(&m_rightOffsetPoints[i], sizeof(glm::vec3));
			rvbo.AddData(&Rcoords, sizeof(glm::vec2));
			rvbo.AddData(&B, sizeof(glm::vec3));

			if (i == m_centrelinePoints.size() - 1) {
				rvbo.AddData(&m_rightOffsetPoints[0], sizeof(glm::vec3));
				rvbo.AddData(&Rcoords, sizeof(glm::vec2));
				rvbo.AddData(&B, sizeof(glm::vec3));
		}
	}

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

void CCatmullRom::RenderCentreline()
{
	// Binds the VAO m_vaoCentreline and renders it
	glBindVertexArray(m_vaoCentreline);
	glDrawArrays(GL_POINTS, 0, m_centrelinePoints.size());

}

void CCatmullRom::RenderOffsetCurves()
{
	// Binds the VAO m_vaoLeftOffsetCurve and renders it
	glBindVertexArray(m_vaoLeftOffsetCurve);
	glDrawArrays(GL_LINE_STRIP, 0, m_leftOffsetPoints.size());

	// Binds the VAO m_vaoRightOffsetCurve and renders it
	glBindVertexArray(m_vaoRightOffsetCurve);
	glDrawArrays(GL_LINE_STRIP, 0, m_rightOffsetPoints.size());
}

void CCatmullRom::TRender(string filename1, string filename2)
{
	// Load the texture
	m_tex.Load(filename1, true);

	// Set parameters for texturing using sampler object
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	m_texture.Load(filename2, true);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_tex.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void CCatmullRom::CreateTrack()
{
	m_tex.Bind();
	glGenVertexArrays(1, &m_vaoTrack);
	glBindVertexArray(m_vaoTrack);

	CVertexBufferObject trackvbo;
	trackvbo.Create();
	trackvbo.Bind();

	float textureRepeat = 1.f;
	m_vertexCount = 0; //Resetting vertexCount.
	
	glm::vec2 tCoord[4] =
	{
	glm::vec2(0.f, 0.f),
	glm::vec2(0.f, textureRepeat),
	glm::vec2(textureRepeat, 0.f),
	glm::vec2(textureRepeat, textureRepeat),
	};

	

	for (unsigned i = 0; i < m_centrelinePoints.size(); i++) {
		glm::vec3 normal(m_centrelineUpVectors[i]);

		if (i == m_centrelinePoints.size() - 1) {
			trackvbo.AddData(&m_leftOffsetPoints[0], sizeof(glm::vec3));
			trackvbo.AddData(&tCoord[0], sizeof(glm::vec2));
			trackvbo.AddData(&normal, sizeof(glm::vec3));
			trackvbo.AddData(&m_rightOffsetPoints[0], sizeof(glm::vec3));
			trackvbo.AddData(&tCoord[3], sizeof(glm::vec2));
			trackvbo.AddData(&normal, sizeof(glm::vec3));
			m_vertexCount += 2;
		}
		trackvbo.AddData(&m_leftOffsetPoints[i], sizeof(glm::vec3));
		trackvbo.AddData(&tCoord[i % 2], sizeof(glm::vec2));
		trackvbo.AddData(&normal, sizeof(glm::vec3));
		trackvbo.AddData(&m_rightOffsetPoints[i], sizeof(glm::vec3));
		trackvbo.AddData(&tCoord[(i % 2) + 2], sizeof(glm::vec2));
		trackvbo.AddData(&normal, sizeof(glm::vec3));

		m_vertexCount += 2;
	}

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


void CCatmullRom::RenderTrack()
{
	// Bind the VAO m_vaoTrack and render it
	glBindVertexArray(m_vaoTrack);
	m_tex.Bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexCount); //m_vertexCount); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CCatmullRom::CreateBarriers() {
	//Left side:
	glGenVertexArrays(1, &m_vaoLeftBarrierCurve);
	glBindVertexArray(m_vaoLeftBarrierCurve);
	CVertexBufferObject lfbvbo;
	lfbvbo.Create();
	lfbvbo.Bind();

	glm::vec2 Coords(0.f, 0.f);
	glm::vec3 Normal(0.f, 1.f, 0.f);

	for (unsigned i = 0; i < m_centrelinePoints.size(); i++) {
		glm::vec3 pBNext;

		if (i != m_centrelinePoints.size() - 1) {
			pBNext = m_centrelinePoints[i + 1];
		}
		else {
			pBNext = m_centrelinePoints[0];
		}

		glm::vec3 T = glm::normalize(pBNext - m_centrelinePoints[i]);
		glm::vec3 N = glm::normalize(glm::cross(T, m_centrelineUpVectors[i]));
		glm::vec3 B = glm::normalize(glm::cross(N, T));

		float width = 75.f;
		glm::vec3 leftBarrier = m_centrelinePoints[i] - (width / 2) * N;

		m_leftBarrierPoints.push_back(leftBarrier + glm::vec3(0, 5, 0));

		lfbvbo.AddData(&m_leftBarrierPoints[i], sizeof(glm::vec3));
		lfbvbo.AddData(&Coords, sizeof(glm::vec2));
		lfbvbo.AddData(&B, sizeof(glm::vec3));

		if (i == m_centrelinePoints.size() - 1) {
			lfbvbo.AddData(&m_leftBarrierPoints[0], sizeof(glm::vec3));
			lfbvbo.AddData(&Coords, sizeof(glm::vec2));
			lfbvbo.AddData(&B, sizeof(glm::vec3));
		}
	}

	lfbvbo.UploadDataToGPU(GL_STATIC_DRAW);

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
	glGenVertexArrays(1, &m_vaoRightBarrierCurve);
	glBindVertexArray(m_vaoRightBarrierCurve);

	CVertexBufferObject rbvbo;

	rbvbo.Create();
	rbvbo.Bind();

	glm::vec2 Rcoords = glm::vec2(0.f, 0.f);
	glm::vec3 Rnormal = glm::vec3(0.f, 1.f, 0.f);

	for (unsigned i = 0; i < m_centrelinePoints.size(); i++) {
		glm::vec3 pBNext;

		if (i != m_centrelinePoints.size() - 1) {
			pBNext = m_centrelinePoints[i + 1];
		}
		else {
			pBNext = m_centrelinePoints[0];
		}

		glm::vec3 T = glm::normalize(pBNext - m_centrelinePoints[i]);
		glm::vec3 N = glm::normalize(glm::cross(T, m_centrelineUpVectors[i]));
		glm::vec3 B = glm::normalize(glm::cross(N, T));

		float width = 75.f;
		glm::vec3 rightBarrier = m_centrelinePoints[i] + (width / 2) * N;

		m_rightBarrierPoints.push_back(rightBarrier + glm::vec3(0, 5, 0));

		rbvbo.AddData(&m_rightBarrierPoints[i], sizeof(glm::vec3));
		rbvbo.AddData(&Rcoords, sizeof(glm::vec2));
		rbvbo.AddData(&B, sizeof(glm::vec3));

		if (i == m_centrelinePoints.size() - 1) {
			rbvbo.AddData(&m_rightBarrierPoints[0], sizeof(glm::vec3));
			rbvbo.AddData(&Rcoords, sizeof(glm::vec2));
			rbvbo.AddData(&B, sizeof(glm::vec3));
		}
	}

	rbvbo.UploadDataToGPU(GL_STATIC_DRAW);

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

void CCatmullRom::RenderBarriers() {
	// Binds the VAO m_vaoLeftBarrierCurve and renders it
	glBindVertexArray(m_vaoLeftBarrierCurve);
	glDrawArrays(GL_LINE_STRIP, 0, m_leftBarrierPoints.size());

	// Binds the VAO m_vaoRightBarrierCurve and renders it
	glBindVertexArray(m_vaoRightBarrierCurve);
	glDrawArrays(GL_LINE_STRIP, 0, m_rightBarrierPoints.size());
}

void CCatmullRom::CreateBarrierTrack() {
	m_texture.Bind();
	glGenVertexArrays(1, &m_vaoBarrierTrack);
	glBindVertexArray(m_vaoBarrierTrack);

	CVertexBufferObject btrackvbo;
	btrackvbo.Create();
	btrackvbo.Bind();

	m_barrierVertexCount = 0; //Resetting vertexCount.
	float textureRepeat = 1.f;

	glm::vec2 tCoord[4] =
	{
	glm::vec2(0.f, 0.f),
	glm::vec2(0.f, textureRepeat),
	glm::vec2(textureRepeat, 0.f),
	glm::vec2(textureRepeat, textureRepeat),
	};

	for (unsigned i = 0; i < m_centrelinePoints.size(); i++) {
		glm::vec3 normal(m_centrelineUpVectors[i]);

		if (i == m_centrelinePoints.size() - 1) {
			btrackvbo.AddData(&m_leftBarrierPoints[0], sizeof(glm::vec3));
			btrackvbo.AddData(&tCoord[0], sizeof(glm::vec2));
			btrackvbo.AddData(&normal, sizeof(glm::vec3));
			btrackvbo.AddData(&m_leftOffsetPoints[0], sizeof(glm::vec3));
			btrackvbo.AddData(&tCoord[3], sizeof(glm::vec2));
			btrackvbo.AddData(&normal, sizeof(glm::vec3));
			m_barrierVertexCount += 2;
		}
			btrackvbo.AddData(&m_leftBarrierPoints[i], sizeof(glm::vec3));
			btrackvbo.AddData(&tCoord[i % 2], sizeof(glm::vec2));
			btrackvbo.AddData(&normal, sizeof(glm::vec3));
			btrackvbo.AddData(&m_leftOffsetPoints[i], sizeof(glm::vec3));
			btrackvbo.AddData(&tCoord[(i % 2)+2], sizeof(glm::vec2));
			btrackvbo.AddData(&normal, sizeof(glm::vec3));
		m_barrierVertexCount += 2;
	}

	btrackvbo.UploadDataToGPU(GL_STATIC_DRAW);

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

	glGenVertexArrays(1, &m_vaoRightTrack);
	glBindVertexArray(m_vaoRightTrack);

	CVertexBufferObject trackvbo;
	trackvbo.Create();
	trackvbo.Bind();

	for (unsigned i = 0; i < m_centrelinePoints.size(); i++) {
		glm::vec3 rnormal(m_centrelineUpVectors[i]);

		if (i == m_centrelinePoints.size() - 1) {
			trackvbo.AddData(&m_rightBarrierPoints[0], sizeof(glm::vec3));
			trackvbo.AddData(&tCoord[0], sizeof(glm::vec2));
			trackvbo.AddData(&rnormal, sizeof(glm::vec3));
			trackvbo.AddData(&m_rightOffsetPoints[0], sizeof(glm::vec3));
			trackvbo.AddData(&tCoord[3], sizeof(glm::vec2));
			trackvbo.AddData(&rnormal, sizeof(glm::vec3));
			m_barrierVertexCount += 2;
		}
			trackvbo.AddData(&m_rightBarrierPoints[i], sizeof(glm::vec3));
			trackvbo.AddData(&tCoord[i%2], sizeof(glm::vec2));
			trackvbo.AddData(&rnormal, sizeof(glm::vec3));
			trackvbo.AddData(&m_rightOffsetPoints[i], sizeof(glm::vec3));
			trackvbo.AddData(&tCoord[(i%2)+2], sizeof(glm::vec2));
			trackvbo.AddData(&rnormal, sizeof(glm::vec3));
		m_barrierVertexCount += 2;
	}

	trackvbo.UploadDataToGPU(GL_STATIC_DRAW);

	GLsizei rstride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);

	//Vertex Positions:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, rstride, 0);
	//Texture Coordinates:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, rstride, (void*)sizeof(glm::vec3));
	//Normal Coordinates:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, rstride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CCatmullRom::RenderBarrierTrack() {
	// Bind the VAO m_vaoTrack and render it
	glBindVertexArray(m_vaoBarrierTrack);
	m_texture.Bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_barrierVertexCount -2); //m_vertexCount); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(m_vaoRightTrack);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_barrierVertexCount -2); //m_vertexCount); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int CCatmullRom::CurrentLap(float d)
{
	return (int)(d / m_distances.back());
}

void CCatmullRom::FreeGPU() {
	m_tex.Release();
	glDeleteVertexArrays(1, &m_vaoCentreline);
	glDeleteVertexArrays(1, &m_vaoLeftOffsetCurve);
	glDeleteVertexArrays(1, &m_vaoRightOffsetCurve);
	glDeleteVertexArrays(1, &m_vaoTrack);
}

glm::vec3 CCatmullRom::_dummy_vector(0.0f, 0.0f, 0.0f);