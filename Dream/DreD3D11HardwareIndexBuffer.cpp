#include "DreD3D11HardwareIndexBuffer.h"

#include "DreD3D11RenderMapping.h"

namespace dream
{

	D3D11HardwareIndexBuffer::D3D11HardwareIndexBuffer(
		ID3D11BufferPtr indexBuffer, ID3D11DevicePtr d3d11Device,
		DRE_INDEX_ELEMENT_TYPE indexType, u32 numIndices,
		DRE_BUFFER_USAGE usage) throw() :

	HardwareIndexBuffer(indexType, numIndices, usage),
		mIndexBuffer(indexBuffer),
		mD3D11Device(d3d11Device)
	{
		mD3D11Device->GetImmediateContext(mD3D11Context.GetReference());
	}

	D3D11HardwareIndexBuffer::~D3D11HardwareIndexBuffer()
	{
		// 留空
	}

	/** 锁定缓冲区的实现方法
	* @param offset 锁定缓冲区的开始端偏移
	* @param length 锁定缓冲区长度
	* @param options 锁定缓冲区方式
	*/
	void* D3D11HardwareIndexBuffer::LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS option)
	{
		mLockOption = option;

		// map选项
		D3D11_MAP mapOption = D3D11RenderMapping::Get(option);
		HRESULT hr = 0;

		if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC)
		{
			hr = mD3D11Context->Map(mIndexBuffer.Get(), 0, mapOption, 0, &mSubResource);
		}

		else if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC_WRITE_ONLY)
		{
			switch (option)
			{
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式不支持读出数据",
					"D3D11HardwareIndexBuffer::LockImpl");
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				hr = mD3D11Context->Map(mIndexBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			}
		}

		else if (this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC ||
			this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY ||
			this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE )
		{
			//
			switch (option)
			{
			// D3D11_USAGE_DYNAMIC时，mVertexBuffer不能读
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				if(this->GetUsage() != DRE_BUFFER_USAGE_DYNAMIC)
				{
					// 复制数据到影子数组
					CopyToShadowResource();
					hr = mD3D11Context->Map(mIndexShadowBuffer.Get(), 0, mapOption, 0, &mSubResource);
				}
				else
				{
					DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式不支持读出数据",
						"D3D11HardwareIndexBuffer::LockImpl");
				}
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
				hr = mD3D11Context->Map(mIndexBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				if(this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE)
				{
					DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式仅支持DISCARD方式读出数据",
						"D3D11HardwareIndexBuffer::LockImpl");
				}
				hr = mD3D11Context->Map(mIndexBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			}
		}

		else // if (this->GetUsage() == DRE_BUFFER_USAGE_DEFAULT)
		{
			//
			switch (option)
			{
			// D3D11_USAGE_DEFAULT时，mIndexBuffer不能读也不能写
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
			case dream::DRE_LOCK_WRITE_ONLY:
				// 复制数据到影子数组
				CopyToShadowResource();
				hr = mD3D11Context->Map(mIndexShadowBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			// 直接取索引缓冲区
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_NO_OVERWRITE:
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式不支持DISCARD和NO OVERWRITE方式读出数据",
					"D3D11HardwareIndexBuffer::LockImpl");		
				break;
			}
		}

		D3D11_IF_FAILED_THROW(hr, "D3D11HardwareVertexBuffer::LockImpl");

		return mSubResource.pData;
	}

	void D3D11HardwareIndexBuffer::CopyToShadowResource()
	{
		D3D11_BUFFER_DESC desc = {0};
		mIndexBuffer->GetDesc(&desc);

		// 修改缓冲区描述
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

		// 创建影子缓冲
		mD3D11Device->CreateBuffer(&desc, nullptr, mIndexShadowBuffer.GetReference());

		// 复制数据
		mD3D11Context->CopyResource(mIndexShadowBuffer.Get(), mIndexBuffer.Get());
	}

	/** 解锁通过lockImpl锁定的缓冲区
	*/
	void D3D11HardwareIndexBuffer::UnlockImpl(void)
	{
		HRESULT hr = 0;

		if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC ||
			this->GetUsage() == DRE_BUFFER_USAGE_STATIC_WRITE_ONLY)
		{	
			mD3D11Context->Unmap(mIndexBuffer.Get(), 0);
		}
		else if (this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC ||
			this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY ||
			this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE )
		{
			switch (mLockOption)
			{
			// D3D11_USAGE_DYNAMIC时，mVertexBuffer不能读
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				mD3D11Context->Unmap(mIndexShadowBuffer.Get(), 0);
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				mD3D11Context->Unmap(mIndexBuffer.Get(), 0);
				break;
			}
		}
		else if (this->GetUsage() == DRE_BUFFER_USAGE_DEFAULT)
		{
			switch (mLockOption)
			{
			// D3D11_USAGE_DEFAULT时，直接unmap VertexShadowBuffer
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				mD3D11Context->Unmap(mIndexShadowBuffer.Get(), 0);
			// D3D11_USAGE_DEFAULT时，先复制VertexShadowBuffer回VertexBuffer，再
			// unmap VertexShadowBuffer
			case dream::DRE_LOCK_WRITE_ONLY:
				// 复制数据到影子数组
				mD3D11Context->CopyResource(mIndexBuffer.Get(), mIndexShadowBuffer.Get());
				mD3D11Context->Unmap(mIndexShadowBuffer.Get(), 0);
				break;
			}
		}

		D3D11_IF_FAILED_THROW(hr, "D3D11HardwareVertexBuffer::UnockImpl");
	}

}	// end namespace dream