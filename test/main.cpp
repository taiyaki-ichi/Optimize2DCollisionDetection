#include"include/tree.hpp"
#include"shape.hpp"
#include"load_data.hpp"
#include<iostream>


namespace my
{
	static int cnt = 0;
	struct hit_p {
		static void hit(const shape&, const shape&) {
			cnt++;
		}
	};
}

int main()
{

	std::string file_name;
	std::cout << "test data file_name: ";
	std::cin >> file_name;

	unsigned int tree_level;
	std::cout << "tree_level: ";
	std::cin >> tree_level;

	auto [data, left, right, bottom, top] = my::load_data(file_name);

	collision_detection::tree<my::shape, my::hit_p> t{};// t{ tree_level,left,right,bottom,top };
	t.set_level(tree_level);
	t.set_range(left, right, bottom, top);

	t.clear();

	for (auto& tmp : data)
		t.resist(tmp);

	t.search();

	std::cout <<"\ncnt: "<< my::cnt << "\n";


	return 0;
}