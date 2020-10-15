#include<iostream>
#include"timer.hpp"
#include"vec2_traits.hpp"

struct hoge { float x, y; };

int main()
{
	hoge huga{ 1.f,2.f };
	std::cout << my::vec2_traits<hoge>::get_x(huga) << std::endl;
	std::cout << my::vec2_traits<hoge>::get_y(huga) << std::endl;

	return 0;
}