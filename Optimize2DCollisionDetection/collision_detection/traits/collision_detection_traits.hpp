#pragma once

namespace collision_detection
{
	template<typename Object>
	struct collision_detection_traits
	{
		//２つのObjectが当たっているかどうかの判定
		static bool collision_detection(const Object&, const Object&);
	};
}