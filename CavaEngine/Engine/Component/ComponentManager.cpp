#include "Core/Cava.h"
#include "Engine/Component/Component.h"
using namespace std;

namespace Cava
{

ComponentManager::ComponentManager()
{}


void ComponentManager::init()
{
	LogInfo("Starting up.")
/*	components	= new std::map<IntHash, Component*>();
	addList		= new std::list<Component*>();
	removeList	= new std::list<IntHash>();
*/
}

	
ComponentManager::~ComponentManager()
{

	
//	SAFE_DELETE(addList);
//	SAFE_DELETE(removeList);
//	SAFE_DELETE(components);
}

	
void ComponentManager::quit()
{
	LogInfo("Finishig up.")
	
}

void ComponentManager::update()
{
	removeObjects();
	addObjects();
}


	void ComponentManager::addObjects()
{
	if(!addList.empty()) {
		for_each(addList.begin(), addList.end(), [&](Component *object)
		{
			components.try_emplace(object->getID(), object);
		});
		LogInfo("Items added: " + addList.size())
		addList.clear();
	}
}

void ComponentManager::removeObjects()
{
	if (!removeList.empty()) {
		for_each(removeList.begin(), removeList.end(), [&](IntHash hash)
		{
			components.erase(components.find(hash));
		});
		LogInfo("Items added: " + removeList.size())
		removeList.clear();
	}
}

void ComponentManager::remove(IntHash id)
{
	removeList.emplace_back(id);
}

void ComponentManager::add(Component *obj)
{
	addList.emplace_back(obj);
}


}