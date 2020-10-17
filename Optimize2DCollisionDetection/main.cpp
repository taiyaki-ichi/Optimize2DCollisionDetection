#include<iostream>
#include"shape/shape.hpp"
#include"collision_detection/tree.hpp"
#include"tree_impl/001/tree_impl.hpp"
#include"collsion_detection_policy/001.hpp"

struct hoge {
	static bool collision_detection(const my::shape&, const my::shape&) {
		return true;
	}
};


int main()
{
	my::shape base{ { 1.f,1.f},{ -1.f,1.f},{ -1.f,-1.f},{ 1.f,-1.f} };
	std::vector<my::vec2f> moveVec{ {2.f,0.f},{3.f,0.f},{5.f,0.f},{-2.f,10.f},{-3.f,10.f},{-5.f,10.f} };
	std::vector<my::shape> s{};

	if (my::is_crossing(0.f, 0.f, 2.f, 2.f, 0.f, 1.f, 2.f, 1.f))
		std::cout << "a";
	if (my::is_crossing(0.f, 0.f, -2.f, 2.f, 0.f, 1.f, 2.f, 1.f))
		std::cout << "b";
	if (my::is_inside_rect(0.f, 0.f, base))
		std::cout << "c";
	if (my::is_inside_rect(10.f, 0.f, base))
		std::cout << "d";

	/*
	my::shape tmp{};
	for (auto move : moveVec)
	{
		tmp.clear();
		for (const auto& v : base)
			tmp.emplace_back(move + v);
		s.emplace_back(std::move(tmp));
	}

	collision_detection::tree<my::tree_imple001<my::shape,hoge>> t{ 2,-100.f,100.f,-100.f,100.f };
	t.clear();
	collision_detection::hit_cnt::clear();
	for (const auto& shape : s)
		t.resist(shape);
	t.search();
	std::cout << "cnt:" << collision_detection::hit_cnt::get();
	*/

	return 0;
}