#pragma once
#include<cmath>

namespace my
{
	//flaot‚Ì2ŽŸŒ³ƒxƒNƒgƒ‹
	struct vec2f
	{
		float x;
		float y;

		constexpr vec2f()
			:x{}
			, y{}
		{}

		constexpr vec2f(float inX, float inY)
			: x{ inX }
			, y{ inY }
		{}

		constexpr vec2f operator+(const vec2f& rhs) const noexcept {
			return { x + rhs.x,y + rhs.y };
		}

		constexpr vec2f operator+=(const vec2f& rhs) noexcept {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		constexpr vec2f operator-(const vec2f& rhs) const noexcept {
			return { x - rhs.x,y - rhs.y };
		}

		constexpr vec2f& operator-=(const vec2f& rhs) noexcept {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		constexpr vec2f operator*(float rhs) const noexcept {
			return { x * rhs,y * rhs };
		}

		constexpr vec2f& operator*=(float rhs) noexcept {
			x *= rhs;
			y *= rhs;
			return *this;
		}

		constexpr vec2f operator/(float rhs) const noexcept {
			return { x / rhs,y / rhs };
		}

		constexpr vec2f& operator/=(float rhs) noexcept {
			x /= rhs;
			y /= rhs;
			return *this;
		}

		constexpr float length_sq() const noexcept {
			return x * x + y * y;
		}

		float length() const noexcept {
			return std::sqrtf(length_sq());
		}

		constexpr vec2f normalize() const noexcept {
			return (*this) / length();
		}

		constexpr void normalize_self() noexcept {
			(*this) /= length();
		}

		static constexpr float dot(const vec2f& a, const vec2f& b) {
			return a.x * b.x + a.y * b.y;
		}

		static constexpr float cross(const vec2f& a, const vec2f& b) {
			return a.x * b.y - a.y * b.x;
		}
	};

}