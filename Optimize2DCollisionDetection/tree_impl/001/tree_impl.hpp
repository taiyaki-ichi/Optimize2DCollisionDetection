#pragma once
#include"../../collision_detection/traits/collision_detection_traits.hpp"
#include"../../collision_detection/traits/hit_traits.hpp"
#include"../../collision_detection/traits/range_traits.hpp"

namespace my
{
	template<typename Object,
		typename CollisionDetection = collision_detection::collision_detection_traits<Object>,
		typename Hit = collision_detection::hit_traits<Object>,
		typename Range = collision_detection::range_traits<Object>>
		class tree_imple001
	{

	public:
		//tree—p
		using value_type = Object;
	};
}