#pragma once

namespace collision_detection
{
	template<typename Object>
	struct hit_traits
	{
		//2��Object���������Ă���Ƃ��ɌĂяo�����
		//�e���v���[�g����ꉻ���Ďg�p
		static void hit(const Object&, const Object&);
	};
}