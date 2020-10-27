#pragma once

#include "RenderingUnit.h"
#include "StateVisitor.h"

#include "Object/Transform.h"
#include "Object/Mesh.h"
#include "Object/Cube.h"


namespace OGE
{
	class NodeVisitor :public Visitor
	{
	public:
		typedef std::map<SPtr(ShaderSource), std::map<SPtr(Texture2DSource), std::map<SPtr(Texture2DSource),
			std::map<SPtr(Texture2DSource), std::map<SPtr(VAO), std::vector<SPtr(RenderingUnit)>>>>>> StateTree;

		//����ʵ��
		static SPtr(NodeVisitor) Create(const std::vector<SPtr(Light)>& lights)
		{
			return SPtr(NodeVisitor)(new NodeVisitor(lights));
		}

		virtual void Visit(SPtr(Interviewee) object);

		//���״̬��
		StateTree GetTree() const { return tree_; }
		std::vector<SPtr(RenderingUnit)> GetTransparentTree() const { return transparent_tree_; }

	protected:
		NodeVisitor(const std::vector<SPtr(Light)>& lights);

		void Process(SPtr(Mesh) mesh);
		void Process(SPtr(Cube) cube);
		void Process(SPtr(Group) group);
		void Process(SPtr(Transform) transform);

	protected:
		SPtr(PhongState)							state_;

		std::vector<SPtr(Light)>					lights_;

		//��͸��״̬��
		StateTree									tree_;

		//͸��״̬��
		std::vector<SPtr(RenderingUnit)>			transparent_tree_;

		//��¼map
		std::map<SPtr(Leaf), SPtr(RenderingUnit)>	units_;

		SPtr(StateVisitor)							state_visitor_;
	};
}