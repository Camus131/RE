#pragma once

#include <vector>

#include "GLObject.h"


namespace OGE
{
	class Texture :public GLObject
	{
    public:
        //�����᷽��
        enum WrapDir 
        {
            WRAP_S = GL_TEXTURE_WRAP_S,
            WRAP_T = GL_TEXTURE_WRAP_T,
            WRAP_R = GL_TEXTURE_WRAP_R,
        };

        //����ģʽ
        enum WrapMode 
        {
            //�ظ�����
            REPEAT = GL_REPEAT,
            //�ظ������Ǿ�����õ�
            MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
            //��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч��
            CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
            //����������Ϊ�û�ָ���ı�Ե��ɫ
            CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
        };

        //����ʱ��
        enum FilterChance
        {
            MIN_FILTER = GL_TEXTURE_MIN_FILTER,
            MAG_FILTER = GL_TEXTURE_MAG_FILTER,
        };

        //����ģʽ
        enum FilterMode 
        {
            //�ڽ�����
            NEAREST = GL_NEAREST,
            //ʹ�����ڽ��Ķ༶��Զ������ƥ�����ش�С����ʹ���ڽ���ֵ�����������
            NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
            //��������ƥ�����ش�С�Ķ༶��Զ����֮��������Բ�ֵ��ʹ���ڽ���ֵ���в���
            NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
            //���Թ���
            LINEAR = GL_LINEAR,
            //�������ڽ��Ķ༶��Զ����֮��ʹ�����Բ�ֵ����ʹ�����Բ�ֵ���в���
            LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
            //ʹ�����ڽ��Ķ༶��Զ�����𣬲�ʹ�����Բ�ֵ���в���
            LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
        };

        //����Ԫ
        enum Unit
        {
            TEXTURE0 = GL_TEXTURE0,
        };

        //���ݸ�ʽ
        enum Format
        {
            DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
            DEPTH_STENCIL = GL_DEPTH_STENCIL,
            RED = GL_RED,
            RG = GL_RG,
            RGB = GL_RGB,
            RGBA = GL_RGBA,
        };

        //��������
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

        //unitΪ�󶨵�����Ԫ
        virtual void Bind(int unit) const = 0;

        //��û���ģʽ
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

        //���û���ģʽ
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

        //��ù���ģʽ
        FilterMode GetFilterMode(FilterChance chance) const 
        {
            return chance == FilterChance::MIN_FILTER ? parameter_list_.min_filter_ : parameter_list_.mag_filter_;
        }

        //���ù���ģʽ
        void SetFilterMode(FilterChance chance,FilterMode mode) 
        { 
            if (chance == FilterChance::MIN_FILTER)
                update_parameter_list_.min_filter_ = mode;
            else
                update_parameter_list_.mag_filter_ = mode;
        }

        //��ö༶��Զ��������״̬
        bool GetMipMapEnable() const { return parameter_list_.is_enable_mipmap_; }

        //���ö༶��Զ��������״̬
        void SetMipMapEnable(bool enable) { update_parameter_list_.is_enable_mipmap_ = enable; }

        //��ö༶��Զ�ȼ�
        int GetMipMapLevel() const { return parameter_list_.level_; }

        //���ö༶��Զ�ȼ�
        void SetMipMapLevel(int level) { update_parameter_list_.level_ = level; }

        //���GPU���ݸ�ʽ
        Format GetInternalFormat() const { return parameter_list_.internal_format_; }

        //����GPU���ݸ�ʽ
        void SetInternalFormat(Format format) { update_parameter_list_.internal_format_ = format; }

        //���CPU���ݸ�ʽ
        Format GetFormat() const { return parameter_list_.format_; }

        //����CPU���ݸ�ʽ
        void SetFormat(Format format) { update_parameter_list_.format_ = format; }

        //���CPU��������
        Type GetType() const { return parameter_list_.type_; }

        //����CPU��������
        void SetType(Type type) { update_parameter_list_.type_ = type; }

        //��ÿ�
        int GetWidth() const { return parameter_list_.width_; }

        //���ÿ�
        void SetWidth(int width) { update_parameter_list_.width_ = width; }

        //��ø�
        int GetHeight() const { return parameter_list_.height_; }

        //���ø�
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
        //��������б�
        struct TextureParameterList
        {
            //s�ỷ��ģʽ
            WrapMode                    s_wrap_;

            //t�ỷ��ģʽ
            WrapMode                    t_wrap_;

            //r�ỷ��ģʽ
            WrapMode                    r_wrap_;

            //��Сʱ�Ĺ���ģʽ
            FilterMode                  min_filter_;

            //�Ŵ�ʱ�Ĺ���ģʽ
            FilterMode                  mag_filter_;

            //�Ƿ����ö༶��Զ����
            bool                        is_enable_mipmap_;

            //�༶��Զ����ȼ�
            int                         level_;

            //GPU���ݸ�ʽ
            Format                      internal_format_;

            //CPU���ݸ�ʽ
            Format			            format_;

            //CPU��������
            Type                        type_;

            //��
            int				            width_;

            //��
            int				            height_;
        }; 

        //��ǰ�������
        TextureParameterList    parameter_list_;

        //�������������
        TextureParameterList    update_parameter_list_;
	};
}