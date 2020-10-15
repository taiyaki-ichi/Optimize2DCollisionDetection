#pragma once

namespace my
{
	template<typename T>
	struct vec2_traits
	{
		static inline float get_x(const T& vec) { return vec.x; }
		static inline float get_y(const T& vec) { return vec.y; }
	};
}