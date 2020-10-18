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
		bool set_data(const std::string& file_name)
		{
			std::ifstream f{ "../data/" + file_name + ".txt" };

			if (!f)
				return false;

			m_shape_data.clear();

			int shape_num;
			f >> shape_num;
			m_shape_data.reserve(shape_num);

			int vert_num;
			float tmp_x, tmp_y;
			my::shape tmp_shape{};

			int i, j;
			for (i = 0; i < shape_num; i++)
			{
				tmp_shape.clear();

				f >> vert_num;
				for (j = 0; j < vert_num; j++)
				{
					f >> tmp_x;
					f >> tmp_y;
					tmp_shape.emplace_back(my::vec2f{ tmp_x,tmp_y });
				}

				m_shape_data.emplace_back(std::move(tmp_shape));
			}

			/*
			for (auto& s : m_shape_data) {
				for (auto v : s)
					std::cout << " (" << v.x << "," << v.y << ") ";
				std::cout << "\n";
			}
			std::cout << m_shape_data.size();
			*/

			return true;
		}

		//計測の開始
		//戻り値は結果
		unsigned long do_test()
		{
			m_timer.clear();
			m_timer.do_test();

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