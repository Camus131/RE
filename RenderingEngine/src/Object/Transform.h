#pragma once

#include "Group.h"


namespace OGE
{
	class Transform :public Group
	{
	public:
		friend class NodeVisitor;

		//创建实例
		static SPtr(Transform) Create(const Matrix& matrix)
		{
			return SPtr(Transform)(new Transform(matrix));
		}

		//获得/设置变换矩阵
		Matrix GetMatrix() const { return matrix_; }
		void SetMatrix(const Matrix& matrix) { matrix_ = matrix; }

	protected:
		Transform(const Matrix& matrix) :
			Group(),
			matrix_(matrix)
		{
			name_ = OGE_Transform;
		}

		virtual void UpdateBox();

	protected:
		Matrix			matrix_;
	};
}