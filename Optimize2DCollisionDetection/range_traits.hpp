#pragma once
#include<tuple>
#include"vec2_traits.hpp"

namespace my
{
	//デフォルトのShapeはvec2_traitsを満たす頂点のコンテナで当たり判定を行う形表現している想定
	template<typename Shape>
	struct range_traits
	{
		//left,right,bottom,topの順
		static std::tuple<float, float, float, float> get_range(const Shape& s)
		{
			using vec2 = typename Shape::value_type;

			float left{ vec2_traits<vec2>::get_x(s[0]) };
			float right{ vec2_traits<vec2>::get_x(s[0]) };
			float bottom{ vec2_traits<vec2>::get_y(s[0]) };
			float top{ vec2_traits<vec2>::get_y(s[0]) };

			float x, y;
			for (size_t i = 1; i < s.size(); i++)
			{
				x = vec2_traits<vec2>::get_x(s[i]);
				y = vec2_traits<vec2>::get_y(s[i]);

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
}