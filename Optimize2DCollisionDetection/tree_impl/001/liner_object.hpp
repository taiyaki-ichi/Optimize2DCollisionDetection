#pragma once
#include<vector>

namespace my
{
	template<typename T>
	class SpaceCell;

	template<typename T>
	class LinerObject
	{
		T* mPtr;

	public:
		LinerObject<T>* mPreLinerObject;
		LinerObject<T>* mNextLinerObject;
		//Š‘®‚·‚é‹óŠÔ
		SpaceCell<T>* mSpaceCell;

		LinerObject(T* ptr=nullptr)
			:mPtr{ptr}
			, mPreLinerObject{nullptr}
			, mNextLinerObject{nullptr}
			, mSpaceCell{nullptr}
		{}
		~LinerObject() = default;

		T* GetPtr() const noexcept {
			return mPtr;
		}

		void ClearPtr() noexcept {
			mPtr = nullptr;
		}

		void SetPtr(T* ptr) noexcept {
			mPtr = ptr;
		}

		void RemoveSpaceCell() {
			if (mSpaceCell)
				mSpaceCell->RemoveList(this);
			mPreLinerObject = nullptr;
			mNextLinerObject = nullptr;
		}
	};

	//LinerObject‚ÌŠÇ—
	//O(1)‚Å‘}“ü
	template<typename T>
	class LinerObjectContainer
	{
		std::vector<LinerObject<T>> m_contanier;

		rsize_t m_size;

	public:
		LinerObjectContainer(unsigned int size)
			:m_contanier(size)
			, m_size{ 0 }
		{}

		const LinerObject<T>& GetLinerObject(const T& obj)
		{
			if (m_contanier.size() < m_size)
				m_contanier[m_size].SetPtr(&obj);
			else
				m_contanier.emplace_back({ &obj });

			m_size++;
			return m_contanier[m_size - 1];
		}

		void Clear()
		{
			for (rsize_t i = 0; i < m_size; i++) {
				m_contanier[i].RemoveSpaceCell();
				m_contanier[i].mPreLinerObject = nullptr;
				m_contanier[i].mNextLinerObject = nullptr;
				m_contanier[i].ClearPtr();
			}
			m_size = 0;
		}
	};
}