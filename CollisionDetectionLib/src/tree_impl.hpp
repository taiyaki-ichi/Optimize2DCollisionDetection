#pragma once
#include<array>
#include"utility.hpp"
#include"space_cell.hpp"
#include"include/traits.hpp"
#include"morton_number.hpp"
#include"include/tree.hpp"

namespace collision_detection
{
	template<typename T, typename HitPolicy, typename CollitionDetectionPolicy, int MAX_TREE_LEVEL>
	tree<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>::tree()
		:m_tree_impl{ nullptr }
	{
		m_tree_impl = std::make_unique<tree_impl<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>>();
	}

	template<typename T, typename HitPolicy, typename CollitionDetectionPolicy,int MAX_TREE_LEVEL>
	tree<T,HitPolicy,CollitionDetectionPolicy, MAX_TREE_LEVEL>::tree(unsigned int level, float left, float right, float bottom, float top)
		:m_tree_impl{ nullptr }
	{
		m_tree_impl = std::make_unique<tree_impl<T,HitPolicy,CollitionDetectionPolicy,MAX_TREE_LEVEL>>(level, left, right, bottom, top);
	}

	template<typename T, typename HitPolicy, typename CollitionDetectionPolicy, int MAX_TREE_LEVEL>
	void tree<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>::set_range(float left, float right, float bottom, float top) {
		m_tree_impl->set_range(left, right, bottom, top);
	}

	template<typename T, typename HitPolicy, typename CollitionDetectionPolicy, int MAX_TREE_LEVEL>
	void tree<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>::set_level(unsigned int level) {
		m_tree_impl->set_level(level);
	}

	template<typename T, typename HitPolicy, typename CollitionDetectionPolicy,int MAX_TREE_LEVEL>
	void tree<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>::resist(const T& object) {
		m_tree_impl->regist(object);
	}

	template<typename T, typename HitPolicy, typename CollitionDetectionPolicy,int MAX_TREE_LEVEL>
	void tree<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>::search() {
		m_tree_impl->search();
	}

	template<typename T, typename HitPolicy, typename CollitionDetectionPolicy,int MAX_TREE_LEVEL>
	void tree<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>::clear() {
		m_tree_impl->clear();
	}


	template<typename T
			,typename Hit
			,typename CollisionDetection
			,int MAX_TREE_LEVEL
	>
	class tree_impl
	{
	public:
		//最大SpeaceNum
		static constexpr unsigned int MAX_SPACECELL_NUM = collision_detection::pow_of_four_sum(MAX_TREE_LEVEL);

	private:
		std::array<space_cell<T>, MAX_SPACECELL_NUM> m_space_cell_array;

		//オブジェクトの数、clearでリセット
		unsigned int m_object_num;

		//モートン番号用の情報
		float m_range_left;
		float m_range_bottom;
		float m_range_unit_width;
		float m_range_unit_height;
		unsigned int m_tree_level;

	public:
		tree_impl()
			:m_space_cell_array{}
			, m_tree_level{}
			, m_range_left{}
			, m_range_bottom{}
			, m_range_unit_width{}
			, m_range_unit_height{}
			, m_object_num{}
		{}

		tree_impl(unsigned int level, float left, float right, float bottom, float top)
			:m_space_cell_array{}
			, m_tree_level{ level }
			, m_range_left{ left }
			, m_range_bottom{ bottom }
			, m_range_unit_width{ (right - left) / (1 << level) }
			, m_range_unit_height{ (top - bottom) / (1 << level) }
			, m_object_num{}
		{}

		//セッタ
		void set_range(float left, float right, float bottom, float top)
		{
			m_range_left = left;
			m_range_bottom = bottom;
			m_range_unit_width = (right - left) / (1 << m_tree_level);
			m_range_unit_height = (top - bottom) / (1 << m_tree_level);
		}
		void set_level(unsigned int level)
		{
			float right = m_range_unit_width * (1 << m_tree_level) + m_range_left;
			float top = m_range_unit_height * (1 << m_tree_level) + m_range_bottom;

			m_tree_level = level;
			m_range_unit_width = (right - m_range_left) / (1 << m_tree_level);
			m_range_unit_height = (top - m_range_bottom) / (1 << m_tree_level);
		}

