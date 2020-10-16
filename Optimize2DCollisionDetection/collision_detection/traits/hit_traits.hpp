#pragma once

namespace collision_detection
{
	template<typename Object>
	struct hit_traits
	{
		//2つのObjectが当たっているときに呼び出される
		static void hit(const Object&, const Object&);
	};
}