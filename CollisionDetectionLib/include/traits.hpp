#pragma once
#include<utility>

namespace collision_detection
{
	//���p�`�̏����擾���邽�߂�
	template<typename T>
	struct shape_traits
	{
		//���_���̎擾
		static unsigned int get_vertex_num(const T&);

		//T�̒��_��x,y���W���擾
		//0����X�^�[�g��(vertex_num-1)�܂ł̐�����vertexNum�̒l�Ƃ��Ďg�p�����
		static float get_vertex_x(const T&, unsigned int vertexNum);
		static float get_vertex_y(const T&, unsigned int vertexNum);
	};

	//�؂̓o�^�Ɏg�p
	template<typename T>
	struct range_traits
	{
		//T�����S�Ɏ��܂�ł��邾���������͈͂�Ԃ�
		//left,right,bottom,top�̏�
		//�e���v���[�g����ꉻ���Ďg�p
		static std::tuple<float, float, float, float> get_range(const T&);
	};
}