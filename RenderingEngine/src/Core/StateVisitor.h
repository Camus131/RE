#pragma once

#include "ShaderSource.h"
#include "Texture2DSource.h"

#include "Object/State.h"
#include "Object/Light.h"


namespace OGE
{
	class StateVisitor :public Visitor
	{
	public:
		friend class NodeVisitor;

		//创建实例
		static SPtr(StateVisitor) Create(const std::vector<SPtr(Light)>& lights)
		{
			return SPtr(StateVisitor)(new StateVisitor(lights));
		}

		virtual void Visit(SPtr(Interviewee) object);

	protected:
		StateVisitor(const std::vector<SPtr(Light)>& lights) :
			Visitor(),
			lights_(lights),
			alpha_(1.0f)
		{
			name_ = OGE_StateVisitor;
		}

		void Process(SPtr(PhongState) state);
		void Process(SPtr(CustomState) state);

	protected:
		std::vector<SPtr(Light)>	lights_;

		float						alpha_;

		SPtr(UniformList)			materials_;

		SPtr(ShaderSource)			shader_;

		SPtr(Texture2DSource)		emission_map_;

		SPtr(Texture2DSource)		diffuse_map_;

		SPtr(Texture2DSource)		specular_map_;

		//临时变量
		std::map<std::vector<std::string>, SPtr(ShaderSource)>		shaders_;
		std::map<SPtr(Texture2D), SPtr(Texture2DSource)>			emission_maps_;
		std::map<SPtr(Texture2D), SPtr(Texture2DSource)>			diffuse_maps_;
		std::map<SPtr(Texture2D), SPtr(Texture2DSource)>			specular_maps_;
	};
}