#pragma once
#include<tuple>

namespace collision_detection
{
	template<typename Object>
	struct range_traits
	{
		//Object�����S�Ɏ��܂�ł��邾���������͈͂�Ԃ�
		//left,right,bottom,top�̏�
		static std::tuple<float, float, float, float> get_range(const Object&);
	};
}