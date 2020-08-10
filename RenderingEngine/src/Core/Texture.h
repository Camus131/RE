#pragma once

#include <vector>

#include "GLObject.h"


namespace OGE
{
	class Texture :public GLObject
	{
    public:
        //环绕轴方向
        enum WrapDir 
        {
            WRAP_S = GL_TEXTURE_WRAP_S,
            WRAP_T = GL_TEXTURE_WRAP_T,
            WRAP_R = GL_TEXTURE_WRAP_R,
        };

        //环绕模式
        enum WrapMode 
        {
            //重复纹理
            REPEAT = GL_REPEAT,
            //重复纹理是镜像放置的
            MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
            //纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果
            CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
            //超出的坐标为用户指定的边缘颜色
            CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
        };

        //过滤时机
        enum FilterChance
        {
            MIN_FILTER = GL_TEXTURE_MIN_FILTER,
            MAG_FILTER = GL_TEXTURE_MAG_FILTER,
        };

        //过滤模式
        enum FilterMode 
        {
            //邻近过滤
            NEAREST = GL_NEAREST,
            //使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
            NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
            //在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
            NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
            //线性过滤
            LINEAR = GL_LINEAR,
            //在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样
            LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
            //使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
            LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
        };

        //纹理单元
        enum Unit
        {
            TEXTURE0 = GL_TEXTURE0,
        };

        //数据格式
        enum Format
        {
            DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
            DEPTH_STENCIL = GL_DEPTH_STENCIL,
            RED = GL_RED,
            RG = GL_RG,
            RGB = GL_RGB,
            RGBA = GL_RGBA,
        };

        //数据类型
        enum Type
        {
            BYTE = GL_BYTE,
            UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
            SHORT = GL_SHORT,
            UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
            INT = GL_INT,
            UNSIGNED_INT = GL_UNSIGNED_INT,
            FLOAT = GL_FLOAT,
        };

        //unit为绑定的纹理单元
        virtual void Bind(int unit) const = 0;

        //获得环绕模式
        WrapMode GetWrapMode(WrapDir dir) const
        {
            switch (dir)
            {
            case WrapDir::WRAP_S:
                return parameter_list_.s_wrap_;
                break;
            case WrapDir::WRAP_T:
                return parameter_list_.t_wrap_;
                break;
            case WrapDir::WRAP_R:
                return parameter_list_.r_wrap_;
                break;
            }
        }

        //设置环绕模式
        void SetWrapMode(WrapDir dir, WrapMode mode)
        {
            switch (dir)
            {
            case WrapDir::WRAP_S:
                update_parameter_list_.s_wrap_ = mode;
                break;
            case WrapDir::WRAP_T:
                update_parameter_list_.t_wrap_ = mode;
                break;
            case WrapDir::WRAP_R:
                update_parameter_list_.r_wrap_ = mode;
                break;
            }
        }

        //获得过滤模式
        FilterMode GetFilterMode(FilterChance chance) const 
        {
            return chance == FilterChance::MIN_FILTER ? parameter_list_.min_filter_ : parameter_list_.mag_filter_;
        }

        //设置过滤模式
        void SetFilterMode(FilterChance chance,FilterMode mode) 
        { 
            if (chance == FilterChance::MIN_FILTER)
                update_parameter_list_.min_filter_ = mode;
            else
                update_parameter_list_.mag_filter_ = mode;
        }

        //获得多级渐远纹理启用状态
        bool GetMipMapEnable() const { return parameter_list_.is_enable_mipmap_; }

        //设置多级渐远纹理启用状态
        void SetMipMapEnable(bool enable) { update_parameter_list_.is_enable_mipmap_ = enable; }

        //获得多级渐远等级
        int GetMipMapLevel() const { return parameter_list_.level_; }

        //设置多级渐远等级
        void SetMipMapLevel(int level) { update_parameter_list_.level_ = level; }

        //获得GPU数据格式
        Format GetInternalFormat() const { return parameter_list_.internal_format_; }

        //设置GPU数据格式
        void SetInternalFormat(Format format) { update_parameter_list_.internal_format_ = format; }

        //获得CPU数据格式
        Format GetFormat() const { return parameter_list_.format_; }

        //设置CPU数据格式
        void SetFormat(Format format) { update_parameter_list_.format_ = format; }

        //获得CPU数据类型
        Type GetType() const { return parameter_list_.type_; }

        //设置CPU数据类型
        void SetType(Type type) { update_parameter_list_.type_ = type; }

        //获得宽
        int GetWidth() const { return parameter_list_.width_; }

        //设置宽
        void SetWidth(int width) { update_parameter_list_.width_ = width; }

        //获得高
        int GetHeight() const { return parameter_list_.height_; }

        //设置高
        void SetHeight(int height) { update_parameter_list_.height_ = height; }

    protected:
        Texture() :
            GLObject()
        {
            parameter_list_.s_wrap_ = update_parameter_list_.s_wrap_ = WrapMode::REPEAT;
            parameter_list_.t_wrap_ = update_parameter_list_.t_wrap_ = WrapMode::REPEAT;
            parameter_list_.r_wrap_ = update_parameter_list_.r_wrap_ = WrapMode::REPEAT;
            parameter_list_.min_filter_ = update_parameter_list_.min_filter_ = FilterMode::NEAREST;
            parameter_list_.mag_filter_ = update_parameter_list_.mag_filter_ = FilterMode::NEAREST;
            parameter_list_.is_enable_mipmap_ = update_parameter_list_.is_enable_mipmap_ = false;
            parameter_list_.level_ = update_parameter_list_.level_ = 0;
            parameter_list_.internal_format_ = update_parameter_list_.internal_format_ = Format::RGB;
            parameter_list_.format_ = update_parameter_list_.format_ = Format::RGB;
            parameter_list_.type_ = update_parameter_list_.type_ = Type::UNSIGNED_BYTE;
            parameter_list_.width_ = update_parameter_list_.width_ = 0;
            parameter_list_.height_ = update_parameter_list_.height_ = 0;
        }

    protected:
        //纹理参数列表
        struct TextureParameterList
        {
            //s轴环绕模式
            WrapMode                    s_wrap_;

            //t轴环绕模式
            WrapMode                    t_wrap_;

            //r轴环绕模式
            WrapMode                    r_wrap_;

            //缩小时的过滤模式
            FilterMode                  min_filter_;

            //放大时的过滤模式
            FilterMode                  mag_filter_;

            //是否启用多级渐远纹理
            bool                        is_enable_mipmap_;

            //多级渐远纹理等级
            int                         level_;

            //GPU数据格式
            Format                      internal_format_;

            //CPU数据格式
            Format			            format_;

            //CPU数据类型
            Type                        type_;

            //宽
            int				            width_;

            //高
            int				            height_;
        }; 

        //当前纹理参数
        TextureParameterList    parameter_list_;

        //待更新纹理参数
        TextureParameterList    update_parameter_list_;
	};
}