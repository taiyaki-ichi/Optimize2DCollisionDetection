#pragma once
#include"../../collision_detection/traits/collision_detection_traits.hpp"
#include"../../collision_detection/traits/hit_traits.hpp"
#include"../../collision_detection/traits/range_traits.hpp"
#include"space_cell.hpp"
#include"../../collision_detection/morton_number.hpp"
#include<vector>

#include"../../shape/traits.hpp"

namespace my
{
	template<typename Object,
		typename CollisionDetection = typename collision_detection::collision_detection_traits<Object>,
		typename Hit = typename collision_detection::hit_traits<Object>,
		typename Range = typename collision_detection::range_traits<Object>>
		class tree_imple001
	{
	public:
		//tree用
		using value_type = Object;
		//最大レベル
		static constexpr unsigned int MAX_TREE_LEVEL = 5;
		//最大SpeaceNum
		static constexpr unsigned int MAX_SPACECELL_NUM = collision_detection::pow_of_four_sum(MAX_TREE_LEVEL);

	private:
		space_cell<Object>* m_space_cell_array[MAX_SPACECELL_NUM];
		liner_object_container<Object> m_liner_object_container;
		//一次的なスタック
		std::vector<liner_object<Object>*> m_liner_object_tmp_stack;

		//モートン番号用の情報
		const float m_range_left;
		const float m_range_bottom;
		const float m_range_unit_width;
		const float m_range_unit_height;
		const unsigned int m_tree_level;

	public:
		constexpr tree_imple001(unsigned int level, float left, float right, float bottom, float top)
			:m_space_cell_array{}
			, m_liner_object_container{50}
			, m_liner_object_tmp_stack{}
			, m_tree_level{level}
			, m_range_left{left}
			, m_range_bottom{bottom}
			, m_range_unit_width{(right-left)/(1<<level)}
			, m_range_unit_height{(top-bottom)/(1<<level)}
		{
			for (unsigned int i = 0; i < MAX_SPACECELL_NUM; i++)
				m_space_cell_array[i] = new space_cell<Object>();
		}
		~tree_imple001()
		{
			for (unsigned int i = 0; i < MAX_SPACECELL_NUM; i++)
				if (m_space_cell_array[i])
					delete m_space_cell_array[i];
		}

		void resist(const Object& obj)
		{
			auto [left, right, bottom, top] = Range::get_range(obj);
			auto number = collision_detection::get_morton_number(left, right, bottom, top,
				m_range_left, m_range_bottom, m_range_unit_width, m_range_unit_height, m_tree_level);

			std::cout << "num: " << number << "\n";

			if (0 <= number && number < MAX_SPACECELL_NUM)
			{
				auto lo = m_liner_object_container.get_liner_object(obj);
				convey_residt_liner_object(number);
				m_space_cell_array[number]->push(lo);
			}
		}

		void search()
		{
			m_liner_object_tmp_stack.clear();
			recursion_search_tree(0);
		}

		void clear()
		{
			reset_has_liner_object(0);
			m_liner_object_container.clear();
		}

	private:
		//SpaceCellのhasLinerObjectFlagを立てる
		void convey_residt_liner_object(int spaceNum) {
			while (!m_space_cell_array[spaceNum]->m_has_liner_object) {
				m_space_cell_array[spaceNum]->m_has_liner_object = true;

				spaceNum = (spaceNum - 1) >> 2;
				if (spaceNum < 0)
					break;
			}
		}

		//SpacecellのHasLinerObjectFlagを全部下げる
		void reset_has_liner_object(int spaceNum) {

			if (m_space_cell_array[spaceNum]->m_has_liner_object) {
				m_space_cell_array[spaceNum]->m_has_liner_object = false;
				for (int i = 0; i < 4; i++) {
					int childNum = spaceNum * 4 + 1 + i;
					if (childNum < MAX_SPACECELL_NUM && m_space_cell_array[childNum]->m_has_liner_object)
						reset_has_liner_object(childNum);

				}
			}
		}

		void do_collision_detection(liner_object<Object>* a,liner_object<Object>* b)
		{
			if (CollisionDetection::collision_detection(*a->get_ptr(), *b->get_ptr()))
				Hit::hit(*a->get_ptr(), *b->get_ptr());
		}

		void recursion_search_tree(unsigned int spaceCellNum)
		{
			liner_object<Object>* linerObj1 = m_space_cell_array[spaceCellNum]->get_first_liner_object();
			liner_object<Object>* linerObj2 = nullptr;

			while (linerObj1)
			{
				linerObj2 = linerObj1->m_next_liner_object;
				while (linerObj2)
				{
					do_collision_detection(linerObj1, linerObj2);
					linerObj2 = linerObj2->m_next_liner_object;
				}

				if (!m_liner_object_tmp_stack.empty())
					for (auto linerObj : m_liner_object_tmp_stack)
						do_collision_detection(linerObj1, linerObj);

				linerObj1 = linerObj1->m_next_liner_object;
			}

			bool isAddThisSpaceLinerObject = false;
			int addLinerObjectNum = 0;

			for (int i = 0; i < 4; i++)
			{
				int nextSpaceCellNum = spaceCellNum * 4 + 1 + i;
				if (nextSpaceCellNum < MAX_SPACECELL_NUM && m_space_cell_array[nextSpaceCellNum]->m_has_liner_object)
				{
					if (!isAddThisSpaceLinerObject) {
						linerObj1 = m_space_cell_array[spaceCellNum]->get_first_liner_object();
						while (linerObj1) {
							m_liner_object_tmp_stack.emplace_back(linerObj1);
							addLinerObjectNum++;
							linerObj1 = linerObj1->m_next_liner_object;
						}
					}
					isAddThisSpaceLinerObject = true;

					recursion_search_tree(nextSpaceCellNum);
				}
			}

			if (isAddThisSpaceLinerObject)
				for (int i = 0; i < addLinerObjectNum; i++)
					m_liner_object_tmp_stack.pop_back();
			
		}
	};
}