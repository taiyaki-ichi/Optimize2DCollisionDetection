#pragma once

namespace collision_detection
{
	template<typename Object>
	struct collision_detection_traits
	{
		//�Q��Object���������Ă��邩�ǂ����̔���
		//�e���v���[�g����ꉻ���Ďg�p
		static bool collision_detection(const Object&, const Object&);
	};
}