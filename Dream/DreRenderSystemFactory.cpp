#include "DreRenderSystemFactory.h"

#include "DreD3D11RenderSystem.h"
#include "DreD3D11Adapter.h"

#include "DreMemoryAllocatorConfig.h"

namespace dream
{

	RenderSystemPtr RenderSystemFactory::CreateD3D11RenderSystem(AdapterPtr adapter)
	{
		DreAssert(adapter != nullptr, "��Ⱦ�豸����Ϊ�գ�Func��RenderSystemFactory::CreateD3D11RenderSystem");

		D3D11AdapterPtr d3dAdapter(dynamic_pointer_cast<D3D11Adapter, Adapter>(adapter));

		// Ҫʹ�þ���Ӳ������ʾ����������D3D11�����driverTypes��ΪD3D_DRIVER_TYPE_UNKNOWN
#		if !defined(_DEBUG) && !defined(DEBUG)
			D3D_DRIVER_TYPE driverTypes = D3D_DRIVER_TYPE_UNKNOWN;
			IDXGIAdapter* realAdapter = d3dAdapter->GetDXGIAdapter().Get();
#		else
		// ʹ��VS�Դ���DirectX���Թ���ʱ������ѡ��Ĭ����ʾ������
			D3D_DRIVER_TYPE driverTypes = D3D_DRIVER_TYPE_HARDWARE;
			IDXGIAdapter* realAdapter = nullptr;
#		endif

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};
		unsigned int totalFeatureLevels = ARRAYSIZE( featureLevels );

		// D3D11�豸������־
		u32 creationFlags = 0;
#		ifdef _DEBUG
			creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#		endif

		ID3D11DevicePtr d3dDevice;
		ID3D11DeviceContextPtr d3dContext;

		D3D_FEATURE_LEVEL feature = D3D_FEATURE_LEVEL_11_0;

		// ����D3D11�豸
		HRESULT hr = D3D11CreateDevice(
			realAdapter, driverTypes, 0, creationFlags,
			featureLevels, totalFeatureLevels,
			D3D11_SDK_VERSION,
			d3dDevice.GetReference(), &feature, d3dContext.GetReference());
		D3D11_IF_FAILED_THROW(hr, "RenderSystemFactory::CreateD3D11RenderSystem");

		return D3D11RenderSystemPtr(
			DREAM_NEW D3D11RenderSystem(
				d3dDevice, d3dContext, adapter
			)
		);
	}

	AdapterPtr RenderSystemFactory::GetD3D11RenderAdapter(u32 index)
	{
		IDXGIFactoryPtr dxgiFactory;
		HRESULT hr = CreateDXGIFactory1(IID_IDXGIFactory, (void**)dxgiFactory.GetReference());
		if (FAILED(hr))
		{
			DRE_EXCEPT(DRE_EXCEPTION_RENDERINGAPI_ERROR, DXGetErrorDescription(hr),
				"RenderSystemFactory::GetD3D11RenderAdapterList");
		}

		IDXGIAdapterPtr d3dAdapter;
		dxgiFactory->EnumAdapters(index, d3dAdapter.GetReference());
		if (FAILED(hr))
		{
			DRE_EXCEPT(DRE_EXCEPTION_RENDERINGAPI_ERROR, DXGetErrorDescription(hr),
				"RenderSystemFactory::GetD3D11RenderAdapterList");
		}

		if(d3dAdapter != nullptr)
			return D3D11AdapterPtr(DREAM_NEW D3D11Adapter(d3dAdapter));
		else
			return D3D11AdapterPtr();
	}

}	// end namespace dream