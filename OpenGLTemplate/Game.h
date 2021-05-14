#pragma once

#include "Common.h"
#include "GameWindow.h"

// Classes used in game.  For a new class, declare it here and provide a pointer to an object of this class below.  Then, in Game.cpp, 
// include the header.  In the Game constructor, set the pointer to NULL and in Game::Initialise, create a new object.  Don't forget to 
// delete the object in the destructor.   
class CCamera;
class CSkybox;
class CShader;
class CShaderProgram;
class CPlane;
class CFreeTypeFont;
class CHighResolutionTimer;
class CSphere;
class COpenAssetImportMesh;
class CAudio;
class CCatmullRom;
class CCube;
class GGrassPatch;
class CRoad;
class CPentahedron;
class CFrameBufferObject;

class Game {
private:
	// Three main methods used in the game.  Initialise runs once, while Update and Render run repeatedly in the game loop.
	void Initialise();
	void Update();
	void Render();
	void SceneRendering(int a);

	// Pointers to game objects.  They will get allocated in Game::Initialise()
	//Skybox:
	CSkybox *m_pSkybox;

	//Camera
	CCamera *m_pCamera;

	//Shaders:
	vector <CShaderProgram *> *m_pShaderPrograms;

	//Terrain:
	CPlane *m_pPlanarTerrain;

	//Fonts
	CFreeTypeFont *m_pFtFont;

	//Meshes
	COpenAssetImportMesh *m_pBarrelMesh;
	COpenAssetImportMesh *m_pHorseMesh;
	COpenAssetImportMesh *m_Tree;
	COpenAssetImportMesh *m_Fighter;
	COpenAssetImportMesh *m_Car;
	COpenAssetImportMesh *m_Jeep;
	COpenAssetImportMesh *m_f360;

	//Primitives and objects
	CSphere *m_pSphere;
	CCube	*m_Cube;
	GGrassPatch	*m_GP;
	CPentahedron* m_Pp;

	//Audio
	CAudio *m_pAudio;

	//CatmullRom splines
	CCatmullRom *m_CatmullRom;

	//Side Road
	CRoad		*m_Road;

	CHighResolutionTimer* m_pHighResolutionTimer;

	//FBO
	CFrameBufferObject* m_FBO;

	// Some other member variables
	//DeltaTime
	double m_dt;
	int m_framesPerSecond;
	//Checks whether app is active
	bool m_appActive;
	//CatmullRom spline information.
	float m_currentDist;

	//Camera variables:
	bool isTPview, isFPview, isFreeview, isTopDownview, isSideView, isOPView;
	float m_camRot;

	//Player variables:
	glm::vec3 fighter_position;
	glm::mat4 fighter_orientation;
	float m_Speed;
	float m_CurrSpeed;
	bool isFinished;
	bool isDead;
	bool isLeft;
	bool isMiddle;
	bool isRight;
	int lap;
	bool isLevel1;
	bool isLevel2;
	bool isLevel3;
	bool isLevel4;

	//Horses positon
	float a;

	//Objects variables:
	float m_TreeSpacing;
	float m_rotY;
	float m_rotYY;
	float m_HouseSpacing;
	float m_GrassSpacing;
	float m_RoofSpacing;
	glm::vec3 car_position;
	glm::mat4 car_orientation;
	float m_CarSpeed;
	float m_CarcurrDist;
	int Carlap;

	//Vectors3
	glm::vec3 N;
	glm::vec3 B;
	glm::vec3 T;
	glm::vec3 p;
	float Turn;
	glm::vec3 n;
	glm::vec3 b;
	glm::vec3 t;

	//Other variables:
		//Music
	bool isMusic;
		//Lights
	bool isNight;
		//Fog & Discarding & Blur
	bool fog;
	bool isAppearing;
	bool isBlur;
	float blur;
	bool isReflection;
		//float for the blinking lights
	float m_t;
	vector<glm::vec3> ambients;
	glm::vec3 AmbientLightsColors;
	bool isDynamic;


public:
	Game();
	~Game();
	static Game& GetInstance();
	LRESULT ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param);
	void SetHinstance(HINSTANCE hinstance);
	WPARAM Execute();

private:
	static const int FPS = 60;
	void DisplayFrameRate();
	void GameLoop();
	GameWindow m_gameWindow;
	HINSTANCE m_hInstance;
	int m_frameCount;
	double m_elapsedTime;

	void Reset();
	void LevelObstacles();
	void LevelChecker();
};
