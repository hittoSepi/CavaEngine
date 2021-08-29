#pragma once
#include "Core/Cava.h"
#include <string>

namespace Cava
{

	class Component
	{
	public:
		friend class ComponentManager;
		friend class GameObject;

		Component();
		Component(const std::string& name);
		virtual     ~Component();

		virtual void init();
		virtual void update();
		virtual void render();
		virtual void created();
		virtual void beforeQuit();


		// setters
		void    getGameObject(GameObject* gameobj);
		int     getIndex(const int idx);
		void	getName(std::string name) { name = name; }

		// getters
		int                 getIndex() { return index; }
		IntHash				getID() { return id; }
		std::string			getName() { return name; }
		GameObject*			getAttachedGameObject();

		static Component* create(std::string name) { return new Component(name); }

	private:
		IntHash			id					= -1;
		int             index				= -1;
		std::string		name				= "";
		GameObject*		attachedGameObject	= nullptr;


	protected:
		void setID(const IntHash _id) { id = _id; }

	private:


	};

}
