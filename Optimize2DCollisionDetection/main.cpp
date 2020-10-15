#include<iostream>
#include"timer.hpp"

int main()
{
	my::timer t{};

	t.start();
	for (int i = 0; i < 100000; i++)
		std::string a{ "a" };

	std::cout << t.get_ms();

	return 0;
}