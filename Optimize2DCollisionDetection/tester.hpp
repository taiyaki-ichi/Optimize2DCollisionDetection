#pragma once
#include"collision_detection/tree.hpp"
#include"timer.hpp"
#include"shape/shape.hpp"

namespace my
{
	struct result;
	struct test_data;

	//TreeImple��CollsionDetectionPolicy�Ŏ��̉�����Ă�Ǝv��
	template<typename TreeImple>
	class tester
	{
		collision_detection::tree<TreeImple,shape> m_tree;
		timer m_timer;

	public:
		//�v���̏���
		bool init();

		//�v���̊J�n
		//�߂�l�͌���
		result start(test_data&&);
	};
}