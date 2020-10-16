#pragma once
#include"collision_detection/tree.hpp"
#include"timer.hpp"
#include"shape/shape.hpp"

namespace my
{
	struct result;
	struct test_data;

	//TreeImpleはCollsionDetectionPolicyで実体化されてると思う
	template<typename TreeImple>
	class tester
	{
		collision_detection::tree<TreeImple,shape> m_tree;
		timer m_timer;

	public:
		//計測の準備
		bool init();

		//計測の開始
		//戻り値は結果
		result start(test_data&&);
	};
}