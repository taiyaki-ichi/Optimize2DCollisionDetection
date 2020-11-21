#pragma once
#include"include/traits.hpp"
#include"utility.hpp"

namespace collision_detection
{
	namespace
	{
		//点pがsの内側かどうか
		template<typename T>
		inline bool is_inside_rect(float p_x, float p_y, const T& s)
		{
			using st = collision_detection::shape_traits<T>;
			unsigned int num = st::get_vertex_num(s);
			for (unsigned i = 0; i < num - 1; i++)
			{
				if (get_cross_z(
					st::get_vertex_x(s, i) - st::get_vertex_x(s, i + 1), st::get_vertex_y(s, i) - st::get_vertex_y(s, i + 1),
					p_x - st::get_vertex_x(s, i), p_y - st::get_vertex_y(s, i)) > 0)
					return false;
			}
			if (get_cross_z(
				st::get_vertex_x(s, num - 1) - st::get_vertex_x(s, 0), st::get_vertex_y(s, num - 1) - st::get_vertex_y(s, 0),
				p_x - st::get_vertex_x(s, num - 1), p_y - st::get_vertex_y(s, num - 1)) > 0)
				return false;

			return true;
		}

	}

	//当たり判定のデフォ
	template<typename T>
	struct default_collision_detection_policy
	{
		inline static bool collision_detection(const T& a, const T& b)
		{
			using st = collision_detection::shape_traits<T>;
			unsigned int aNum = st::get_vertex_num(a);
			unsigned int bNum = st::get_vertex_num(b);

			//点が含まれているか
			for (unsigned int i = 0; i < aNum; i++)
				if (is_inside_rect(st::get_vertex_x(a, i), st::get_vertex_y(a, i), b))
					return true;
			for (unsigned int i = 0; i < bNum; i++)
				if (is_inside_rect(st::get_vertex_x(b, i), st::get_vertex_y(b, i), a))
					return true;

			return false;
		}
	};
}