#include "Core/Cava.h"

namespace Cava
{


	Component::Component()
	{
		getName("Component_");
	}


	Component::Component(const std::string& name)
	{
		getName(name);
	}

	Component::~Component()
	{
		//delete (attachedGameObject);
	}

	void Component::beforeQuit()
	{
		//attachedGameObject->quit();
	}

	void Component::init()
	{
		if (attachedGameObject == nullptr)
		{
			LogWarning("Component isn't attached to GameObject.");
		}
	}

	void Component::created()
	{
	}


	void Component::update()
	{
	}

	void Component::render()
	{
	}


	int Component::getIndex(const int idx)
	{
		index = idx;
		return index;
	}

	/// Attach Component to Game”bject
	void Component::getGameObject(GameObject* gameobj)
	{
		attachedGameObject = gameobj;
	}

	
	GameObject* Component::getAttachedGameObject()
	{
		return attachedGameObject;
	}

}
