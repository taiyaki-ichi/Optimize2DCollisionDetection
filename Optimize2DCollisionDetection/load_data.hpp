#pragma once
#include<string>
#include<fstream>
#include<tuple>
#include"shape/shape.hpp"

namespace my
{


	std::tuple<std::vector<shape>,float,float,float,float> load_data(const std::string& file_name)
	{
		std::vector<shape> result{};

		std::ifstream f{ "../data/" + file_name + ".txt" };

		if (!f)
			return { result,0.f,0.f,0.f,0.f };

		int shape_num;
		f >> shape_num;
		result.reserve(shape_num);

		float left, right, bottom, top;
		f >> left >> right >> bottom >> top;

		int vert_num;
		float tmp_x, tmp_y;
		my::shape tmp_shape{};

		int i, j;
		for (i = 0; i < shape_num; i++)
		{
			tmp_shape.clear();

			f >> vert_num;
			for (j = 0; j < vert_num; j++)
			{
				f >> tmp_x;
				f >> tmp_y;
				tmp_shape.emplace_back(my::vec2f{ tmp_x,tmp_y });
			}

			result.emplace_back(std::move(tmp_shape));
		}

		return { result,left,right,bottom,top };
	}
}