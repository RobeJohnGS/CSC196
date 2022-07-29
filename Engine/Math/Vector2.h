#pragma once
//#include "../Math/Color.h"
#include <cmath>
#include <sstream>
#include <string>


namespace JREngine
{
	struct Vector2
	{
		float x, y;

		//Constructors
		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(float v) : x{ v }, y{ v } {}
		Vector2(int x, int y) : x{ (float)x }, y{ (float)y } {}

		//Functions
		void Set(float x, float y) { this->x = x, this->y = y; }
		Vector2 Add(const Vector2& v) { return Vector2{ v.x + x, v.y + y }; }

		float LengthSqr();
		float Length();
		float DstanceSqr(const Vector2& v);
		float Distance(const Vector2& v);

		Vector2 Normalized();
		void Normalize();

		float GetAngle();

		static Vector2 Rotate(const Vector2& v, float angle);

		//Arithmetic Operators
		//Vector2 = Vector2 + Vector2
		Vector2 operator + (const Vector2& v) const { return Vector2{ this->x + v.x, this->y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ this->x - v.x, this->y - v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ this->x / v.x, this->y / v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ this->x * v.x, this->y * v.y }; }

		//Vector2 = Vector2 + float
		Vector2 operator += (const Vector2& v) { this->x += v.x, this->y += v.y; return *this; }
		Vector2 operator -= (const Vector2& v) { this->x -= v.x, this->y -= v.y; return *this; }
		Vector2 operator /= (const Vector2& v) { this->x /= v.x, this->y /= v.y; return *this; }
		Vector2 operator *= (const Vector2& v) { this->x *= v.x, this->y *= v.y; return *this; }

		//Assignment Operators
		Vector2 operator + (float s) const { return Vector2{ this->x + s, this->y + s }; }
		Vector2 operator - (float s) const { return Vector2{ this->x - s, this->y - s }; }
		Vector2 operator / (float s) const { return Vector2{ this->x / s, this->y / s }; }
		Vector2 operator * (float s) const { return Vector2{ this->x * s, this->y * s }; }

		Vector2 operator += (float s) { return Vector2{ this->x += s, this->y += s }; }
		Vector2 operator -= (float s) { return Vector2{ this->x -= s, this->y -= s }; }
		Vector2 operator /= (float s) { return Vector2{ this->x /= s, this->y /= s }; }
		Vector2 operator *= (float s) { return Vector2{ this->x *= s, this->y *= s }; }

		//Unary
		//Vector2 = -Vector2
		Vector2 operator - () { return Vector2{ -x, -y }; }

		//Comparison
		//Vector2 == Vector2
		bool operator == (const Vector2& v) const { return (this->x == v.x && this->y == v.y); }
		bool operator != (const Vector2& v) const { return (this->x != v.x || this->y != v.y); }
	};

	inline std::istream& operator >> (std::istream& stream, Vector2& v)
	{
		std::string line;
		std::getline(stream, line);

		std::string xstring = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") - 1));
		v.x = std::stof(xstring);

		std::string ystring = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ystring);

		return stream;
	}

	inline float Vector2::LengthSqr() { 
		return (x * x) + (y * y); 
	}

	inline float Vector2::Length() { 
		return std::sqrt((x * x) + (y * y)); 
	}

	inline float Vector2::DstanceSqr(const Vector2& v)
	{
		return ((*this) - v).LengthSqr();
	}

	inline float Vector2::Distance(const Vector2& v)
	{
		return ((*this) - v).Length();
	}

	inline Vector2 Vector2::Normalized()
	{
		float length = Length();

		return Vector2{ x / length, y / length };
	}

	inline void Vector2::Normalize()
	{
		(*this) /= Length();
	}

	inline Vector2 Vector2::Rotate(const Vector2& v, float angle)
	{
		float x = v.x * std::cos(angle) - v.y * std::sin(angle);
		float y = v.x * std::sin(angle) + v.y * std::cos(angle);

		return Vector2{ x, y };
	}

	inline float Vector2::GetAngle()
	{
		return std::atan2(y, x);
	}
}