#include<iostream>
#include"timer.hpp"
#include"vec2_traits.hpp"
#include"vec2.hpp"
#include"range_traits.hpp"
#include<vector>

int main()
{

	constexpr my::vec2f v1{ 1.f,2.f };
	constexpr my::vec2f v2{ 4.f,1.f };
	constexpr my::vec2f v3{ 5.f,3.f };
	constexpr my::vec2f v4{ 2.f,4.f };

	std::vector shape{ v1,v2,v3,v4 };

	auto [l, r, b, t] = my::range_traits<std::vector<my::vec2f>>::get_range(shape);

	std::cout << l << " " << r << " " << b << " " << t << std::endl;

	return 0;
}