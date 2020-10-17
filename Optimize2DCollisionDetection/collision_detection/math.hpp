#pragma once

namespace collision_detection
{
	//p1��p2�̊O�ς�z���W�����߂�
	inline constexpr float get_cross_z(float p1_x, float p1_y, float p2_x, float p2_y) noexcept
	{
		return p1_x * p2_y - p1_y * p2_x;
	}
}