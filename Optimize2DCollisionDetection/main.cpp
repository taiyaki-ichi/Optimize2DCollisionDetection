#include<iostream>
#include"shape/shape.hpp"
#include"collision_detection/tree.hpp"
#include"tree_impl/001/tree_impl.hpp"



int main()
{
	collision_detection::tree<my::tree_imple001<my::vec2f>> t{ 1,-1.f,1.f,-1.f,1.f };
	t.clear();
	t.search();

	return 0;
}