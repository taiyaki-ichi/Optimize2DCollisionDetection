#pragma once

namespace collision_detection
{
	template<typename Shape>
	struct shape_traits
	{
		//���_���̎擾
		inline static unsigned int get_vertex_num(const Shape&);

		//Spape�̒��_��x,y���W���擾
		//0����X�^�[�g��(vertex_num-1)�܂ł̐�����vertexNum�̒l�Ƃ��Ďg�p�����
		inline static float get_vertex_x(const Shape&, unsigned int vertexNum);
		inline static float get_vertex_y(const Shape&, unsigned int vertexNum);
	};
}