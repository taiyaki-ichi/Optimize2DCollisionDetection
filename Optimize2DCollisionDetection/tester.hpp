#pragma once
#include<iostream>
#include<fstream>
#include"collision_detection/tree.hpp"
#include"timer.hpp"
#include"shape/shape.hpp"
#include"shape/traits.hpp"

namespace my
{
	
	//�^����ꂽ�f�[�^��60�񓖂��蔻����s�����Ԃ𑪒�
	//TreeImple��CollsionDetectionPolicy�Ŏ��̉�����Ă�Ǝv��
	template<typename TreeImple>
	class tester
	{
		std::vector<my::shape> m_shape_data;
		collision_detection::tree<TreeImple,shape> m_tree;
		timer m_timer;

	public:
		tester(unsigned int level, float left, float right, float bottom, float top)
			:m_tree{level,left,right,bottom,top}
			, m_timer{}
			, m_shape_data{}
		{}

		//�v���̏���
		void set_data(const std::vector<shape>& data)
		{
			m_shape_data = data;
		}

		//�v���̊J�n
		//�߂�l�͌���
		std::pair<unsigned long,std::vector<unsigned int>> do_test()
		{
			//�e�X�g�̉�
			constexpr unsigned int test_num = 60;

			std::vector<unsigned int> cnt(test_num);

			m_timer.clear();
			m_timer.do_test();

			//�Ƃ��60��ɂ��Ă���
			for (int i = 0; i < test_num; i++)
			{
				collision_detection::hit_cnt::clear();

				//�؂��N���A
				m_tree.clear();

				//�؂ւ̓o�^
				for (const auto& shape : m_shape_data)
					m_tree.resist(shape);
				
				//�؂̑���
				m_tree.search();

				cnt[i] = collision_detection::hit_cnt::get();
			}

			unsigned long time = m_timer.get_ms();

			return { time,cnt };
		}
	};
}