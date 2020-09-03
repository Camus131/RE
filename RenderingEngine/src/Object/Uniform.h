#pragma once

#include "ExternalObject.h"
#include "../Math/Vec2f.h"
#include "../Math/Vec4f.h"
#include "../Math/Matrixf.h"


namespace OGE
{
	class Uniform :public ExternalObject
	{
	public:
		//获得/设置uniform名字
		std::string GetUniformName() const { return uniform_name_; }
		void SetUniformName(const std::string& uniform_name) { uniform_name_ = uniform_name; }

	protected:
		Uniform() :
			ExternalObject() {}

	protected:
		std::string		uniform_name_;
	};


	class UniformFloat :public Uniform
	{
	public:
		typedef float value_type;

		//创建实例
		static SPtr(UniformFloat) Create(const std::string& uniform_name, value_type value)
		{
			return SPtr(UniformFloat)(new UniformFloat(uniform_name, value));
		}

		SPtr(UniformFloat) Copy() const { return SPtr(UniformFloat)(new UniformFloat(uniform_name_, value_)); }

		//获得/设置uniform值
		value_type GetValue() const { return value_; }
		void SetValue(value_type value) { value_ = value; }

		bool operator == (const UniformFloat& uniform) const { return uniform_name_ == uniform.uniform_name_ && value_ == uniform.value_; }

	protected:
		UniformFloat(const std::string& uniform_name, value_type value);

	protected:
		value_type		value_;
	};


	class UniformInt :public Uniform
	{
	public:
		typedef int value_type;

		//创建实例
		static SPtr(UniformInt) Create(const std::string& uniform_name, value_type value)
		{
			return SPtr(UniformInt)(new UniformInt(uniform_name, value));
		}

		SPtr(UniformInt) Copy() const { return SPtr(UniformInt)(new UniformInt(uniform_name_, value_)); }

		//获得/设置uniform值
		value_type GetValue() const { return value_; }
		void SetValue(value_type value) { value_ = value; }

		bool operator == (const UniformInt& uniform) const { return uniform_name_ == uniform.uniform_name_ && value_ == uniform.value_; }

	protected:
		UniformInt(const std::string& uniform_name, value_type value);

	protected:
		value_type		value_;
	};


	class UniformVec2 :public Uniform
	{
	public:
		typedef Vec2 value_type;

		//创建实例
		static SPtr(UniformVec2) Create(const std::string& uniform_name, const value_type& value)
		{
			return SPtr(UniformVec2)(new UniformVec2(uniform_name, value));
		}

		SPtr(UniformVec2) Copy() const { return SPtr(UniformVec2)(new UniformVec2(uniform_name_, value_)); }

		//获得/设置uniform值
		value_type GetValue() const { return value_; }
		void SetValue(const value_type& value) { value_ = value; }

		bool operator == (const UniformVec2& uniform) const { return uniform_name_ == uniform.uniform_name_ && value_ == uniform.value_; }

	protected:
		UniformVec2(const std::string& uniform_name, const value_type& value);

	protected:
		value_type		value_;
	};


	class UniformVec3 :public Uniform
	{
	public:
		typedef Vec3 value_type;

		//创建实例
		static SPtr(UniformVec3) Create(const std::string& uniform_name, const value_type& value)
		{
			return SPtr(UniformVec3)(new UniformVec3(uniform_name, value));
		}

		SPtr(UniformVec3) Copy() const { return SPtr(UniformVec3)(new UniformVec3(uniform_name_, value_)); }

		//获得/设置uniform值
		value_type GetValue() const { return value_; }
		void SetValue(const value_type& value) { value_ = value; }

		bool operator == (const UniformVec3& uniform) const { return uniform_name_ == uniform.uniform_name_ && value_ == uniform.value_; }

	protected:
		UniformVec3(const std::string& uniform_name, const value_type& value);

	protected:
		value_type		value_;
	};


	class UniformVec4 :public Uniform
	{
	public:
		typedef Vec4 value_type;

		//创建实例
		static SPtr(UniformVec4) Create(const std::string& uniform_name, const value_type& value)
		{
			return SPtr(UniformVec4)(new UniformVec4(uniform_name, value));
		}

		SPtr(UniformVec4) Copy() const { return SPtr(UniformVec4)(new UniformVec4(uniform_name_, value_)); }

		//获得/设置uniform值
		value_type GetValue() const { return value_; }
		void SetValue(const value_type& value) { value_ = value; }

		bool operator == (const UniformVec4& uniform) const { return uniform_name_ == uniform.uniform_name_ && value_ == uniform.value_; }

	protected:
		UniformVec4(const std::string& uniform_name, const value_type& value);

	protected:
		value_type		value_;
	};


	class UniformMat :public Uniform
	{
	public:
		typedef Matrix value_type;

		//创建实例
		static SPtr(UniformMat) Create(const std::string& uniform_name, const value_type& value)
		{
			return SPtr(UniformMat)(new UniformMat(uniform_name, value));
		}

		SPtr(UniformMat) Copy() const { return SPtr(UniformMat)(new UniformMat(uniform_name_, value_)); }

		//获得/设置uniform值
		value_type GetValue() const { return value_; }
		void SetValue(const value_type& value) { value_ = value; }

		bool operator == (const UniformMat& uniform) const { return uniform_name_ == uniform.uniform_name_ && value_ == uniform.value_; }

	protected:
		UniformMat(const std::string& uniform_name, const value_type& value);

	protected:
		value_type		value_;
	};
}