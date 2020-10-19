#include<iostream>
#include<fstream>
#include"shape/shape.hpp"
#include"collision_detection/tree.hpp"
#include"tree_impl/001/tree_impl.hpp"
#include"collsion_detection_policy/001.hpp"
#include"tester.hpp"
#include"load_data.hpp"
#include"window/window.hpp"

int main()
{

	/*
	std::string file_name;
	std::cout << "test data file_name: ";
	std::cin >> file_name;

	unsigned int tree_level;
	std::cout << "tree_level: ";
	std::cin >> tree_level;

	auto [data, left, right, bottom, top] = my::load_data(file_name);

	my::tester<my::tree_imple001<my::shape, my::cd_001<my::shape>>> tester{ tree_level,left,right,bottom,top };
	tester.set_data(data);

	auto [t,cnt] = tester.do_test();
	std::cout << "\n";

	for (size_t i = 0; i < cnt.size(); i++)
		std::cout << "cnt " << i << ": " << cnt[i] << "\n";
	std::cout << "\n";

	std::cout << "time: "<<t << "\n";
	*/

	auto hwnd = my::create_simple_window(L"aaa", 500.f, 500.f);
	auto [hdc, hglrc] = my::init_opengl(hwnd);

	wglMakeCurrent(hdc, hglrc);

	glClearColor(0.2, 0.2, 0.2, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(-0.9, -0.9);
	glVertex2d(0.9, -0.9);
	glVertex2d(0.9, 0.9);
	glVertex2d(-0.9, 0.9);
	glEnd();

	SwapBuffers(hdc);
	wglMakeCurrent(NULL, NULL);

	while (my::process_window_message());

	my::shutdown(hwnd, hdc, hglrc);

	return 0;
}