#include<iostream>
#include"collision_detection/morton_number.hpp"
#include<Windows.h>



int main()
{
	std::cout << collision_detection::get_morton_number(0.1, 0.2, 0.1, 0.2, -1.f, -1.f, 0.5f, 0.5f, 2) << "\n";
	std::cout << collision_detection::get_morton_number(-0.9, 0.9, -0.9, 0.9, -1.f, -1.f, 0.5f, 0.5f, 2) << "\n";
	std::cout << collision_detection::get_morton_number(0.1, 0.9, -0.9, -0.1, -1.f, -1.f, 0.5f, 0.5f, 2) << "\n";
	//std::cout << sizeof(unsigned short) << " " << sizeof(unsigned long) << "\n";
	//std::cout << sizeof(WORD) << " " << sizeof(DWORD) << "\n";

	return 0;
}