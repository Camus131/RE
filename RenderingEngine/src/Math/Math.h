#pragma once

#include <cmath>


namespace OGE
{
	//定义三角值及函数
#ifdef PI
#undef PI
#undef PI_2
#undef PI_4
#endif
	const double PI = 3.14159265358979323846;
	const double PI_2 = 1.57079632679489661923;
	const double PI_4 = 0.78539816339744830962;
	const double LN_2 = 0.69314718055994530942;
	const double INVLN_2 = 1.0 / LN_2;

	const float PIf = 3.14159265358979323846f;
	const float PI_2f = 1.57079632679489661923f;
	const float PI_4f = 0.78539816339744830962f;
	const float LN_2f = 0.69314718055994530942f;
	const float INVLN_2f = 1.0f / LN_2f;

	inline double Angle(double rad) { return rad * 180.0 / PI; }
	inline double Rad(double angle) { return angle * PI / 180.0; }
	inline double Cos(double angle) { return cos(Rad(angle)); }
	inline double Sin(double angle) { return sin(Rad(angle)); }
	inline double Tan(double angle) { return tan(Rad(angle)); }
	inline double Cot(double angle) { return 1.0 / Tan(angle); }

	inline float Angle(float rad) { return rad * 180.0f / PIf; }
	inline float Rad(float angle) { return angle * PIf / 180.0f; }
	inline float Cos(float angle) { return cosf(Rad(angle)); }
	inline float Sin(float angle) { return sinf(Rad(angle)); }
	inline float Tan(float angle) { return tanf(Rad(angle)); }
	inline float Cot(float angle) { return 1.0f / Tan(angle); }

	//绝对值
	template<typename T>
	inline T Absolute(T v) { return v < (T)0 ? -v : v; }

	//浮点数开方
	inline float Sqrt(float v) { return sqrtf(v); }
	inline double Sqrt(double v) { return sqrt(v); }

	//返回true表示两浮点数相等
	inline bool IsEqual(float lhs, float rhs, float epsilon = 1e-6)
	{
		return Absolute(lhs - rhs) <= epsilon;
	}
	inline bool IsEqual(double lhs, double rhs, double epsilon = 1e-6)
	{
		return Absolute(lhs - rhs) <= epsilon;
	}

	//较小数
	template<typename T>
	inline T Minimum(T lhs, T rhs) { return lhs < rhs ? lhs : rhs; }

	//较大数
	template<typename T>
	inline T Maximum(T lhs, T rhs) { return lhs > rhs ? lhs : rhs; }

	//返回ture表示浮点数非法
	inline bool IsNaN(double v) { return std::isnan(v); }
	inline bool IsNaN(float v) { return std::isnan(v); }

	//交换两数的值
	template<typename T>
	inline void Swap(T& lhs, T& rhs) 
	{
		T temp = lhs;
		lhs = rhs;
		rhs = temp;
	}
}