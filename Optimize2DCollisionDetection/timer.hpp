#pragma once
#include<chrono>

namespace my
{

	//時間計測用クラス
	class timer
	{
		std::chrono::system_clock::time_point m_start;

	public:
		constexpr timer()
			:m_start{ std::chrono::system_clock::time_point::min() }
		{}


		//タイマーのクリア
		inline void clear() {
			using namespace std::chrono;

			m_start = system_clock::time_point::min();
		}

		//タイマーが稼働中かどうか
		inline bool is_started() const {
			using namespace std::chrono;

			return m_start.time_since_epoch() != system_clock::duration(0);
		}

		//タイマーの開始
		inline void do_test() {
			using namespace std::chrono;
			m_start = system_clock::now();
		}

		//タイマーが開始してからのミリ秒
		inline unsigned long get_ms() {
			using namespace std::chrono;

			if (is_started())
				return (unsigned)(duration_cast<milliseconds>(system_clock::now() - m_start).count());
			else
				return 0;
		}
	};
}