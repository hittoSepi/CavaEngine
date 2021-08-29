#pragma once

#include "Engine/Component/Component.h"

namespace Cava
{

	class GameObject : public BaseObject
	{
	
	public:
		friend class Component;
		friend class GameObjectManager;
		
		GameObject();
		GameObject(const std::string& name);

		virtual void OnInit() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;
		virtual void BeforeQuit() override;
		virtual void OnCreated() override;
		virtual ~GameObject() override;

		// setters
		void setRoot(GameObject* _root) { root = _root; }
		void setParent(GameObject* _parent) { parent = _parent; }
		void setChildrens(std::map<IntHash, GameObject*> _childrens) { childrens = _childrens; }
		void SetComponents(std::map<IntHash, Component*> _components) { components = _components; }

		// getters
		GameObject* GetRoot() { return parent; }
		GameObject* GetParent() { return parent; }
		std::map<IntHash, GameObject*> GetChildrens() { return childrens; }
		std::map<IntHash, Component*> GetComponents() { return components; }

		// adders
		void AddChildren(GameObject* go);	// add children GameObject
		void AddComponent(Component* comp); // add Component to GameObject

		GameObject* clone();

		static GameObject* Create(std::string name); /// create new GameObject
	private:
		bool atPool = false; // GameObjectManager sets to true when added to pool

		GameObject* parent = nullptr;
		GameObject* root = nullptr;
		
		std::map<IntHash, GameObject*> childrens;
		std::map<IntHash, Component*> components;
	};


}
