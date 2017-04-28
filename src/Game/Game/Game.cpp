#include <Game/Game/Game.h>
#include <Game/Scene/Game_Scene.h>
#include <Engine\Loaders\Loader.h>

//Constructor
Game::Game()
{
	b_GameIsOver = false;
	po_Loader = new Loader();
}

void Game::init()
{
	po_Loader->start();
	o_State.push_State(new Game_Scene());
}

//Process input
void Game::process_Input(GLfloat deltaTime)
{
	if (!o_State.is_Empty()) // If stack is not empty
	{
		o_State.back()->keyboard_Input(deltaTime, ab_Keys, ab_LockedKeys);
		o_State.back()->mouse_Input(ab_MousePress);
	}
}

//Update
void Game::update(GLfloat deltaTime, glm::vec2 mouse_Pos_In)
{
	if (o_State.is_Empty()) //If stack is not empty
	{
		b_GameIsOver = true;
	}
	else // else process it
	{
		if (o_State.back()->is_LoaderEmpty()) o_State.back()->pass_Loader(po_Loader);
		mouse_Lock(o_State.back()->is_MouseLocked());
		o_State.back()->update_Scene(deltaTime, mouse_Pos_In);
	}
}

//Draw
void Game::draw()
{
	if (!o_State.is_Empty()) o_State.back()->render();
}

//Process keys
void Game::process_Key(int key, GLboolean state)
{
	ab_Keys[key] = state;
}

void Game::process_Mouse(int button, GLboolean state)
{
	ab_MousePress[button] = state;
}

void Game::clean_Up()
{
	po_Loader->clean_Up();
	delete po_Loader;
}