#pragma once

namespace collision_detection
{
	template<typename Shape>
	struct shape_traits
	{
		//頂点数の取得
		inline static unsigned int get_vertex_num(const Shape&);

		//Spapeの頂点のx,y座標を取得
		//0からスタートで(vertex_num-1)までの数字がvertexNumの値として使用される
		inline static float get_vertex_x(const Shape&, unsigned int vertexNum);
		inline static float get_vertex_y(const Shape&, unsigned int vertexNum);
	};
}