#pragma once
#include"traits.hpp"
#include"src/default_collision_detection_policy.hpp"

namespace collision_detection
{

	//���ꉻ���Ȃ���΃f�t�H���g�̓����蔻����g�p
	template<typename T>
	struct collision_detection_policy
	{
		inline static bool collision_detection(const T& a, const T& b) {
			
			//���_������Ă��邩�̂ݒ��ׂ�
			return default_collision_detection_policy<T>::collision_detection(a, b);
		}
	};


	//�������������̏���
	//���ꉻ���Ȃ���Ή������Ȃ�
	template<typename T>
	struct hit_policy
	{
		//2���Փ˂��Ă����ꍇ�Ăяo�����
		inline static void hit(const T&, const T&) {}
	};

}