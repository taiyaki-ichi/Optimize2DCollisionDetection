#pragma once
#include"../collision_detection/math.hpp"
#include"../collision_detection/traits/shape_traits.hpp"

namespace my
{
	namespace
	{
		//点pがsの内側かどうか
		template<typename T>
		inline bool is_inside_rect(float p_x, float p_y, const T& s)
		{
			using st = collision_detection::shape_traits<T>;
			unsigned int num = collision_detection::shape_traits<T>::get_vertex_num(s);
			for (unsigned i = 0; i < num - 1; i++)
			{
				if (collision_detection::get_cross_z(
					st::get_vertex_x(s, i) - st::get_vertex_x(s, i + 1), st::get_vertex_y(s, i) - st::get_vertex_y(s, i + 1),
					p_x - st::get_vertex_x(s, i), p_y - st::get_vertex_y(s, i)) > 0)
					return false;
			}
			if (collision_detection::get_cross_z(
				st::get_vertex_x(s, num - 1) - st::get_vertex_x(s, 0), st::get_vertex_y(s, num - 1) - st::get_vertex_y(s, 0),
				p_x - st::get_vertex_x(s, num - 1), p_y - st::get_vertex_y(s, num - 1)) > 0)
				return false;
			
			return true;
		}

		//p1とp2からなる直線とq1とq2からなる直線の交差判定
		inline bool is_crossing(float p1_x, float p1_y, float p2_x, float p2_y, float q1_x, float q1_y, float q2_x, float q2_y)
		{
			using namespace collision_detection;

			float tmp1 = get_cross_z(p2_x - p1_x, p2_y - p1_y, q1_x - p1_x, q1_y - p1_y);
			float tmp2 = get_cross_z(p2_x - p1_x, p2_y - p1_y, q2_x - p1_x, q2_y - p1_y);
			float tmp3 = get_cross_z(q2_x - q1_x, q2_y - q1_y, p1_x - q1_x, p1_y - q1_y);
			float tmp4 = get_cross_z(q2_x - q1_x, q2_y - q1_y, p2_x - q1_x, p2_y - q1_y);

			if (tmp1 * tmp2 < 0 && tmp3 * tmp4 < 0)
				return true;
			else
				return false;
		}
	}

	template<typename T>
	struct cd_001
	{
		static bool collision_detection(const T& a, const T& b)
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
					
			//辺が交差しているかどうか
			unsigned int a_j, b_j;
			for(unsigned int a_i=0;a_i<aNum;a_i++)
				for (unsigned int b_i = 0; b_i < bNum; b_i++)
				{
					a_j = (a_i == aNum - 1) ? 0 : a_i + 1;
					b_j = (b_i == bNum - 1) ? 0 : b_i + 1;

					if (is_crossing(st::get_vertex_x(a, a_i), st::get_vertex_y(a, a_i), st::get_vertex_x(a, a_j), st::get_vertex_y(a, a_j),
						st::get_vertex_x(b, b_i), st::get_vertex_y(b, b_i), st::get_vertex_x(b, b_j), st::get_vertex_y(b, b_j)))
						return true;
				}

			return false;
		}
	};
}