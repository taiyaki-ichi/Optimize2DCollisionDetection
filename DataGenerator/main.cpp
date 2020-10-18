#include<random>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace my
{
	namespace
	{
		constexpr float PI = 3.1415;

		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());

		std::uniform_real_distribution<> dist(-1.0, 1.0);

		//�P�ʉ~����̐����p�`�̎擾
		inline std::vector<std::pair<float, float>> get_normalized_shape(int vertNum)
		{
			std::vector<std::pair<float, float>> result{};
			result.reserve(vertNum);

			for (int i = 0; i < vertNum; i++)
			{
				result.emplace_back(std::make_pair(std::cos(2.f * PI * i / static_cast<float>(vertNum)), std::sin(2.f * PI * i / static_cast<float>(vertNum))));
			}

			return result;
		}

		//���_�𒆐S�ɉ�]
		inline std::pair<float, float> rotation(std::pair<float, float>&& p, float rot)
		{
			float tmp_x = p.first;
			p.first = std::cos(rot) * p.first - std::sin(rot) * p.second;
			p.second = std::sin(rot) * tmp_x + std::cos(rot) * p.second;
			return p;
		}

		//���_����̋�����s�{�ɂ���
		inline std::pair<float, float> scale(std::pair<float, float>&& p, float s)
		{
			p.first *= s;
			p.second *= s;
			return p;
		}

		//x,y�����s�ړ�
		inline std::pair<float, float> translation(std::pair<float, float>&& p, float x, float y)
		{
			p.first += x;
			p.second += y;
			return p;
		}

		//pair���͈͓��ɂ��邩�ǂ���
		inline bool is_in_range(const std::pair<float, float>& p, float left, float right, float bottom, float top)
		{
			if (left <= p.first && p.first < right && bottom <= p.second && p.second < top)
				return true;
			else
				return false;
		}
	}
}

int main()
{

	int n;
	std::cout << "shape num: ";
	std::cin >> n;

	float left, right, bottom, top;
	std::cout << "range _left _right _bottom _top: ";
	std::cin >> left >> right >> bottom >> top;

	int min_vert_num, max_vert_num;
	std::cout << "min_vert_num max_vert_num: ";
	std::cin >> min_vert_num >> max_vert_num;


	std::string file_name;
	std::cout << "file_name: ";
	std::cin >> file_name;

	//x,y�̃����_��
	std::uniform_real_distribution<> dist_x(left, right);
	std::uniform_real_distribution<> dist_y(bottom, top);

	//scale�̃����_��
	std::uniform_real_distribution<> dist_scale(5.f, 20.f);

	//rot�̃����_��
	std::uniform_real_distribution<> dist_rot(0.f, my::PI * 2.0);

	//���_���̌�
	std::uniform_int_distribution<> dist_vert(min_vert_num, max_vert_num);

	std::ofstream file{ "../data/" + file_name + ".txt" };

	int j,v,i;
	float scale, trans_x, trans_y, rot;
	bool is_valid;

	i = 0;

	file << n << "\n";
	while (i < n)
	{
		//���_�̐�
		v = dist_vert(my::engine);
		auto shape = my::get_normalized_shape(v);

		trans_x = static_cast<float>(dist_x(my::engine));
		trans_y = static_cast<float>(dist_y(my::engine));

		scale = static_cast<float>(dist_scale(my::engine));

		rot = static_cast<float>(dist_rot(my::engine));

		is_valid = true;
		for (j = 0; j < v; j++)
		{
			shape[j] = my::translation(my::scale(my::rotation(std::move(shape[j]), rot), scale), trans_x, trans_y);

			//�����Ȉʒu�������ꍇ
			if (!my::is_in_range(shape[j], left, right, bottom, top)) {
				is_valid = false;
				break;
			}
		}

		if (is_valid)
		{
			//���_�̐�
			file << v << " ";
			//���ꂼ��̍��W
			for (j = 0; j < v; j++)
			{
				file << shape[j].first << " " << shape[j].second << " ";
			}
			file << "\n";

			i++;
		}
	}


	return 0;
}