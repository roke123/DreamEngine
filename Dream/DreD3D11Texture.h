#ifndef __DRED3D11TEXTURE_H__
#define __DRED3D11TEXTURE_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreTexture.h"

namespace dream
{

	class D3D11Texture final : public Texture
	{
		friend class D3D11RenderSystem;
		friend class D3D11RenderWindow;
		friend class D3D11RenderTarget;
	private:
		D3D11Texture(ID3D11Texture2DPtr texture, ID3D11ShaderResourceViewPtr shaderResource,
			ID3D11DevicePtr d3dDevice, u32 sizeInByte,
			DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f);

	public:
		~D3D11Texture();

		/** 把纹理导出成独立的Image
		*/
		ImagePtr ExportAsImage() override;

		/** 锁定缓冲区的实现方法
		* @param offset 锁定缓冲区的开始端偏移
		* @param length 锁定缓冲区长度
		* @param options 锁定缓冲区方式
		*/
		void * LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS options) override;

		/** 解锁通过lockImpl锁定的缓冲区
		*/
		void UnlockImpl(void) override;

		/** 获取D3D11渲染资源
		*/
		ID3D11ShaderResourceViewPtr GetShaderResource() { return mShaderResource; };

		/** 获取D3D11中对应Texture的实例
		*/
		ID3D11Texture2DPtr GetTexture() { return mTexture; };

	private:
		/** 把2D纹理数据复制到影子缓冲区
		* @remark	因为D3D11_USAGE_DEFAULT与D3D11_USAGE_DYNAM
		*			IC的缓冲区有部分读写操作不能直接完成，必须通
		*			过一个间接的影子缓冲区完成
		*/
		void CopyToShadowResource();

	private:
		/// D3D11的2D纹理
		ID3D11Texture2DPtr mTexture;
		/// D3D11的纹理渲染资源
		ID3D11ShaderResourceViewPtr mShaderResource;
		/// D3D11的2D纹理的影子缓冲
		ID3D11Texture2DPtr mShadowTexture;
		/// D3D11渲染设备
		ID3D11DevicePtr mD3D11Device;
		/// D3D11渲染设备内容
		ID3D11DeviceContextPtr mD3D11Context;
		/// 映射到CPU数据
		D3D11_MAPPED_SUBRESOURCE mSubResource;
		// 当前锁定选项
		DRE_LOCK_OPTIONS mLockOption;

	};	// end class D3D11Texture

}	// end namespace dream

#endif	// end __DRED3D11TEXTURE_H__