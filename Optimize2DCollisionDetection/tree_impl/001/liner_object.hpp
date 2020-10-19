#pragma once
#include<vector>

namespace my
{
	template<typename T>
	class space_cell;

	template<typename T>
	class liner_object
	{
		const T* m_ptr;

	public:
		liner_object<T>* m_pre_liner_object;
		liner_object<T>* m_next_liner_object;
		//Š‘®‚·‚é‹óŠÔ
		space_cell<T>* m_space_cell;

		liner_object(const T* ptr=nullptr)
			:m_ptr{ptr}
			, m_pre_liner_object{nullptr}
			, m_next_liner_object{nullptr}
			, m_space_cell{nullptr}
		{}
		~liner_object() = default;

		const T* get_ptr() const noexcept {
			return m_ptr;
		}

		void clear_ptr() noexcept {
			m_ptr = nullptr;
		}

		void set_ptr(const T* ptr) noexcept {
			m_ptr = ptr;
		}

		void remove_space_cell() {
			if (m_space_cell)
				m_space_cell->remove_list(this);
			m_pre_liner_object = nullptr;
			m_next_liner_object = nullptr;
		}
	};

	//LinerObject‚ÌŠÇ—
	//O(1)‚Å‘}“ü
	template<typename T>
	class liner_object_container
	{
		std::vector<liner_object<T>*> m_contanier;

		rsize_t m_size;

	public:
		liner_object_container(unsigned int size)
			:m_contanier(size)
			, m_size{ 0 }
		{
			for (unsigned int i = 0; i < size; i++)
				m_contanier[i] = new liner_object<T>{};
		}

		~liner_object_container()
		{
			for (unsigned int i = 0; i < m_contanier.size(); i++)
				if (m_contanier[i])
					delete m_contanier[i];
		}

		liner_object<T>* get_liner_object(const T& obj)
		{
			if (m_contanier.size() > m_size)
				m_contanier[m_size]->set_ptr(&obj);
			else 
				m_contanier.emplace_back(new liner_object<T>{ &obj });

			m_size++;
			return m_contanier[m_size - 1];
		}

		void clear()
		{
			for (rsize_t i = 0; i < m_size; i++) {
				m_contanier[i]->remove_space_cell();
				m_contanier[i]->m_pre_liner_object = nullptr;
				m_contanier[i]->m_next_liner_object = nullptr;
				m_contanier[i]->clear_ptr();
			}
			m_size = 0;
		}
	};
}