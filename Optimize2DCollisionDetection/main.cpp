#include<iostream>
#include"timer.hpp"
#include"vec2_traits.hpp"
#include"vec2.hpp"

int main()
{

	constexpr my::vec2f a{ 1.f,2.f };
	constexpr my::vec2f b{ 4.f,5.f };

	constexpr float c = my::vec2f::dot(a, b);

	static_assert(my::vec2f::dot(a, b));

	return 0;
}