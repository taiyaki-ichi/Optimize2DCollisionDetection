#include<iostream>
#include"shape/shape.hpp"
#include"collision_detection/tree.hpp"
#include"tree_impl/001/tree_impl.hpp"
#include"collsion_detection_policy/001.hpp"

int main()
{
	my::shape base{ { 1.f,1.f},{ -1.f,1.f},{ -1.f,-1.f},{ 1.f,-1.f} };
	std::vector<my::vec2f> moveVec{ {2.f,0.f},{10.f,0.f},{20.f,0.f},{-20.f,10.f},{-30.f,10.f},{-50.f,10.f} };
	std::vector<my::shape> s{};

	my::shape tmp{};
	for (auto move : moveVec)
	{
		tmp.clear();
		for (const auto& v : base)
			tmp.emplace_back(move + v);
		s.emplace_back(std::move(tmp));
	}

	collision_detection::tree<my::tree_imple001<my::shape, my::cd_001<my::shape>>> t{ 2,-100.f,100.f,-100.f,100.f };
	t.clear();
	collision_detection::hit_cnt::clear();
	for (const auto& shape : s)
		t.resist(shape);
	t.search();
	std::cout << "cnt:" << collision_detection::hit_cnt::get();
	

	return 0;
}