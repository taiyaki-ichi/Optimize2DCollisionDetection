#pragma once
#include<vector>

namespace my
{
	template<typename Object>
	class space_cell002
	{
		std::vector<const Object*> m_object;

	public:
		//この空間またはこの空間より下位の空間にObjectがあるかどうか
		bool m_has_object_flag;

		space_cell002()
			:m_object{}
			, m_has_object_flag{false}
		{}

		void resist(const Object& obj)
		{
			m_object.emplace_back(&obj);
		}

		void clear()
		{
			m_object.clear();
		}

		auto begin() {
			return m_object.begin();
		}

		auto end() {
			return m_object.end();
		}

	};
}