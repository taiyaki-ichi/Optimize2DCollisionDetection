#pragma once

namespace collision_detection
{
	template<typename T>
	struct shape_traits
	{
		//頂点数の取得
		inline static unsigned int get_vertex_num(const T&);

		//Spapeの頂点のx,y座標を取得
		//0からスタートで(vertex_num-1)までの数字がvertexNumの値として使用される
		inline static float get_vertex_x(const T&, unsigned int vertexNum);
		inline static float get_vertex_y(const T&, unsigned int vertexNum);
	};
}