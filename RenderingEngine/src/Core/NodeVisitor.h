#pragma once

#include "RenderingUnit.h"

#include "Object/Transform.h"
#include "Object/Mesh.h"
#include "Object/Cube.h"
#include "Object/Light.h"


namespace OGE
{
	class NodeVisitor :public Visitor
	{
	public:
		typedef std::map<SPtr(ShaderSource), std::map<SPtr(Texture2DSource), std::map<SPtr(Texture2DSource),
			std::map<SPtr(Texture2DSource), std::map<SPtr(VAO), std::vector<SPtr(RenderingUnit)>>>>>> StateTree;

		//创建实例
		static SPtr(NodeVisitor) Create(const std::vector<SPtr(Light)>& lights)
		{
			return SPtr(NodeVisitor)(new NodeVisitor(lights));
		}

		virtual void Visit(SPtr(Interviewee) object);

		//获得状态树
		StateTree GetTree() const { return tree_; }
		StateTree GetTransparentTree() const { return transparent_tree_; }

	protected:
		NodeVisitor(const std::vector<SPtr(Light)>& lights);

		void Process(SPtr(Mesh) mesh);
		void Process(SPtr(Cube) cube);
		void Process(SPtr(Group) group);
		void Process(SPtr(Transform) transform);

	protected:
		SPtr(PhongState)				state_;

		std::vector<SPtr(Light)>		lights_;

		//不透明状态树
		StateTree						tree_;

		//透明状态树
		StateTree						transparent_tree_;

		//临时变量
		std::map<std::vector<std::string>, SPtr(ShaderSource)>		shaders_;
		std::map<SPtr(Texture2D), SPtr(Texture2DSource)>			emission_maps_;
		std::map<SPtr(Texture2D), SPtr(Texture2DSource)>			diffuse_maps_;
		std::map<SPtr(Texture2D), SPtr(Texture2DSource)>			specular_maps_;
		std::map<SPtr(Leaf), SPtr(RenderingUnit)>					units_;
	};
}