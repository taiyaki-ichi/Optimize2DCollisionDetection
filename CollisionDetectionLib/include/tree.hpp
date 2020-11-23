#pragma once
#include<memory>
#include"policy.hpp"

namespace collision_detection
{
	template<typename T, typename HitPolicy , typename CollitionDetectionPolicy , int MAX_TREE_LEVEL>
	class tree_impl;

	//木
	template<typename T
		//当たった時の処理
		, typename HitPolicy = hit_policy<T>
		//当たり判定
		, typename CollitionDetectionPolicy = collision_detection_policy<T>
		//最大レベル
		,int MAX_TREE_LEVEL = 5
	>
	class tree
	{
	public:
		tree();
		tree(unsigned int level, float left, float right, float bottom, float top);

		//Objectの木への登録
		//ここでrange_traitsを使用
		inline void resist(const T& o);

		//木を走査し当たり判定を行う
		//ここでcollision_detection_traits,hit_traitsを使用
		inline void search();

		//木のクリア
		inline void clear();

		//セッタ
		inline void set_range(float left, float right, float bottom, float top);
		inline void set_level(unsigned int level);

		//コピー禁止
		tree(tree&) = delete;
		tree& operator=(const tree&) = delete;
		//ムーブ可能
		tree(tree&&) = default;
		tree& operator=(tree&&) = default;

	private:
		//実装
		std::unique_ptr<tree_impl<T, HitPolicy, CollitionDetectionPolicy, MAX_TREE_LEVEL>> m_tree_impl;
	};
}

#include"src/tree_impl.hpp"

