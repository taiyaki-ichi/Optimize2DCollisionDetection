#pragma once

namespace collision_detection
{
	template<typename Object>
	struct hit_traits
	{
		//2��Object���������Ă���Ƃ��ɌĂяo�����
		static void hit(const Object&, const Object&);
	};
}