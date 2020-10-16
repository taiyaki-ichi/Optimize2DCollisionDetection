#pragma once

namespace collision_detection
{
	template<typename Object>
	struct hit_traits
	{
		//2‚Â‚ÌObject‚ª“–‚½‚Á‚Ä‚¢‚é‚Æ‚«‚ÉŒÄ‚Ño‚³‚ê‚é
		static void hit(const Object&, const Object&);
	};
}