#pragma once

#include "State.h"
#include "DrawArrays.h"
#include "DrawElements.h"


namespace OGE
{
	class Mesh :public ExternalObject
	{
	public:
		//����ʵ��
		static SPtr(Mesh) Create()
		{
			return SPtr(Mesh)(new Mesh);
		}
		static SPtr(Mesh) CreateBox();

		//���/����position����
		Vec3Array& GetPosArray() { return position_array_; }
		Vec3Array GetPosArray() const { return position_array_; }
		void SetPosArray(const Vec3Array& array) { position_array_ = array; }
		int SizeOfPosArray() const { return position_array_.size() * sizeof(float) * 3; }

		//���/����normal����
		Vec3Array& GetNormArray() { return normal_array_; }
		Vec3Array GetNormArray() const { return normal_array_; }
		void SetNormArray(const Vec3Array& array) { normal_array_ = array; }
		int SizeOfNormArray() const { return normal_array_.size() * sizeof(float) * 3; }

		//���/����uv����
		Vec2Array& GetUvArray() { return uv_array_; }
		Vec2Array GetUvArray() const { return uv_array_; }
		void SetUvArray(const Vec2Array& array) { uv_array_ = array; }
		int SizeOfUvArray() const { return uv_array_.size() * sizeof(float) * 2; }

		//���/����tanget����
		Vec3Array& GetTanArray() { return tangent_array_; }
		Vec3Array GetTanArray() const { return tangent_array_; }
		void SetTanArray(const Vec3Array& array) { tangent_array_ = array; }
		int SizeOfTanArray() const { return tangent_array_.size() * sizeof(float) * 3; }

		//���/����bitanget����
		Vec3Array& GetBitanArray() { return bitangent_array_; }
		Vec3Array GetBitanArray() const { return bitangent_array_; }
		void SetBitanArray(const Vec3Array& array) { bitangent_array_ = array; }
		int SizeOfBitanArray() const { return bitangent_array_.size() * sizeof(float) * 3; }

		//���/���û�������
		SPtr(DrawingSet) GetDrawingSet() { return drawing_set_; }
		void SetDrawingSet(SPtr(DrawingSet) drawing_set) { drawing_set_ = drawing_set; }

		//���/����ģ�;���
		Matrix GetModelMatrix() const { return model_matrix_; }
		void SetModelMatrix(const Matrix& mat) { model_matrix_ = mat; }

		//���/������Ⱦ״̬
		SPtr(State) GetState() { return state_; }
		void SetState(SPtr(State) state) { state_ = state; }

	protected:
		Mesh();

	protected:
		Vec3Array			position_array_;

		Vec3Array			normal_array_;

		Vec2Array			uv_array_;

		Vec3Array			tangent_array_;

		Vec3Array			bitangent_array_;

		SPtr(DrawingSet)	drawing_set_;

		Matrix				model_matrix_;

		SPtr(State)			state_;
	};
}