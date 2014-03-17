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

			//防止编译器把enum编译为非32位值
			ETT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
		};

		class IVideoDevice;

		class ITexture
		{
		public:
		//构造函数
			ITexture( IVideoDevice * Device, const io::CPath path, ETEXTURETYPE type, 
				u32 width, u32 height, ECOLORFMT fmt, bool isMipmap );
			
		//虚析构函数
			virtual ~ITexture() = 0;

		//锁定与解锁Texture
			//param: readOnly - 是否只读的标记,默认为读写
			//param: mipmapLevel - 表示取出哪一个mipmapLevel的纹理贴图
			virtual void * Lock( bool readOnly = false, u32 mipmapLevel = 0 ) = 0;

			virtual bool Unlock() = 0;

		//获取纹理信息
			virtual bool HasMipmap() const = 0;

			//取出纹理贴图宽度
			//param: mipmapLevel - 表示哪一个mipmapLevel的纹理贴图
			virtual u32 GetWidth( u32 mipmapLevel = 0 ) const = 0;

			//取出纹理贴图高度
			//param: mipmapLevel - 表示哪一个mipmapLevel的纹理贴图
			virtual u32 GetHeight( u32 mipmapLevel = 0 ) const = 0;

			virtual u32 GetColorFormat() const = 0;

			virtual u32 GetTextureType() const = 0;

			virtual bool HasAlpha() const {
				return GetColorFormat () == ECF_A8R8G8B8 || GetColorFormat () == ECF_A1R5G5B5;
			}

			// 生成mipmap纹理
			// param: mipmapData - 为0时，启用硬件生成，为1时，启用软件生成
			virtual void RegenerateMipMapLevels( void * mipmapData = 0 ) = 0;

			//取得像素所占跨度
			virtual u32 GetPitch() const = 0;

		};

		typedef std::tr1::shared_ptr< ITexture > ITexturePtr;

	}	// end namespace video

}	// end namespace dream

#endif	// end __ITEXTURE_H__