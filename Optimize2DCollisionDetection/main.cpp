#include<iostream>
#include<fstream>
#include"shape/shape.hpp"
#include"collision_detection/tree.hpp"
#include"tree_impl/001/tree_impl.hpp"
#include"collsion_detection_policy/001.hpp"
#include"tester.hpp"
#include"load_data.hpp"

int main()
{

	std::string file_name;
	std::cout << "test data file_name: ";
	std::cin >> file_name;

	unsigned int tree_level;
	std::cout << "tree_level: ";
	std::cin >> tree_level;

	auto [data, left, right, bottom, top] = my::load_data(file_name);

	my::tester<my::tree_imple001<my::shape, my::cd_001<my::shape>>> tester{ tree_level,left,right,bottom,top };
	tester.set_data(data);

	auto t = tester.do_test();
	std::cout << "\n";
	std::cout << "time: "<<t << "\n";
	std::cout << "cnt: " << collision_detection::hit_cnt::get() << "\n";

	/*

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
	
	*/

	return 0;
}