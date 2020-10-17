#pragma once
#include"../collision_detection/math.hpp"
#include"../collision_detection/traits/shape_traits.hpp"

namespace my
{
	//namespace
	//{
		//“_p‚ªs‚Ì“à‘¤‚©‚Ç‚¤‚©
		template<typename Shape>
		inline bool is_inside_rect(float p_x, float p_y, const Shape& s)
		{
			using st = collision_detection::shape_traits<Shape>;
			unsigned int num = collision_detection::shape_traits<Shape>::get_vertex_num(s);
			for (int i = 0; i < num - 1; i++)
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

		//p1‚Æp2‚©‚ç‚È‚é’¼ü‚Æq1‚Æq2‚©‚ç‚È‚é’¼ü‚ÌŒğ·”»’è
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
	//}

	template<typename Shape>
	struct cd_001
	{
		static bool collision_detection(const Shape& a, const Shape& b)
		{

		}
	};
}