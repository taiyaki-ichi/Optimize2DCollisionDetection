#pragma once
#include<chrono>

namespace my
{

	//���Ԍv���p�N���X
	class timer
	{
		std::chrono::system_clock::time_point m_start;

	public:
		constexpr timer()
			:m_start{ std::chrono::system_clock::time_point::min() }
		{}


		//�^�C�}�[�̃N���A
		inline void clear() {
			using namespace std::chrono;

			m_start = system_clock::time_point::min();
		}

		//�^�C�}�[���ғ������ǂ���
		inline bool is_started() const {
			using namespace std::chrono;

			return m_start.time_since_epoch() != system_clock::duration(0);
		}

		//�^�C�}�[�̊J�n
		inline void do_test() {
			using namespace std::chrono;
			m_start = system_clock::now();
		}

		//�^�C�}�[���J�n���Ă���̃~���b
		inline unsigned long get_ms() {
			using namespace std::chrono;

			if (is_started())
				return (unsigned)(duration_cast<milliseconds>(system_clock::now() - m_start).count());
			else
				return 0;
		}
	};
}