#pragma once

namespace collision_detection
{
	//p1‚Æp2‚ÌŠOÏ‚ÌzÀ•W‚ğ‹‚ß‚é
	inline constexpr float get_cross_z(float p1_x, float p1_y, float p2_x, float p2_y) noexcept
	{
		return p1_x * p2_y - p1_y * p2_x;
	}
}