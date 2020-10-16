#pragma once

namespace collision_detection
{
	template<typename Object>
	struct collision_detection_traits
	{
		//‚Q‚Â‚ÌObject‚ª“–‚½‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©‚Ì”»’è
		static bool collision_detection(const Object&, const Object&);
	};
}