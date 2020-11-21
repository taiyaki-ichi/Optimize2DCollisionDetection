#pragma once
#include<utility>

namespace collision_detection
{
	//多角形の情報を取得するための
	template<typename T>
	struct shape_traits
	{
		//頂点数の取得
		inline static unsigned int get_vertex_num(const T&);

		//Tの頂点のx,y座標を取得
		//0からスタートで(vertex_num-1)までの数字がvertexNumの値として使用される
		inline static float get_vertex_x(const T&, unsigned int vertexNum);
		inline static float get_vertex_y(const T&, unsigned int vertexNum);
	};

	//木の登録に使用
	template<typename T>
	struct range_traits
	{
		//Tが完全に収まるできるだけ小さい範囲を返す
		//left,right,bottom,topの順
		//テンプレートを特殊化して使用
		inline static std::tuple<float, float, float, float> get_range(const T&);
	};
}