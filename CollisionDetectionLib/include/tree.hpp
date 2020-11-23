#pragma once
#include<memory>
#include"policy.hpp"

namespace collision_detection
{
	template<typename T, typename HitPolicy , typename CollitionDetectionPolicy , int MAX_TREE_LEVEL>
	class tree_impl;

	//��
	template<typename T
		//�����������̏���
		, typename HitPolicy = hit_policy<T>
		//�����蔻��
		, typename CollitionDetectionPolicy = collision_detection_policy<T>
		//�ő僌�x��
		,int MAX_TREE_LEVEL = 5
	>
	class tree
	{
	public:
		tree();
		tree(unsigned int level, float left, float right, float bottom, float top);

		//Object�̖؂ւ̓o�^
		//������range_traits���g�p
		inline void resist(const T& o);

		//�؂𑖍��������蔻����s��
		//������collision_detection_traits,hit_traits���g�p
		inline void search();

		//�؂̃N���A
		inline void clear();

		//�Z�b�^
		inline void set_range(float left, float right, float bottom, float top);
		inline void set_level(unsigned int level);

		//�R�s�[�֎~
		tree(tree&) = delete;
		tree& operator=(const tree&) = delete;
		//���[�u�\
		tree(tree&&) = default;
		tree& operator=(tree&&) = default;

	private:
		//����
		std::unique_ptr<tree_impl<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>> m_tree_impl;
	};
}

#include"src/tree_impl.hpp"

