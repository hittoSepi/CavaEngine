#pragma once

namespace Cava
{
	/// <summary>
	/// Component Manager class for <c>Component</c>\n
	/// </summary>
	class   ComponentManager : public Singleton<ComponentManager>
	{
	public:
		ComponentManager();
		~ComponentManager();

		void init();
		void quit();
		void update();
		//void render();

		void add(Component* obj);
		void remove(IntHash id);

	private:
		void addObjects();
		void removeObjects();

		std::map<IntHash, Component*>	components;
		std::list<Component*>			addList;
		std::list<IntHash>				removeList;
	};

}
