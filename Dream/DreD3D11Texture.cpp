#include "DreD3D11Texture.h"

#include "DreD3D11RenderMapping.h"
#include "DreNormalImage.h"

namespace dream
{

	D3D11Texture::D3D11Texture(
		ID3D11Texture2DPtr texture, ID3D11ShaderResourceViewPtr shaderResource,
		ID3D11DevicePtr d3dDevice, u32 sizeInByte,
		DRE_BUFFER_USAGE usage, bool isTransparentFigure /* = false */,
		u32 fsaa /* = 1 */, u32 fsaaQuality /* = 0 */, f32 gamma /* = 1.0f */) :
	Texture(sizeInByte, usage, isTransparentFigure, fsaa, fsaaQuality, gamma),
		mTexture(texture), mShaderResource(shaderResource),
		mD3D11Device(d3dDevice)
	{
		mD3D11Device->GetImmediateContext(mD3D11Context.GetReference());

		D3D11_TEXTURE2D_DESC textureDesc = {0};
		mTexture->GetDesc(&textureDesc);

		SetFinalAtrributes(textureDesc.Width, textureDesc.Height, D3D11RenderMapping::Get(textureDesc.Format));
	}

	D3D11Texture::~D3D11Texture()
	{
		// 留空
	}

	/** 把纹理导出成独立的Image
	*/
	ImagePtr D3D11Texture::ExportAsImage()
	{
		u32 imageSize = this->GetSizeInBytes();
		u8Array imageData(imageSize);

		this->ReadData(0, imageSize / 8, &imageData[0]);

		D3D11_TEXTURE2D_DESC desc = {0};
		mTexture->GetDesc(&desc);

		DRE_PIXEL_FORMAT imageFormat = D3D11RenderMapping::Get(desc.Format);
		if(imageFormat == DRE_PIXEL_FORMAT_UNKNOWN)
		{
			// 事实上Texture均由image生成，理论上不会出现不能转换的情况
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "不能转换该texture到image中",
				"D3D11Texture::ExportAsImage");
		}
		
		return ImagePtr(new NormalImage(imageData, desc.Width, desc.Height,
			imageFormat));
	}

	/** 锁定缓冲区的实现方法
	* @param offset 锁定缓冲区的开始端偏移
	* @param length 锁定缓冲区长度
	* @param options 锁定缓冲区方式
	*/
	void* D3D11Texture::LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS option)
	{
		if( option == DRE_LOCK_DISCARD || option == DRE_LOCK_NO_OVERWRITE)
		{
			mLockOption = DRE_LOCK_WRITE_ONLY;
		}
		else
		{
			mLockOption = option;
		}
		
		// map选项
		D3D11_MAP mapOption = D3D11RenderMapping::Get(mLockOption);
		HRESULT hr = 0;

		if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC)
		{	
			hr = mD3D11Context->Map(mTexture.Get(), 0, mapOption, 0, &mSubResource);
		}

		else if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC_WRITE_ONLY)
		{
			switch (option)
			{
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式不支持读出数据",
					"D3D11Texture::LockImpl");
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				hr = mD3D11Context->Map(mTexture.Get(), 0, mapOption, 0, &mSubResource);
				break;
			}
		}

		else if (this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC ||
			this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY ||
			this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE )
		{
			//
			switch (mLockOption)
			// D3D11_USAGE_DYNAMIC时，mVertexBuffer不能读
			{
			// D3D11_USAGE_DYNAMIC时，mVertexBuffer不能读
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				if(this->GetUsage() != DRE_BUFFER_USAGE_DYNAMIC)
				{
					// 复制数据到影子数组
					CopyToShadowResource();
					hr = mD3D11Context->Map(mShadowTexture.Get(), 0, mapOption, 0, &mSubResource);
					break;
				}
				else
				{
					DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式不支持读出数据",
						"D3D11Texture::LockImpl");
				}
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_WRITE_ONLY:
				hr = mD3D11Context->Map(mTexture.Get(), 0, mapOption, 0, &mSubResource);
				break;
			}
		}

		else //if (this->GetUsage() == DRE_BUFFER_USAGE_DEFAULT)
		{
			switch (mLockOption)
			{
			// D3D11_USAGE_DEFAULT时，mVertexBuffer不能读也不能写
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
			case dream::DRE_LOCK_WRITE_ONLY:
				// 复制数据到影子数组
				CopyToShadowResource();
				hr = mD3D11Context->Map(mShadowTexture.Get(), 0, mapOption, 0, &mSubResource);
				break;
			}
		}

		D3D11_IF_FAILED_THROW(hr, "D3D11Texture::LockImpl");

		return mSubResource.pData;
	}

	/** 解锁通过lockImpl锁定的缓冲区
	*/
	void D3D11Texture::UnlockImpl(void)
	{
		HRESULT hr = 0;

		if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC ||
			this->GetUsage() == DRE_BUFFER_USAGE_STATIC_WRITE_ONLY)
		{	
			mD3D11Context->Unmap(mTexture.Get(), 0);
		}
		else if (this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC ||
			this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY ||
			this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE )
		{
			switch (mLockOption)
			{
			// D3D11_USAGE_DYNAMIC时，mTexture不能读
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				mD3D11Context->Unmap(mShadowTexture.Get(), 0);
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				mD3D11Context->Unmap(mTexture.Get(), 0);
				break;
			}
		}
		else //if (this->GetUsage() == DRE_BUFFER_USAGE_DEFAULT)
		{
			switch (mLockOption)
			{
			// D3D11_USAGE_DEFAULT时，直接unmap VertexShadowBuffer
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				mD3D11Context->Unmap(mShadowTexture.Get(), 0);
			case dream::DRE_LOCK_WRITE_ONLY:
				// 复制影子数组数据
				mD3D11Context->CopyResource(mTexture.Get(), mShadowTexture.Get());
				mD3D11Context->Unmap(mShadowTexture.Get(), 0);
				break;
			}
		}

		D3D11_IF_FAILED_THROW(hr, "D3D11Texture::UnlockImpl");
	}

	void D3D11Texture::CopyToShadowResource()
	{
		D3D11_TEXTURE2D_DESC desc = {0};
		mTexture->GetDesc(&desc);

		// 修改缓冲区描述
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

		// 创建影子缓冲
		HRESULT hr = mD3D11Device->CreateTexture2D(&desc, nullptr, mShadowTexture.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11Texture::CopyToShadowResource");

		// 复制数据
		mD3D11Context->CopyResource(mShadowTexture.Get(), mTexture.Get());
	}

}	// end namespace dream