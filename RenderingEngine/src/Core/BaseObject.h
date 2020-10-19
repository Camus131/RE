#pragma once

#include "glad/glad.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>


namespace OGE
{
#define SPtr(T)				std::shared_ptr<T>
#define SPtrCast(T,V)		std::static_pointer_cast<T>(V)	

	enum  ObjectName
	{
		OGE_None,
		OGE_DrawingCall,
		OGE_IndexBuffer,
		OGE_NodeVisitor,
		OGE_Renderer,
		OGE_RenderingUnit,
		OGE_ShaderSource,
		OGE_Texture2DSource,
		OGE_UniformList,
		OGE_VertexArray,
		OGE_VertexBuffer,
		OGE_IndexBufferUByte,
		OGE_IndexBufferUShort,
		OGE_IndexBufferUInt,
		OGE_DrawArrays,
		OGE_DrawElementsUByte,
		OGE_DrawElementsUShort,
		OGE_DrawElementsUInt,
		OGE_Image,
		OGE_DirLight,
		OGE_PointLight,
		OGE_Material,
		OGE_Mesh,
		OGE_Program,
		OGE_Shader,
		OGE_PhongState,
		OGE_CustomState,
		OGE_Texture2D,
		OGE_UniformInt,
		OGE_UniformFloat,
		OGE_UniformVec2,
		OGE_UniformVec3,
		OGE_UniformVec4,
		OGE_UniformMat,
		OGE_Group,
		OGE_Transform,
		OGE_Cube,
		OGE_Viewport,
		OGE_PerspectiveCamera,
	};

	class BaseObject :public std::enable_shared_from_this<BaseObject>
	{
	public:
		//获得标记名字
		ObjectName GetName() const { return name_; }

	protected:
		//防止外部创建对象
		BaseObject() :
			name_(OGE_None) {}

		SPtr(BaseObject) Self() const { return std::const_pointer_cast<BaseObject>(shared_from_this()); }

	protected:
		//标记名字
		ObjectName		name_;
	};
}