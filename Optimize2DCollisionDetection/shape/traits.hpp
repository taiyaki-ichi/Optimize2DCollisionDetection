#pragma once
#include"../collision_detection/traits/collision_detection_traits.hpp"
#include"../collision_detection/traits/hit_traits.hpp"
#include"../collision_detection/traits/range_traits.hpp"
#include"shape.hpp"

#include<iostream>

namespace collision_detection
{
	//tree‚É“o˜^‚Å‚«‚é‚æ‚¤‚É‚»‚ê‚¼‚ê‚Ìtraits‚ð“ÁŽê‰»

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
	struct collision_detection_traits<my::shape>
	{
		template<typename CollisionDetectionPolicy>
		static bool collision_detection(const my::shape& a, const my::shape& b)
		{
			return CollisionDetectionPolicy::collision_detection(a, b);
		}
	};

	template<>
	struct hit_traits<my::shape>
	{
		static void hit(const my::shape& a, const my::shape& b)
		{
			std::cout << "hit!\n";
		}
	};

}