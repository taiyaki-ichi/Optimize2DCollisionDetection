#pragma once
#include<iostream>
#include<fstream>
#include"collision_detection/tree.hpp"
#include"timer.hpp"
#include"shape/shape.hpp"
#include"shape/traits.hpp"

namespace my
{
	
	//与えられたデータで60回当たり判定を行い時間を測定
	//TreeImpleはCollsionDetectionPolicyで実体化されてると思う
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

		//計測の準備
		void set_data(const std::vector<shape>& data)
		{
			m_shape_data = data;
		}

		//計測の開始
		//戻り値は結果
		unsigned long do_test()
		{
			m_timer.clear();
			m_timer.do_test();

			//とりま60回にしておく
			for (int i = 0; i < 60; i++)
			{
				//collision_detection::hit_cnt::clear();

				//木をクリア
				m_tree.clear();

				//木への登録
				for (const auto& shape : m_shape_data)
					m_tree.resist(shape);
				
				//木の走査
				m_tree.search();

				//std::cout << collision_detection::hit_cnt::get() << "\n";
			}

			return m_timer.get_ms();
		}
	};
}