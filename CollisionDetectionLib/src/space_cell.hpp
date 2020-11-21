#pragma once
#include<vector>

namespace collision_detection
{
	template<typename T>
	class space_cell
	{
		//‚±‚Ì‹óŠÔ‚ÉŠ‘®‚µ‚Ä‚¢‚éObject‚Ìƒ|ƒCƒ“ƒ^
		std::vector<const T*> m_object;

		//‚±‚Ì‹óŠÔ‚Ü‚½‚Í‚±‚Ì‹óŠÔ‚æ‚è‰ºˆÊ‚Ì‹óŠÔ‚ÉObject‚ª‚ ‚é‚©‚Ç‚¤‚©
		bool m_has_object_flag;

	public:
		space_cell()
			:m_object{}
			, m_has_object_flag{ false }
		{}

		void resist(const T& obj) {
			m_object.emplace_back(&obj);
		}

		void clear() {
			m_object.clear();
		}

		unsigned int size() const {
			return m_object.size();
		}

		const T* operator[](unsigned int num) const {
			return m_object[num];
		}

		void set_has_object_flag(bool b) {
			m_has_object_flag = b;
		}

		bool get_has_object_flag() const {
			return m_has_object_flag;
		}
	};
}