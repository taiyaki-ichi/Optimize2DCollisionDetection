#pragma once
#include<vector>
#include"vec2f.hpp"
#include"include/traits.hpp"

namespace my
{
	//3ŒÂˆÈã‚Ì’¸“_‚©‚ç\¬‚³‚ê‚é‘½ŠpŒ`
	using shape = std::vector<vec2f>;

}

namespace collision_detection
{
	template<>
	struct range_traits<my::shape>
	{
		static std::tuple<float, float, float, float> get_range(const my::shape& s)
		{

			float left{ s[0].x };
			float right{ s[0].x };
			float bottom{ s[0].y };
			float top{ s[0].y };

			float x, y;
			for (size_t i = 1; i < s.size(); i++)
			{
				x = s[i].x;
				y = s[i].y;

				if (x < left)
					left = x;
				else if (right < x)
					right = x;

				if (y < bottom)
					bottom = y;
				else if (top < y)
					top = y;
			}

			return { left,right,bottom,top };
		}
	};

	template<>
	struct shape_traits<my::shape>
	{
		static inline unsigned int get_vertex_num(const my::shape& s) {
			return s.size();
		}

		static inline float get_vertex_x(const my::shape& s, unsigned int num) {
			return s[num].x;
		}

		static inline float get_vertex_y(const my::shape& s, unsigned int num) {
			return s[num].y;
		}
	};
}