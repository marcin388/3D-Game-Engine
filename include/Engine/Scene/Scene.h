#pragma once

#include <glad/glad.h>
#include <glm\glm.hpp>
#include <Engine\Loaders\Loader.h>
#include <Engine/Game_Objects/Game_Object.h>
#include <Engine/State/State.h>
#include <Engine\Game_Objects\Camera_3D.h>
#include <Engine\Loaders\SceneLoader.h>
#include <Engine\Physics\CollisionManager.h>
//#include <Light.h>

class Loader;

class Scene
{
protected:
	//Main resource loader
	Loader* po_Loader;

	//State manager
	State* po_GameState;

	//Scene loader
	SceneLoader* o_SceneLoader;

	//Cameras
	Camera_3D* camera_3D;

	//Collision Manager
	CollisionManager colManage;

	//Game Objects
	std::map<std::string, Game_Object*> mspo_Objects;

	// Is mouse locked?
	bool b_LockMouse;

    //Is mouse pressed?
	bool b_MousePressed;

	//Initalize the scene
	bool b_Init;

public:
	//Constructor
	Scene() {};

	//Initialize
	virtual void init() = 0;

	//Render
	virtual void render() = 0;

	//Reloads the scene
	virtual void reload_Scene() = 0;

	//Update scene
	virtual void update_Scene(GLfloat f_Delta_In, glm::vec2 v2_MousePos_In) = 0;

	//Keyboard input
	virtual void keyboard_Input(GLfloat f_Delta_In, GLboolean* pab_KeyArray_In, GLboolean* pab_LockedArray_In) = 0;

	//Mosue input
	virtual void mouse_Input(GLboolean* pab_MouseArray_In) = 0;

	//Clean up
	virtual void clean_Up() = 0;
	
	//Extract state
	void extract_State(State* po_State_In);

	//Pass loader
	void pass_Loader(Loader* po_Loader_In);

	//Is loader empty?
	bool is_LoaderEmpty();

	//Lock mouse
	void lock_mouse(bool b_Cond_In);

	//Is mouse locked?
	bool is_MouseLocked();
};