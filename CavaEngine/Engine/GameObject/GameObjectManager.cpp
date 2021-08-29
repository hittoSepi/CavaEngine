#include "Core/Cava.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/Component.h"

using namespace std;

namespace Cava
{

	GameObjectManager::GameObjectManager()
	{

	}


	void GameObjectManager::init()
	{
		Running = true;
		
		updateThread = thread(&UpdateThread, nullptr);
		updateThread.detach();
	}

	void GameObjectManager::UpdateThread()
	{
		LogInfo("Started UpdateThread().");

		while (Running)
		{
			if (!addList.empty() || !removeList.empty())
			{
				removeObjects();
				addObjects();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void GameObjectManager::update()
	{
	}

	void GameObjectManager::render()
	{
	}

	/// <summary>
	/// Wait for UpdateThread to join back.
	/// </summary>
	void GameObjectManager::quit()
	{

		LogInfo("GameObjectManager: Quitting thread");
		Running = false;
	}

	GameObjectManager::~GameObjectManager()
	{
		//SAFE_DELETE(gameObjects);
		//SAFE_DELETE(addList);
		//SAFE_DELETE(removeList);

		//delete (updateThread);
	}



	void GameObjectManager::addObjects()
	{
		for (auto iter = addList.begin(); iter != addList.end(); ++iter)
		{
			GameObject* obj = (GameObject*)iter._Ptr;
			
			// Skip if somehow already at pool
			if (obj->atPool == false)
			{
				obj->atPool = true;
				gameObjects.try_emplace(obj->getID(), obj);
				gameObjectsCreated++;
			}
		}
		addList.clear();

	}



	void GameObjectManager::removeObjects()
	{
		auto iter = removeList.begin();
		while (iter != removeList.end())
		{
			auto goDelIter = gameObjects.find(((GameObject*)&iter)->getID());
			gameObjects.erase(goDelIter);
			delete& iter;
			iter++;
		}
	}


	void GameObjectManager::remove(GameObject* obj)
	{
		if (lock.try_lock())
		{
			removeList.emplace_back(obj->getID());
			lock.unlock();
		}
	}


	void GameObjectManager::add(GameObject* obj)
	{
		if (lock.try_lock())
		{
			addList.emplace_back(obj);
			lock.unlock();
		}
	}

	GameObject* GameObjectManager::create(std::string name)
	{
		GameObject* newObject = new GameObject(name);
		if (lock.try_lock())
		{
			addList.emplace_back(newObject);
			lock.unlock();
		}
		return newObject;
	}

}