#pragma once

#pragma once

#include <cmath>
#include <cassert>

namespace nu
{
	struct Vector3
	{
		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
		};

		Vector3() = default;
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector3(float v) : x{ v }, y{ v }, z{ v } {}

		float  operator [] (unsigned int i) const { assert(i < 2); return (&x)[i]; }
		float& operator [] (unsigned int i) { assert(i < 2); return (&x)[i]; }

		bool operator == (const Vector3& v) const { return (this->x == v.x && this->y == v.y && this->z == v.z); }
		bool operator != (const Vector3& v) const { return (this->x != v.x || this->y != v.y || this ->z != v.z); }

		Vector3 operator + (const Vector3& v) const { return Vector3{ this->x + v.x, this->y + v.y, this->z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ this->x - v.x, this->y - v.y, this->z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ this->x * v.x, this->y * v.y, this->z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ this->x / v.x, this->y / v.y, this->z / v.z }; }

		Vector3 operator + (float v) const { return Vector3{ this->x + v, this->y + v, this->z + v }; }
		Vector3 operator - (float v) const { return Vector3{ this->x - v, this->y - v, this->z - v }; }
		Vector3 operator * (float v) const { return Vector3{ this->x * v, this->y * v, this->z * v }; }
		Vector3 operator / (float v) const { return Vector3{ this->x / v, this->y / v, this->z / v }; }

		Vector3& operator += (const Vector3& v) { this->x += v.x, this->y += v.y, this->z += v.z; return *this; } //Cannot be a const function if you're modifying what its grabbing
		Vector3& operator -= (const Vector3& v) { this->x -= v.x, this->y -= v.y, this->z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { this->x *= v.x, this->y *= v.y, this->z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { this->x /= v.x, this->y /= v.y, this->z /= v.z; return *this; }

		Vector3& operator += (float v) { this->x += v, this->y += v, this->z += v; return *this; } //Cannot be a const function if you're modifying what its grabbing
		Vector3& operator -= (float v) { this->x -= v, this->y -= v, this->z -= v; return *this; }
		Vector3& operator *= (float v) { this->x *= v, this->y *= v, this->z *= v; return *this; }
		Vector3& operator /= (float v) { this->x /= v, this->y /= v, this->z /= v; return *this; }

		float LengthSqr() const { return (x * x) + (y * y) + (z * z); }
		float Length() const { return std::sqrt(LengthSqr()); }
		Vector3 Normalized() const { return (*this) / Length(); }
		float Dot(const Vector3& v) const { return (this->x * v.x) + (this->y * v.y); }
		float Angle() const { return std::atan2(this->y, this->x); }
		float AngleBetween(const Vector3& v) const { return std::acos(Dot(v)); }
		Vector3 Rotate(float radians) {
			Vector3 v;

			v.x = this->x * std::cos(radians) - this->y * std::sin(radians);
			v.y = this->x * std::sin(radians) + this->y * std::cos(radians);

			return v;

		}
		//Troll game where you make the operators do the wrong thing?
	};

	using Color = Vector3;
}
