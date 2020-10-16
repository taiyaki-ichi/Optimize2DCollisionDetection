#pragma once
#include<tuple>

namespace collision_detection
{
	template<typename Object>
	struct range_traits
	{
		//Objectが完全に収まるできるだけ小さい範囲を返す
		//left,right,bottom,topの順
		//テンプレートを特殊化して使用
		static std::tuple<float, float, float, float> get_range(const Object&);
	};
}