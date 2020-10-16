#pragma once
#include<tuple>

namespace collision_detection
{
	template<typename Object>
	struct range_traits
	{
		//Object‚ªŠ®‘S‚Éû‚Ü‚é‚Å‚«‚é‚¾‚¯¬‚³‚¢”ÍˆÍ‚ğ•Ô‚·
		//left,right,bottom,top‚Ì‡
		static std::tuple<float, float, float, float> get_range(const Object&);
	};
}