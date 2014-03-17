#ifndef __ITEXTURE_H__
#define __ITEXTURE_H__

#include "DreComplieConfig.h"
#include "Path.h"
#include "SColor.h"

namespace dream
{

	namespace video
	{

		enum ETEXTURETYPE
		{
			ETT_SHADERRESOURCE = 0,
			ETT_DEPTHSTENCIL = 1,
			ETT_RENDERTARGET = 2,

			//��ֹ��������enum����Ϊ��32λֵ
			ETT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
		};

		class IVideoDevice;

		class ITexture
		{
		public:
		//���캯��
			ITexture( IVideoDevice * Device, const io::CPath path, ETEXTURETYPE type, 
				u32 width, u32 height, ECOLORFMT fmt, bool isMipmap );
			
		//����������
			virtual ~ITexture() = 0;

		//���������Texture
			//param: readOnly - �Ƿ�ֻ���ı��,Ĭ��Ϊ��д
			//param: mipmapLevel - ��ʾȡ����һ��mipmapLevel��������ͼ
			virtual void * Lock( bool readOnly = false, u32 mipmapLevel = 0 ) = 0;

			virtual bool Unlock() = 0;

		//��ȡ������Ϣ
			virtual bool HasMipmap() const = 0;

			//ȡ��������ͼ���
			//param: mipmapLevel - ��ʾ��һ��mipmapLevel��������ͼ
			virtual u32 GetWidth( u32 mipmapLevel = 0 ) const = 0;

			//ȡ��������ͼ�߶�
			//param: mipmapLevel - ��ʾ��һ��mipmapLevel��������ͼ
			virtual u32 GetHeight( u32 mipmapLevel = 0 ) const = 0;

			virtual u32 GetColorFormat() const = 0;

			virtual u32 GetTextureType() const = 0;

			virtual bool HasAlpha() const {
				return GetColorFormat () == ECF_A8R8G8B8 || GetColorFormat () == ECF_A1R5G5B5;
			}

			// ����mipmap����
			// param: mipmapData - Ϊ0ʱ������Ӳ�����ɣ�Ϊ1ʱ�������������
			virtual void RegenerateMipMapLevels( void * mipmapData = 0 ) = 0;

			//ȡ��������ռ���
			virtual u32 GetPitch() const = 0;

		};

		typedef std::tr1::shared_ptr< ITexture > ITexturePtr;

	}	// end namespace video

}	// end namespace dream

#endif	// end __ITEXTURE_H__