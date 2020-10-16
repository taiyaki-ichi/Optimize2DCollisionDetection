#include<iostream>
#include"timer.hpp"
#include"vec2f.hpp"
#include<vector>
#include"shape/shape.hpp"
#include"shape/traits.hpp"


struct hoge
{
	static bool collision_detection(const my::shape& a, const my::shape& b)
	{
		std::cout << "hoge colliiiiiii!\n";
		return true;
	}
};

int main()
{
	constexpr my::vec2f v1{ 1.f,2.f };
	constexpr my::vec2f v2{ 4.f,1.f };
	constexpr my::vec2f v3{ 5.f,3.f };
	constexpr my::vec2f v4{ 2.f,4.f };

	my::shape s{ v1,v2,v3,v4 };

	auto [l, r, b, t] = collision_detection::range_traits<my::shape>::get_range(s);

	std::cout << l << " " << r << " " << b << " " << t << std::endl;

	collision_detection::collision_detection_traits<my::shape>::collision_detection<hoge>(s, s);

	collision_detection::hit_traits<my::shape>::hit(s, s);

	return 0;
}