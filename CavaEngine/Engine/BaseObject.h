#pragma once

namespace Cava
{

	/// <summary>
	/// Base Entity object
	/// </summary>
	class BaseObject
	{
	public:
		BaseObject(std::string name);

		virtual ~BaseObject() {}
		virtual void OnInit() = 0;
		virtual void OnCreated() = 0; // Triggers once when spawned to scene
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void BeforeQuit() = 0;

		void setName(std::string name) { name = name; }

		IntHash getID() { return id; }
		std::string getName() { return name; }

	protected:
		void setID(IntHash id) { this->id = id; }
		IntHash		id = -1;
		std::string name = "";

	private:
		BaseObject();
	};

	
}