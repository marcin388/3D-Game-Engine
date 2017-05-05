#include "Game/AIController/AIController.h"
#include "Game/AIController/State_Idle.h"
#include "Game/AIController/State_Patrol.h"
#include "Game/AIController/State_Attack.h"

AIController::AIController(GameObject_3D * character) :
	FSM(&stateList)
{
	stateList.push_back(new State_Idle(ccs::Idle));
	stateList.push_back(new State_Patrol(ccs::Patrol));
	stateList.push_back(new State_Attack(ccs::Attack));
	InitializeToState(ccs::Idle);
	data.character = character;
}

AIController::~AIController()
{
	for (unsigned int i = 0; i < stateList.size(); i++)
	{
		delete stateList[i];
	}
}

void AIController::Update()
{
	Run();
}
