#pragma once

namespace Cava {

	template <class T>
	class Rectangle
	{
	public:
		T x, y, width, height;
		Rectangle(T x, T y, T width, T height):
			x(x), y(y), width(width), height(height)
		{
			
		}

		const float &area()
		{
			return width*height;
		}
	};

}