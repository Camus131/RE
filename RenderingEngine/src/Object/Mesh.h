#pragma once

#include "Leaf.h"
#include "DrawingSet.h"


namespace OGE
{
	class Mesh :public Leaf
	{
	public:
		friend class NodeVisitor;

		//创建实例
		static SPtr(Mesh) Create()
		{
			return SPtr(Mesh)(new Mesh);
		}

		//获得/设置position数组
		Vec3Array& GetPosArray() { return position_array_; }
		Vec3Array GetPosArray() const { return position_array_; }
		void SetPosArray(const Vec3Array& array);

		//获得/设置normal数组
		Vec3Array& GetNormArray() { return normal_array_; }
		Vec3Array GetNormArray() const { return normal_array_; }
		void SetNormArray(const Vec3Array& array) { normal_array_ = array; }

		//获得/设置uv数组
		Vec2Array& GetUvArray() { return uv_array_; }
		Vec2Array GetUvArray() const { return uv_array_; }
		void SetUvArray(const Vec2Array& array) { uv_array_ = array; }

		//获得/设置tanget数组
		Vec3Array& GetTanArray() { return tangent_array_; }
		Vec3Array GetTanArray() const { return tangent_array_; }
		void SetTanArray(const Vec3Array& array) { tangent_array_ = array; }

		//获得/设置bitanget数组
		Vec3Array& GetBitanArray() { return bitangent_array_; }
		Vec3Array GetBitanArray() const { return bitangent_array_; }
		void SetBitanArray(const Vec3Array& array) { bitangent_array_ = array; }

		//获得/设置drawing set
		SPtr(DrawingSet) GetDrawingSet() { return drawing_set_; }
		void SetDrawingSet(SPtr(DrawingSet) drawing_set) { drawing_set_ = drawing_set; }

	protected:
		Mesh() :
			Leaf()
		{
			name_ = OGE_Mesh;
		}

		virtual void UpdateBox();

	protected:
		Vec3Array			position_array_;

		Vec3Array			normal_array_;

		Vec2Array			uv_array_;

		Vec3Array			tangent_array_;

		Vec3Array			bitangent_array_;

		SPtr(DrawingSet)	drawing_set_;
	};
}