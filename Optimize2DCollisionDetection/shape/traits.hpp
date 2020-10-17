#pragma once
#include"../collision_detection/traits/collision_detection_traits.hpp"
#include"../collision_detection/traits/hit_traits.hpp"
#include"../collision_detection/traits/range_traits.hpp"
#include"../collision_detection/traits/shape_traits.hpp"
#include"shape.hpp"

#include<iostream>

namespace collision_detection
{
	//tree‚É“o˜^‚Å‚«‚é‚æ‚¤‚É‚»‚ê‚¼‚ê‚Ìtraits‚ğ“Áê‰»

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
	
	//‚¢‚ë‚¢‚ë•ÏX‚Å‚«‚é‚æ‚¤‚Éƒƒ“ƒoŠÖ”‚Íƒeƒ“ƒvƒŒ[ƒg‚É‚µ‚Ä‚¨‚­
	template<>
	struct collision_detection_traits<my::shape>
	{
		template<typename CollisionDetectionPolicy>
		static bool collision_detection(const my::shape& a, const my::shape& b)
		{
			return CollisionDetectionPolicy::collision_detection(a, b);
		}
	};

	class hit_cnt
	{
		static unsigned int m_cnt;

	public:
		static void add() { m_cnt++; }
		static unsigned int get() { return m_cnt; }
		static void clear() { m_cnt = 0; }
	};

	unsigned int hit_cnt::m_cnt = 0;

	//‚Æ‚è‚ ‚¦‚¸Õ“Ë‚µ‚½Shape‚Ì”‚ğ”‚¦‚é—\’è
	template<>
	struct hit_traits<my::shape>
	{
		static void hit(const my::shape& a, const my::shape& b)
		{
			hit_cnt::add();
			std::cout << "hit!\n";
			std::cout << "v1: ";
			for (const auto& v : a)
				std::cout << v.x << "," << v.y << "  ";
			a.size();
			std::cout << "\n";
			std::cout << "v2: ";
			for (const auto& v : b)
				std::cout << v.x << "," << v.y << "  ";
			std::cout << "\n\n";
			
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