////This works as a substitution for pragmaonce
//#ifndef __MATH_UTILS_H__
//#define __MATH_UTILS_H__
//
//namespace Math {
//	int sqr(int v);
//}
//#endif //__MATH_UTILS_H__

#pragma once
namespace Math {
	const float pi = 3.14159265359f;
	const float twoPi = 6.28318530718f;
	const float halfPi = 1.57079632679f;

	inline float DegToRad(float degrees) {
		return degrees * (pi / 180);
	}

	inline float RadToDeg(float radians) {
		return radians * (180 / pi);
	}

	int sqr(int v);
	//Inline doesnt really call the funtion, it replaces the word for blocks of code.
	inline int half(int v) { return v / 2; }
}