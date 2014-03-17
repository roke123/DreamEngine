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
		// ����
	}

	/** ������������ʵ�ַ���
	* @param offset �����������Ŀ�ʼ��ƫ��
	* @param length ��������������
	* @param options ������������ʽ
	*/
	void* D3D11HardwareVertexBuffer::LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS option)
	{
		mLockOption = option;

		// mapѡ��
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
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "��ǰ��������ʽ��֧�ֶ�������",
					"D3D11HardwareVertexBuffer::LockImpl");
				break;
			// ֱ��ȡ���㻺����
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
			// D3D11_USAGE_DYNAMICʱ��mVertexBuffer���ܶ�
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				if(this->GetUsage() != DRE_BUFFER_USAGE_DYNAMIC)
				{
					// �������ݵ�Ӱ������
					CopyToShadowResource();
					hr = mD3D11Context->Map(mVertexShadowBuffer.Get(), 0, mapOption, 0, &mSubResource);
				}
				else
				{
					DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "��ǰ��������ʽ��֧�ֶ�������",
						"D3D11HardwareVertexBuffer::LockImpl");
				}
				break;
			// ֱ��ȡ���㻺����
			case dream::DRE_LOCK_DISCARD:
				hr = mD3D11Context->Map(mVertexBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			case dream::DRE_LOCK_WRITE_ONLY:
			case dream::DRE_LOCK_NO_OVERWRITE:
				if(this->GetUsage() == DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE)
				{
					DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "��ǰ��������ʽ��֧��DISCARD��ʽ��������",
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
			// D3D11_USAGE_DEFAULTʱ��mVertexBuffer���ܶ�Ҳ����д
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
			case dream::DRE_LOCK_WRITE_ONLY:
				// �������ݵ�Ӱ������
				CopyToShadowResource();
				hr = mD3D11Context->Map(mVertexShadowBuffer.Get(), 0, mapOption, 0, &mSubResource);
				break;
			// ֱ��ȡ���㻺����
			case dream::DRE_LOCK_DISCARD:
			case dream::DRE_LOCK_NO_OVERWRITE:
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "��ǰ��������ʽ��֧��DISCARD��NO OVERWRITE��ʽ��������",
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

		// �޸Ļ���������
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

		// ����Ӱ�ӻ���
		mD3D11Device->CreateBuffer(&desc, nullptr, mVertexShadowBuffer.GetReference());

		// ��������
		mD3D11Context->CopyResource(mVertexShadowBuffer.Get(), mVertexBuffer.Get());
	}

	/** ����ͨ��lockImpl�����Ļ�����
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
			// D3D11_USAGE_DYNAMICʱ��mVertexBuffer���ܶ�
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				mD3D11Context->Unmap(mVertexShadowBuffer.Get(), 0);
				break;
			// ֱ��ȡ���㻺����
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
			// D3D11_USAGE_DEFAULTʱ��ֱ��unmap VertexShadowBuffer
			case dream::DRE_LOCK_READWRITE:
			case dream::HDRE_LOCK_READ_ONLY:
				mD3D11Context->Unmap(mVertexShadowBuffer.Get(), 0);
			// D3D11_USAGE_DEFAULTʱ���ȸ���VertexShadowBuffer��VertexBuffer����
			// unmap VertexShadowBuffer
			case dream::DRE_LOCK_WRITE_ONLY:
				// �������ݵ�Ӱ������
				mD3D11Context->CopyResource(mVertexBuffer.Get(), mVertexShadowBuffer.Get());
				mD3D11Context->Unmap(mVertexShadowBuffer.Get(), 0);
				break;
			}
		}

		D3D11_IF_FAILED_THROW(hr, "D3D11HardwareVertexBuffer::UnlockImpl");
	}

}	// end namespace dream