#pragma once
#include"traits.hpp"
#include"src/default_collision_detection_policy.hpp"

namespace collision_detection
{

	//特殊化しなければデフォルトの当たり判定を使用
	template<typename T>
	struct collision_detection_policy
	{
		inline static bool collision_detection(const T& a, const T& b) {
			
			//頂点が内包しているかのみ調べる
			return default_collision_detection_policy<T>::collision_detection(a, b);
		}
	};


	//あったった時の処理
	//特殊化しなければ何もしない
	template<typename T>
	struct hit_policy
	{
		//2つが衝突していた場合呼び出される
		inline static void hit(const T&, const T&) {}
	};

}