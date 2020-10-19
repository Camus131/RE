#pragma once

#include "Program.h"
#include "Material.h"
#include "Uniform.h"


namespace OGE
{
	class State :public Interviewee
	{
	protected:
		State() :
			Interviewee() {}
	};


	class PhongState :public State
	{
	public:
		//����ʵ��
		static SPtr(PhongState) Create()
		{
			return SPtr(PhongState)(new PhongState);
		}

		SPtr(PhongState) Copy() const;

		//���/���ò���
		SPtr(Material) GetMaterial() { return material_; }
		void SetMaterial(SPtr(Material) material) { material_ = material; }

		//���/����alpha
		float GetAlpha() { return alpha_; }
		void SetAlpha(float alpha) { alpha_ = alpha; }

	protected:
		PhongState() :
			State()
		{
			name_ = OGE_PhongState;
		}

	protected:
		SPtr(Material)		material_;

		float				alpha_;
	};


	class CustomState :public State
	{
	public:
		//����ʵ��
		static SPtr(CustomState) Create()
		{
			return SPtr(CustomState)(new CustomState);
		}

		SPtr(CustomState) Copy() const;

		//���/������ɫ����
		SPtr(Program) GetProgram() { return program_; }
		void SetProgram(SPtr(Program) program) { program_ = program; }

		//���/ɾ��/���uniform����
		void AddUniform(SPtr(Uniform) uniform);
		void RemoveUniform(SPtr(Uniform) uniform);
		void RemoveUniform(const std::string& name);
		SPtr(Uniform) GetUniform(const std::string& name) const;

	protected:
		CustomState() :
			State()
		{
			name_ = OGE_CustomState;
		}

	protected:
		SPtr(Program)		program_;

		typedef std::vector<SPtr(Uniform)> UniformList;
		UniformList			uniform_list_;
	};
}