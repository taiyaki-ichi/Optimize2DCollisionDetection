#pragma once
#include"liner_object.hpp"

namespace my
{
	template<typename T>
	class space_cell
	{
		liner_object<T>* m_first_liner_object;

	public:

		//–Ø‚Ì\‘¢‚Ì‚±‚ÌSpaceCell‚âq‚â‘·‚ÉLinerObject‚ğ‚Â‚©‚Ç‚¤‚©
		bool m_has_liner_object;

		space_cell()
			:m_first_liner_object(nullptr)
			, m_has_liner_object(false)
		{}
		~space_cell() = default;

		void push(liner_object<T>* obj) {
			obj->m_space_cell = this;

			if (!m_first_liner_object)
				m_first_liner_object = obj;
			else
			{
				obj->m_next_liner_object = m_first_liner_object;
				m_first_liner_object->m_pre_liner_object = obj;
				m_first_liner_object = obj;
			}
		}

		liner_object<T>* get_first_liner_object() const noexcept {
			return m_first_liner_object;
		}

		void remove_list(liner_object<T>* obj) {
			if (m_first_liner_object == obj) {
				m_first_liner_object = obj->m_next_liner_object;
				if (m_first_liner_object)
					m_first_liner_object->m_pre_liner_object = nullptr;
			}
			else {
				if (obj->m_pre_liner_object)
					obj->m_pre_liner_object->m_next_liner_object = obj->m_next_liner_object;

				if (obj->m_next_liner_object)
					obj->m_next_liner_object->m_pre_liner_object = obj->m_pre_liner_object;
			}
		}
	};
}