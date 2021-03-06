#pragma once
#include"../shape/shape.hpp"
#include<Windows.h>
#include<glew.h>
#include<set>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "winmm.lib")


namespace my
{
	template<typename CollisionDetectionPolicy>
	void draw(HDC hdc,float width, float height, const std::vector<shape>& shape, float left, float right, float bottom, float top)
	{
		//描写のついでに当たった回数を数え出力
		//secondよりfirstの方が小さな添え字
		std::set<std::pair<unsigned int, unsigned int>> cnt{};

		glClearColor(1.0, 1.0, 1.0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (size_t i = 0; i < shape.size(); i++)
		{
			size_t j;
			unsigned int left_index, right_index;
			bool is_hit = false;
			for (j = 0; j < shape.size(); j++)
				if (i != j)
					//当たっていた場合
					if (CollisionDetectionPolicy::collision_detection(shape[i], shape[j])) {
						left_index = (i < j) ? i : j;
						right_index = (i < j) ? j : i;

						//挿入
						cnt.insert({ left_index,right_index });

						is_hit = true;
					}
						

			//当たっている場合
			if (is_hit) 
				glColor3d(1.0, 0.0, 0.0);
			//当たってない場合
			else
				glColor3d(0.0, 0.0, 0.0);

			glLineWidth(3.f);

			float x, y;
			float x_length = right - left;
			float y_length = top - bottom;
			
			glBegin(GL_LINE_LOOP);
			for (const auto& v : shape[i])
			{
				x = (v.x - left) / x_length * 2.f - 1.f;
				y = (v.y - bottom) / y_length * 2.f - 1.f;
				glVertex2d(x, y);
			}
			glEnd();
			
		}

		SwapBuffers(hdc);
		wglMakeCurrent(NULL, NULL);

		std::cout << "hit cnt: " << cnt.size() << "\n";

	}
}