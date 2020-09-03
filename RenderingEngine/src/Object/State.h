#pragma once

#include "Program.h"
#include "Material.h"
#include "Light.h"
#include "Uniform.h"


namespace OGE
{
	class State :public ExternalObject
	{
	protected:
		State() :
			ExternalObject() {}
	};


	class PhongState :public State
	{
	public:
		//创建实例
		static SPtr(PhongState) Create()
		{
			return SPtr(PhongState)(new PhongState);
		}

		SPtr(PhongState) Copy() const;

		//获得/设置材质
		SPtr(Material) GetMaterial() { return material_; }
		void SetMaterial(SPtr(Material) material) { material_ = material; }

		//获得/设置光源
		SPtr(Light) GetLight() { return light_; }
		void SetLight(SPtr(Light) light) { light_ = light; }

	protected:
		PhongState();

	protected:
		SPtr(Material)		material_;

		SPtr(Light)			light_;
	};


	class CustomState :public State
	{
	public:
		//创建实例
		static SPtr(CustomState) Create()
		{
			return SPtr(CustomState)(new CustomState);
		}

		SPtr(CustomState) Copy() const;

		//获得/设置着色程序
		SPtr(Program) GetProgram() { return program_; }
		void SetProgram(SPtr(Program) program) { program_ = program; }

		//添加/删除/获得uniform变量
		void AddUniform(SPtr(Uniform) uniform);
		void RemoveUniform(SPtr(Uniform) uniform);
		void RemoveUniform(const std::string& name);
		SPtr(Uniform) GetUniform(const std::string& name) const;

	protected:
		CustomState();

	protected:
		SPtr(Program)		program_;

		typedef std::vector<SPtr(Uniform)> UniformList;
		UniformList			uniform_list_;
	};
}