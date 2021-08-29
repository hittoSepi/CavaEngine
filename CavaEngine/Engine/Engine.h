#pragma once
#include <string>
#include "Core/Cava.h"

namespace Cava
{
	
	class   Engine : public Singleton<Engine>
	{
	public:
		
		friend class Singleton<Engine>;

		Engine();
		~Engine();

		void OnInit();
		void OnUpdate();
		void OnRender();
		void BeforeQuit();

		GameObjectManager* GetGameObjectManager();
		ComponentManager* GetComponentManager();

		static IntHash GetId(std::string input);

	private:
		GameObjectManager* gameObjectManager;
		ComponentManager* componentManager;
	};

}