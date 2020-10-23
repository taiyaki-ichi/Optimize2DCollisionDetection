#pragma once
#include<vector>

namespace my
{
	template<typename Object>
	class space_cell003
	{
		std::vector<const Object*> m_object;

	public:
		//���̋�Ԃ܂��͂��̋�Ԃ�艺�ʂ̋�Ԃ�Object�����邩�ǂ���
		bool m_has_object_flag;

		space_cell003()
			:m_object{}
			, m_has_object_flag{ false }
		{}

		void resist(const Object& obj){
			m_object.emplace_back(&obj);
		}

		void clear(){
			m_object.clear();
		}

		unsigned int size() const {
			return m_object.size();
		}

		const Object* operator[](unsigned int num) const {
			return m_object[num];
		}

	};
}