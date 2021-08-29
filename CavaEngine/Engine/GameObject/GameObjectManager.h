#pragma once

#include "Engine/GameObject/GameObject.h"

namespace Cava
{
	class   GameObjectManager : public Singleton<GameObjectManager>
	{
	friend class Singleton<GameObjectManager>;
	public:
		
		GameObjectManager();
		~GameObjectManager();

		void init();
		void update();
		void render();
		void quit();

		void add(GameObject* obj);
		void remove(GameObject* obj);

		/// <summary>
		/// create new <c> GameObject </c> and add it to GameObjectPool.
		/// Main way to create <c> GameObject </c> 
		/// </summary>
		/// <returns>Pointer to newly created <c> GameObject </c></returns>
		GameObject* create(std::string name);

		long long totalGameObjectsCreated() { return gameObjectsCreated; }
	private:


		/// <summary>
		/// Adds new <c>GameObjects</c> from waiting queue to <c>GameObjectPool</c>
		/// </summary>
		void addObjects();

		/// <summary>
		/// Removes <c>GameObjects</c> from <c>GameObjectPool</c>
		/// </summary>
		void removeObjects();
		
		void UpdateThread();

		std::map<IntHash, GameObject*>				gameObjects;
		std::list<GameObject*>						addList;
		std::list<IntHash>							removeList;
		std::list<GameObject*>::iterator			listIt;
		std::map<IntHash, GameObject*>::iterator	poolIt;

		// thread
		bool					Running = false;
		std::thread				updateThread;
		std::mutex              lock;

		long long        gameObjectsCreated = 0;
	};

}