		void regist(const T& obj)
		{

			auto [left, right, bottom, top] = range_traits<T>::get_range(obj);
			auto number = get_morton_number(left, right, bottom, top,
				m_range_left, m_range_bottom, m_range_unit_width, m_range_unit_height, m_tree_level);


			//モートン番号が有効な値の場合
			if (0 <= number && number < MAX_SPACECELL_NUM)
			{
				m_space_cell_array[number].resist(obj);
				//カウントしておく、search開始時にスタックの容量確保用
				m_object_num++;
				//フラグを挙げておく
				up_has_object_flag(number);
			}
		}

		void search()
		{
			std::vector<const T*> stack{};
			//容量確保
			stack.reserve(m_object_num);
			recursion_search_tree(std::move(stack), 0);
		}

		void clear()
		{
			//フラグを全部下げる
			down_has_object_flag(0);
			for (auto& s : m_space_cell_array)
				s.clear();
			m_object_num = 0;
		}

	private:
		//SpacecellのHasLinerObjectFlagを全部下げる
		void down_has_object_flag(int spaceNum) {

			if (m_space_cell_array[spaceNum].get_has_object_flag()) {
				m_space_cell_array[spaceNum].set_has_object_flag(false);
				for (int i = 0; i < 4; i++) {
					int childNum = spaceNum * 4 + 1 + i;
					if (childNum < MAX_SPACECELL_NUM && m_space_cell_array[childNum].get_has_object_flag())
						down_has_object_flag(childNum);

				}
			}
		}

		//全部上げる
		void up_has_object_flag(int spaceNum)
		{
			while (!m_space_cell_array[spaceNum].get_has_object_flag()) {
				m_space_cell_array[spaceNum].set_has_object_flag(true);

				spaceNum = (spaceNum - 1) >> 2;
				if (spaceNum < 0)
					break;
			}
		}

		//実際に当たり判定を行いhitを適用
		void do_collision_detection(const T* a, const T* b) {
			if (CollisionDetection::collision_detection(*a, *b))
				Hit::hit(*a, *b);
		}

		//再帰して木の走査
		std::vector<const T*> recursion_search_tree(std::vector<const T*> stack, unsigned int spaceCellNum)
		{
			unsigned int obj_index1, obj_index2;
			for (obj_index1 = 0; obj_index1 < m_space_cell_array[spaceCellNum].size(); obj_index1++)
			{
				//同じ空間に所属しているObject同士
				for (obj_index2 = obj_index1 + 1; obj_index2 < m_space_cell_array[spaceCellNum].size(); obj_index2++)
				{
					do_collision_detection(m_space_cell_array[spaceCellNum][obj_index1], m_space_cell_array[spaceCellNum][obj_index2]);
				}

				//spaceCellNumより上位の空間に所属しているObject同士
				if (!stack.empty())
					for (const auto obj : stack)
						do_collision_detection(m_space_cell_array[spaceCellNum][obj_index1], obj);

			}

			//stackに追加した分を記録しておく
			bool isAddThisSpaceLinerObject = false;
			int addLinerObjectNum = 0;

			for (int i = 0; i < 4; i++)
			{
				int nextSpaceCellNum = spaceCellNum * 4 + 1 + i;
				if (nextSpaceCellNum < MAX_SPACECELL_NUM && m_space_cell_array[nextSpaceCellNum].get_has_object_flag())
				{
					if (!isAddThisSpaceLinerObject) {

						for (obj_index1 = 0; obj_index1 < m_space_cell_array[spaceCellNum].size(); obj_index1++) {
							stack.emplace_back(m_space_cell_array[spaceCellNum][obj_index1]);
							//後でstackから取り出すのでカウントしておく
							addLinerObjectNum++;
						}
					}
					isAddThisSpaceLinerObject = true;

					//もぐる
					stack = recursion_search_tree(std::move(stack), nextSpaceCellNum);
				}
			}

			//戻ってきたときに追加した分を削除
			if (isAddThisSpaceLinerObject)
				for (int i = 0; i < addLinerObjectNum; i++)
					stack.pop_back();

			return std::move(stack);
		}

	};
}