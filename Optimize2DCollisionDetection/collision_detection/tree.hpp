#pragma once

namespace collision_detection
{
	//TreeImpl��init,resist,search,clear������
	//�v������r���邽�ߎ��������͓���ւ�����悤�Ƀe���v���[�g�ɂ����B
	//Object��range_traits,collision_detection_traits,hit_traits�𖞂���
	template<typename TreeImpl,typename Object>
	class tree
	{
		TreeImpl m_tree_impl;

	public:
		//������
		inline bool init() {
			m_tree_impl.init();
		}

		//Object�̖؂ւ̓o�^
		//������range_traits���g�p
		inline void resist(const Object& o) {
			m_tree_impl.resist(o);
		}

		//�؂𑖍��������蔻����s��
		//������collision_detection_traits,hit_traits���g�p
		inline void search() {
			m_tree_impl.search();
		}

		//�؂̃N���A
		inline void clear() {
			m_tree_impl.clear();
		}
	};
}