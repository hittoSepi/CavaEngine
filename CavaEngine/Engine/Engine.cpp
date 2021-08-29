#pragma once
#include "Core/Cava.h"
#include "Core/Debug/Debug.h"
#include "Engine/Engine.h"
#include "Engine/Component/ComponentManager.h"
#include "Engine/GameObject/gameObjectManager.h"

namespace Cava
{

Engine::Engine()
{}


void Engine::OnInit()
{
	LogInfo("Starting up.")

	gameObjectManager	= &GameObjectManager::GetInstance();
	componentManager	= &ComponentManager::GetInstance();
}

void Engine::BeforeQuit()
{
	LogInfo("Finishing up.");
	gameObjectManager->quit();
	componentManager->quit();
}

void Engine::OnUpdate()
{
	gameObjectManager->update();
	componentManager->update();
}
void Engine::OnRender()
{
	gameObjectManager->render();
	//componentManager->render();
}

Engine::~Engine()
{
}


IntHash Engine::GetId(std::string input) {
	return std::hash<std::string>{}(input);
}

GameObjectManager* Engine::GetGameObjectManager() { return gameObjectManager; }
ComponentManager*  Engine::GetComponentManager()  { return componentManager;}	
}