#pragma once
#include"utility.hpp"

namespace collision_detection
{
	namespace
	{
		// �r�b�g����
		inline constexpr unsigned long bit_separate_32(unsigned long n)
		{
			n = (n | (n << 8)) & 0x00ff00ff;
			n = (n | (n << 4)) & 0x0f0f0f0f;
			n = (n | (n << 2)) & 0x33333333;
			return (n | (n << 1)) & 0x55555555;
		}

		// 2D���[�g����Ԕԍ��Z�o�֐�
		inline constexpr unsigned short get_2D_morton_number(unsigned short x, unsigned short y)
		{
			return static_cast<unsigned short>(bit_separate_32(x) | (bit_separate_32(y) << 1));
		}

		// ���W�����`4���ؗv�f�ԍ��ϊ��֐�
		inline constexpr unsigned long get_point_elem(float x, float y, float rangeLeft, float rangeBottom, float rangeUnitW, float rangeUnitH)
		{
			return get_2D_morton_number(static_cast<unsigned short>((x - rangeLeft) / rangeUnitW), static_cast<unsigned short>((y - rangeBottom) / rangeUnitH));
		}
	}


	//�{��
	//��������E��ւ�����Z���㉺���]�������ԂŔԍ����U����
	inline constexpr unsigned long get_morton_number(float left, float right, float bottom, float top,
		float rangeLeft, float rangeBottom, float rangeUnitW, float rangeUnitH, unsigned int treeLevel)
	{
		//��Ԃ𕪊����Ȃ��ꍇ�͂��ׂ�0
		if (treeLevel == 0)
			return 0;

		// �ŏ����x���ɂ�����e���ʒu���Z�o
		unsigned long LT = get_point_elem(left, bottom, rangeLeft, rangeBottom, rangeUnitW, rangeUnitH);
		unsigned long RB = get_point_elem(right, top, rangeLeft, rangeBottom, rangeUnitW, rangeUnitH);

		// ��Ԕԍ��̔r���I�_���a����
		// �������x�����Z�o
		unsigned long Def = RB ^ LT;
		unsigned int HiLevel = 0;
		unsigned int i{};
		unsigned long Check{};
		for (i = 0; i < treeLevel; i++)
		{
			Check = (Def >> (i * 2)) & 0x3;
			if (Check != 0)
				HiLevel = i + 1;
		}
		unsigned long SpaceNum = RB >> (HiLevel * 2);
		unsigned long AddNum = (pow_of_four(treeLevel - HiLevel) - 1) / 3;
		SpaceNum += AddNum;

		if (SpaceNum > pow_of_four_sum(treeLevel))
			return 0xffffffff;

		return SpaceNum;
	}
}