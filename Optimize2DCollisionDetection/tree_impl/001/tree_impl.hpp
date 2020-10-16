#pragma once
#include"../../collision_detection/traits/collision_detection_traits.hpp"
#include"../../collision_detection/traits/hit_traits.hpp"
#include"../../collision_detection/traits/range_traits.hpp"
#include"space_cell.hpp"
#include"../../collision_detection/morton_number.hpp"
#include<vector>

namespace my
{
	template<typename Object,
		typename CollisionDetection = collision_detection::collision_detection_traits<Object>,
		typename Hit = collision_detection::hit_traits<Object>,
		typename Range = collision_detection::range_traits<Object>>
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
		SpaceCell<Object>* m_space_cell_array[MAX_SPACECELL_NUM];
		LinerObjectContainer<Object> m_liner_object_container;
		//一次的なスタック
		std::vector<LinerObject<Object>*> m_liner_object_tmp_stack;

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
			, m_range_unit_height{(bottom-top)/(1<<level)}
		{
			for (unsigned int i = 0; i < MAX_SPACECELL_NUM; i++)
				m_space_cell_array[i] = new SpaceCell<Object>();
		}
		~tree_imple001()
		{
			for (unsigned int i = 0; i < MAX_SPACECELL_NUM; i++)
				if (m_space_cell_array[i])
					delete m_space_cell_array[i];
		}

		void resist(const Object& obj)
		{
			const auto& lo = m_liner_object_container.GetLinerObject(obj);
			auto [left, right, bottom, top] = Range::get_range(obj);
			auto number = collision_detection::get_morton_number(left, right, bottom, top,
				m_range_left, m_range_bottom, m_range_unit_width, m_range_unit_height, m_tree_level);

			ConveyResidtLinerObject(number);
			m_space_cell_array[number]->Push(&lo);
		}

		void search()
		{
			m_liner_object_tmp_stack.clear();
			RecursionSearchTree(0);
		}

		void clear()
		{
			ResetHasLinerObject(0);
			m_liner_object_container.Clear();
		}

	private:
		//SpaceCellのhasLinerObjectFlagを立てる
		void ConveyResidtLinerObject(int spaceNum) {
			while (!m_space_cell_array[spaceNum]->mHasLinerObject) {
				m_space_cell_array[spaceNum]->mHasLinerObject = true;

				spaceNum = (spaceNum - 1) >> 2;
				if (spaceNum < 0)
					break;
			}
		}

		//SpacecellのHasLinerObjectFlagを全部下げる
		void ResetHasLinerObject(int spaceNum) {

			if (m_space_cell_array[spaceNum]->mHasLinerObject) {
				m_space_cell_array[spaceNum]->mHasLinerObject = false;
				for (int i = 0; i < 4; i++) {
					int childNum = spaceNum * 4 + 1 + i;
					if (childNum < MAX_SPACECELL_NUM && m_space_cell_array[childNum]->mHasLinerObject)
						ResetHasLinerObject(childNum);

				}
			}
		}

		void RecursionSearchTree(unsigned int speaceCellNum)
		{

			
		}
	};
}