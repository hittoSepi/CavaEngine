#include "Core/Cava.h"
#include "Engine/Component/Component.h"

namespace Cava
{

	GameObject::GameObject() :
		BaseObject("error")
	{
		//should_not_get_here();
		//LogError(std::string("Don't create GameObjects with default constructor!"));
	}

	GameObject::GameObject(const std::string& name) :
		BaseObject(name)
	{
		OnInit();
	}

	GameObject::~GameObject()
	{
	
	}

	void GameObject::BeforeQuit()
	{
		childrens.empty();
		components.empty();
	}


	void GameObject::OnInit() {
	
	}

	void GameObject::OnCreated()
	{

	}


	void GameObject::OnUpdate()
	{


	}

	void GameObject::OnRender()
	{

	}


	void GameObject::AddChildren(GameObject* go)
	{
		childrens.try_emplace(go->getID(), go);
	}

	
	void GameObject::AddComponent(Component* comp)
	{
		components.try_emplace(comp->getID(), comp);
	}

	GameObject* GameObject::clone() { return new GameObject(*this); }
	GameObject* GameObject::Create(std::string name) { return new GameObject(name); }

}