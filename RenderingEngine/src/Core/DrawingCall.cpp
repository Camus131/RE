#include "DrawingCall.h"

#include "Object/DrawArrays.h"
#include "Object/DrawElements.h"


namespace OGE
{
	void DrawingCall::Draw() const
	{
		switch (drawing_set_->GetName())
		{
		case OGE_DrawArrays:
		{
			SPtr(DrawArrays) draw_arrays = SPCast(DrawArrays, drawing_set_);
			DrawArrays::DrawSegments segments_map = draw_arrays->GetAllSegments();
			DrawArrays::Mode mode = draw_arrays->GetMode();
			int instanced_num = draw_arrays->GetInstancedNum();

			//筛选出启用的绘制段
			std::vector<int> first_array, count_array;
			for (auto iter = segments_map.begin(); iter != segments_map.end(); ++iter)
			{
				if (iter->second == true)
				{
					first_array.emplace_back(iter->first.First);
					count_array.emplace_back(iter->first.Count);
				}
			}

			//无启用的则返回
			int draw_count = first_array.size();
			if (!draw_count)
				return;

			if (segments_map.size() > 1)
			{
				if (draw_count > 1)
					glMultiDrawArrays(mode, &first_array[0], &count_array[0], draw_count);
				else
					glDrawArrays(mode, first_array[0], count_array[0]);
			}
			else
			{
				if (instanced_num > 1)
					glDrawArraysInstanced(mode, first_array[0], count_array[0], instanced_num);
				else
					glDrawArrays(mode, first_array[0], count_array[0]);
			}
		}break;
		case OGE_DrawElementsUByte:
		{
			SPtr(DrawElementsUByte) draw_elements = SPCast(DrawElementsUByte, drawing_set_);
			DrawElementsUByte::DrawSegments segments_map = draw_elements->GetAllSegments();
			DrawElementsUByte::Mode mode = draw_elements->GetMode();
			int instanced_num = draw_elements->GetInstancedNum();

			//筛选出启用的绘制段
			std::vector<void*> offset_array;
			std::vector<int> count_array, basevertex_array;

			for (auto iter = segments_map.begin(); iter != segments_map.end(); ++iter)
			{
				if (iter->second == true)
				{
					offset_array.emplace_back((void*)(iter->first.Offset * sizeof(unsigned char)));
					count_array.emplace_back(iter->first.Count);
					basevertex_array.emplace_back(iter->first.BaseVertex);
				}
			}

			//无启用的则返回
			int draw_count = count_array.size();
			if (!draw_count)
				return;

			//应用不同的绘制调用
			if (segments_map.size() > 1)
			{
				if (draw_count > 1)
					glMultiDrawElementsBaseVertex(mode, &count_array[0], GL_UNSIGNED_BYTE, &offset_array[0], draw_count, &basevertex_array[0]);
				else
					glDrawElementsBaseVertex(mode, count_array[0], GL_UNSIGNED_BYTE, offset_array[0], basevertex_array[0]);
			}
			else
			{
				if (instanced_num > 1)
					glDrawElementsInstancedBaseVertex(mode, count_array[0], GL_UNSIGNED_BYTE, offset_array[0], instanced_num, basevertex_array[0]);
				else
					glDrawElementsBaseVertex(mode, count_array[0], GL_UNSIGNED_BYTE, offset_array[0], basevertex_array[0]);
			}
		}break;
		case OGE_DrawElementsUShort:
		{
			SPtr(DrawElementsUShort) draw_elements = SPCast(DrawElementsUShort, drawing_set_);
			DrawElementsUShort::DrawSegments segments_map = draw_elements->GetAllSegments();
			DrawElementsUShort::Mode mode = draw_elements->GetMode();
			int instanced_num = draw_elements->GetInstancedNum();

			//筛选出启用的绘制段
			std::vector<void*> offset_array;
			std::vector<int> count_array, basevertex_array;

			for (auto iter = segments_map.begin(); iter != segments_map.end(); ++iter)
			{
				if (iter->second == true)
				{
					offset_array.emplace_back((void*)(iter->first.Offset * sizeof(unsigned short)));
					count_array.emplace_back(iter->first.Count);
					basevertex_array.emplace_back(iter->first.BaseVertex);
				}
			}

			//无启用的则返回
			int draw_count = count_array.size();
			if (!draw_count)
				return;

			//应用不同的绘制调用
			if (segments_map.size() > 1)
			{
				if (draw_count > 1)
					glMultiDrawElementsBaseVertex(mode, &count_array[0], GL_UNSIGNED_SHORT, &offset_array[0], draw_count, &basevertex_array[0]);
				else
					glDrawElementsBaseVertex(mode, count_array[0], GL_UNSIGNED_SHORT, offset_array[0], basevertex_array[0]);
			}
			else
			{
				if (instanced_num > 1)
					glDrawElementsInstancedBaseVertex(mode, count_array[0], GL_UNSIGNED_SHORT, offset_array[0], instanced_num, basevertex_array[0]);
				else
					glDrawElementsBaseVertex(mode, count_array[0], GL_UNSIGNED_SHORT, offset_array[0], basevertex_array[0]);
			}
		}break;
		case OGE_DrawElementsUInt:
		{
			SPtr(DrawElementsUInt) draw_elements = SPCast(DrawElementsUInt, drawing_set_);
			DrawElementsUInt::DrawSegments segments_map = draw_elements->GetAllSegments();
			DrawElementsUInt::Mode mode = draw_elements->GetMode();
			int instanced_num = draw_elements->GetInstancedNum();

			//筛选出启用的绘制段
			std::vector<void*> offset_array;
			std::vector<int> count_array, basevertex_array;

			for (auto iter = segments_map.begin(); iter != segments_map.end(); ++iter)
			{
				if (iter->second == true)
				{
					offset_array.emplace_back((void*)(iter->first.Offset * sizeof(unsigned int)));
					count_array.emplace_back(iter->first.Count);
					basevertex_array.emplace_back(iter->first.BaseVertex);
				}
			}

			//无启用的则返回
			int draw_count = count_array.size();
			if (!draw_count)
				return;

			//应用不同的绘制调用
			if (segments_map.size() > 1)
			{
				if (draw_count > 1)
					glMultiDrawElementsBaseVertex(mode, &count_array[0], GL_UNSIGNED_INT, &offset_array[0], draw_count, &basevertex_array[0]);
				else
					glDrawElementsBaseVertex(mode, count_array[0], GL_UNSIGNED_INT, offset_array[0], basevertex_array[0]);
			}
			else
			{
				if (instanced_num > 1)
					glDrawElementsInstancedBaseVertex(mode, count_array[0], GL_UNSIGNED_INT, offset_array[0], instanced_num, basevertex_array[0]);
				else
					glDrawElementsBaseVertex(mode, count_array[0], GL_UNSIGNED_INT, offset_array[0], basevertex_array[0]);
			}
		}break;
		}
	}
}