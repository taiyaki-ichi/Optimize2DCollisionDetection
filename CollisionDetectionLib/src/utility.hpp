#pragma once

namespace collision_detection
{

	constexpr unsigned long pow_of_four(unsigned int n)
	{
		if (n == 0)
			return 1;
		else
			return 4 * pow_of_four(n - 1);
	}

	//�S�̊K��̍��v
	constexpr unsigned long pow_of_four_sum(unsigned int n)
	{
		return (pow_of_four(n + 1) - 1) / 3;
	}

	//p1��p2�̊O�ς�z���W�����߂�
	inline constexpr float get_cross_z(float p1_x, float p1_y, float p2_x, float p2_y) noexcept
	{
		return p1_x * p2_y - p1_y * p2_x;
	}
}