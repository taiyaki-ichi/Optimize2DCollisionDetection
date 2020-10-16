#pragma once

namespace collision_detection
{
	//TreeImplはinit,resist,search,clearを実装
	//計測し比較するため実装部分は入れ替えられるようにテンプレートにした。
	//Objectはrange_traits,collision_detection_traits,hit_traitsを満たす
	template<typename TreeImpl,typename Object>
	class tree
	{
		TreeImpl m_tree_impl;

	public:
		//初期化
		inline bool init() {
			m_tree_impl.init();
		}

		//Objectの木への登録
		//ここでrange_traitsを使用
		inline void resist(const Object& o) {
			m_tree_impl.resist(o);
		}

		//木を走査し当たり判定を行う
		//ここでcollision_detection_traits,hit_traitsを使用
		inline void search() {
			m_tree_impl.search();
		}

		//木のクリア
		inline void clear() {
			m_tree_impl.clear();
		}
	};
}