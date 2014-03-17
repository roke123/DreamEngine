#include "DreD3D11HardwareVertexBuffer.h"

#include "DreD3D11RenderMapping.h"

namespace dream
{

	D3D11HardwareVertexBuffer::D3D11HardwareVertexBuffer(
		ID3D11BufferPtr vertexBuffer, ID3D11DevicePtr d3d11Device,
		u32 vertexSize, u32 numVertices,
		DRE_PRIMITIVE_TOPOLOGY vertexType, 
		DRE_BUFFER_USAGE usage,
		bool hasInstanceData /* = false */, u32 instanceDataStepRate /* = 0 */) throw() :
	//------------------------------------------------------------------------------------------------------
	HardwareVertexBuffer(vertexSize, numVertices, usage, vertexType, hasInstanceData, instanceDataStepRate),
		mVertexBuffer(vertexBuffer), 
		mD3D11Device(d3d11Device)
	{
		mD3D11Device->GetImmediateContext(mD3D11Context.GetReference());
	}

	D3D11HardwareVertexBuffer::~D3D11HardwareVertexBuffer()
	{
		// 留空
	}

	/** 锁定缓冲区的实现方法
	* @param offset 锁定缓冲区的开始端偏移
	* @param length 锁定缓冲区长度
	* @param options 锁定缓冲区方式
	*/
	void* D3D11HardwareVertexBuffer::LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS option)
	{
		mLockOption = option;

		// map选项
		D3D11_MAP mapOption = D3D11RenderMapping::Get(option);
		HRESULT hr = 0;

		if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC)
		{			
			hr = mD3D11Context->Map(mVertexBuffer.Get(), 0, mapOption, 0, &mSubResource);
		}

		else if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC_WRITE_ONLY)
		{
			switch (option)
			{
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式不支持读出数据",
					"D3D11HardwareVertexBuffer::LockImpl");
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				hr = mD3D11Context->Map(mVertexBuffer.Get(), 0, mapOption, 0, &mSubResource);
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
					hr = mD3D11Context->Map(mVertexShadowBuffer.Get(), 0, mapOption, 0, &mSubResource);
				}
				else
				{
					DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式不支持读出数据",
						"D3D11HardwareVertexBuffer::LockImpl");
				}
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
				hr = mD3D11Context->Map(mVertexBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				if(this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE)
				{
					DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式仅支持DISCARD方式读出数据",
						"D3D11HardwareVertexBuffer::LockImpl");
				}
				hr = mD3D11Context->Map(mVertexBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			}
		}

		else //if (this->GetUsage() == DRE_BUFFER_USAGE_DEFAULT)
		{
			//
			switch (option)
			{
			// D3D11_USAGE_DEFAULT时，mVertexBuffer不能读也不能写
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
			case dream::DRE_LOCK_WRITE_ONLY:
				// 复制数据到影子数组
				CopyToShadowResource();
				hr = mD3D11Context->Map(mVertexShadowBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_NO_OVERWRITE:
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "当前缓冲区格式不支持DISCARD和NO OVERWRITE方式读出数据",
					"D3D11HardwareVertexBuffer::LockImpl");
				break;
			}
		}

		D3D11_IF_FAILED_THROW(hr, "D3D11HardwareVertexBuffer::LockImpl");

		return mSubResource.pData;
	}

	void D3D11HardwareVertexBuffer::CopyToShadowResource()
	{
		D3D11_BUFFER_DESC desc = {0};
		mVertexBuffer->GetDesc(&desc);

		// 修改缓冲区描述
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

		// 创建影子缓冲
		mD3D11Device->CreateBuffer(&desc, nullptr, mVertexShadowBuffer.GetReference());

		// 复制数据
		mD3D11Context->CopyResource(mVertexShadowBuffer.Get(), mVertexBuffer.Get());
	}

	/** 解锁通过lockImpl锁定的缓冲区
	*/
	void D3D11HardwareVertexBuffer::UnlockImpl(void)
	{
		HRESULT hr = 0;

		if (this->GetUsage() == DRE_BUFFER_USAGE_STATIC ||
			this->GetUsage() == DRE_BUFFER_USAGE_STATIC_WRITE_ONLY)
		{	
			mD3D11Context->Unmap(mVertexBuffer.Get(), 0);
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
				mD3D11Context->Unmap(mVertexShadowBuffer.Get(), 0);
				break;
			// 直接取顶点缓冲区
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				mD3D11Context->Unmap(mVertexBuffer.Get(), 0);
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
				mD3D11Context->Unmap(mVertexShadowBuffer.Get(), 0);
			// D3D11_USAGE_DEFAULT时，先复制VertexShadowBuffer回VertexBuffer，再
			// unmap VertexShadowBuffer
			case dream::DRE_LOCK_WRITE_ONLY:
				// 复制数据到影子数组
				mD3D11Context->CopyResource(mVertexBuffer.Get(), mVertexShadowBuffer.Get());
				mD3D11Context->Unmap(mVertexShadowBuffer.Get(), 0);
				break;
			}
		}

		D3D11_IF_FAILED_THROW(hr, "D3D11HardwareVertexBuffer::UnlockImpl");
	}

}	// end namespace dream