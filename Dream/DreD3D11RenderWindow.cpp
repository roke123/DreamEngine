#include "DreD3D11RenderWindow.h"

#include "DreD3D11RenderMapping.h"
#include "DreD3D11Texture.h"

namespace dream
{
	/** ���캯��
		*/
	D3D11RenderWindow::D3D11RenderWindow(
		IDXGISwapChainPtr swapChain, HWND hwnd, ID3D11DevicePtr d3dDevice,
		ID3D11RenderTargetViewPtr renderTarget, ID3D11DepthStencilViewPtr depthStencil,
		u32 width, u32 height, bool isFullScreen,
		bool hasDepth, bool hasStencil, u32 fsaa, u32 fassQuality) :
	//--------------------------------------------------------------
	RenderWindow(width, height, isFullScreen, hasDepth, hasStencil, fsaa, fassQuality),
		mD3D11SwapChain(swapChain), mHWindow(hwnd), mD3D11Device(d3dDevice),
		mD3D11RenderTarget(renderTarget), mD3D11DepthStencil(depthStencil)
	{
		mD3D11Device->GetImmediateContext(mD3D11Context.GetReference());
	}

	/** ����������
	*/
	D3D11RenderWindow::~D3D11RenderWindow()
	{
		// ����
	}

	/** ����RenderWindow��С
	* @param	width			��ȾĿ����
	* @param	height			��ȾĿ�곤��
	*/
	void D3D11RenderWindow::ResizeRenderWindow(u32 width, u32 height)
	{		
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {0};
		mD3D11SwapChain->GetDesc(&swapChainDesc);

		HRESULT hr = mD3D11SwapChain->ResizeBuffers(swapChainDesc.BufferCount, width, height,
			swapChainDesc.BufferDesc.Format, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH );
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResizeRenderWindow");

		D3D11ComPtr<ID3D11Texture2D> backBuffer;
		// backBuffer->AddRef
		hr = mD3D11SwapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)backBuffer.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResizeRenderWindow");

		// ȡbackBuffer����
		D3D11_TEXTURE2D_DESC backBufferDesc = {0};
		backBuffer->GetDesc(&backBufferDesc);

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		ZeroMemory(&renderTargetDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetDesc.Format = backBufferDesc.Format;
		if(swapChainDesc.SampleDesc.Count > 1)
		{
			renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetDesc.Texture2D.MipSlice = 0;
		}

		D3D11ComPtr<ID3D11RenderTargetView> tempRenderTarget;
		// tempRenderTarget->AddRef
		hr = mD3D11Device->CreateRenderTargetView(backBuffer.Get(), &renderTargetDesc,
			tempRenderTarget.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResizeRenderWindow");

		if(mD3D11DepthStencil != nullptr)
		{
			// depthStencil�Ķ�ȡ��־
			u32 flag = 0;

			D3D11_TEXTURE2D_DESC depthStencilTextureDesc = backBufferDesc;
			depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			if(HasDepthBuffer() && !HasStencilBuffer())
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
				flag = D3D11_DSV_READ_ONLY_DEPTH;
			}
			else if(!HasDepthBuffer() && HasStencilBuffer())
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = D3D11_DSV_READ_ONLY_STENCIL;
			}
			else // if(HasDepthBuffer() && HasStencilBuffer())
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = 0;
			}

			D3D11ComPtr<ID3D11Texture2D> depthStencilTexture;
			// depthStencilTexture->AddRef
			hr = mD3D11Device->CreateTexture2D(&depthStencilTextureDesc, nullptr, 
				depthStencilTexture.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResizeRenderWindow");

			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
			depthStencilDesc.Format = depthStencilTextureDesc.Format;
			if(depthStencilTextureDesc.SampleDesc.Count > 1)
			{
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			}
			else
			{
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilDesc.Texture2D.MipSlice = 0;
			}
			depthStencilDesc.Flags = flag;
			
			D3D11ComPtr<ID3D11DepthStencilView> tempDepthStencil;
			// tempDepthStencil->AddRef
			hr = mD3D11Device->CreateDepthStencilView(depthStencilTexture.Get(), &depthStencilDesc,
				tempDepthStencil.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResizeRenderWindow");

			// ��ԭDepthStencil�ͷ�
			tempDepthStencil.Swap(mD3D11DepthStencil);
		}

		SetWidth(width);
		SetHeight(height);

		// ��ԭrenderTarget�ͷ�
		tempRenderTarget.Swap(mD3D11RenderTarget);

	}

	/** ���ݴ��ڴ�С����RenderWindow��С
	* @param	width			��ȾĿ����
	* @param	height			��ȾĿ�곤��
	*/
	void D3D11RenderWindow::ResizeRenderWindow()
	{
		RECT rc = {0};
		GetWindowRect(mHWindow, &rc);

		ResizeRenderWindow(rc.right - rc.left, rc.bottom - rc.top);
	}

	/** ����RenderWindow�Ĳ�����
	* @param	fsaa			��������
	* @param	fassQuality		��������
	*/
	void D3D11RenderWindow::ResetRenderWindow(u32 width, u32 height, u32 fsaa, u32 fassQuality,
		bool hasDepth, bool hasStencil)
	{
		D3D11ComPtr<IDXGIFactory> dxgiFactory;
		// dxgiFactory->AddRef
		HRESULT hr = CreateDXGIFactory1(IID_IDXGIFactory, (void**)dxgiFactory.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResetRenderWindow");
	
		// ȡswapChain����
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {0};
		mD3D11SwapChain->GetDesc(&swapChainDesc);

		swapChainDesc.SampleDesc.Count = fsaa;
		swapChainDesc.SampleDesc.Quality = fassQuality;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Width = width;

		D3D11ComPtr<IDXGISwapChain> tempSwapChain;
		// tempSwapChain->AddRef
		hr = dxgiFactory->CreateSwapChain(mD3D11Device.Get(), &swapChainDesc,
			tempSwapChain.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResetRenderWindow");

		D3D11ComPtr<ID3D11Texture2D> backBuffer;
		// backBuffer->AddRef
		hr = mD3D11SwapChain->GetBuffer(0, IID_ID3D11Texture2D,
			(void**)backBuffer.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResetRenderWindow");

		// ȡbackBuffer����
		D3D11_TEXTURE2D_DESC backBufferDesc = {0};
		backBuffer->GetDesc(&backBufferDesc);

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		ZeroMemory(&renderTargetDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetDesc.Format = backBufferDesc.Format;
		if(swapChainDesc.SampleDesc.Count > 1)
		{
			renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetDesc.Texture2D.MipSlice = 0;
		}

		D3D11ComPtr<ID3D11RenderTargetView> tempRenderTarget;
		// tempRenderTarget->AddRef
		hr = mD3D11Device->CreateRenderTargetView(backBuffer.Get(), &renderTargetDesc,
			tempRenderTarget.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResetRenderWindow");

		if(hasDepth || hasStencil)
		{
			// depthStencil�Ķ�ȡ��־
			u32 flag = 0;
			// Depthλ��
			u32 depthBits = 0;

			D3D11_TEXTURE2D_DESC depthStencilTextureDesc = backBufferDesc;
			depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			if(hasDepth && !hasStencil)
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
				flag = D3D11_DSV_READ_ONLY_DEPTH;
				depthBits = 32;
			}
			else if(!hasDepth && hasStencil)
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = D3D11_DSV_READ_ONLY_STENCIL;
				depthBits = 32;
			}
			else // if(hasDepth && HasStencilBuffer())
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = 0;
			}

			D3D11ComPtr<ID3D11Texture2D> depthStencilTexture;
			// depthStencilTexture->AddRef
			hr = mD3D11Device->CreateTexture2D(&depthStencilTextureDesc, nullptr, 
				depthStencilTexture.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResetRenderWindow");

			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
			depthStencilDesc.Format = depthStencilTextureDesc.Format;
			if(depthStencilTextureDesc.SampleDesc.Count > 1)
			{
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			}
			else
			{
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilDesc.Texture2D.MipSlice = 0;
			}
			depthStencilDesc.Flags = flag;
			
			D3D11ComPtr<ID3D11DepthStencilView> tempDepthStencil;
			// tempDepthStencil->AddRef
			hr = mD3D11Device->CreateDepthStencilView(depthStencilTexture.Get(), &depthStencilDesc,
				tempDepthStencil.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::ResetRenderWindow");

			SetDepthBuffer(hasDepth);
			SetStencilBuffer(hasStencil);
			SetDepthBits(depthBits);

			tempDepthStencil.Swap(mD3D11DepthStencil);
		}
		else
		{
			SetDepthBuffer(false);
			SetStencilBuffer(false);
			SetDepthBits(0);
		}

		SetWidth(width);
		SetHeight(height);
		SetFASSCount(fsaa);
		SetFASSQuality(fassQuality);

		// ��ԭrenderTarget�ͷ�
		tempRenderTarget.Swap(mD3D11RenderTarget);

		// ��ԭswapChain�ͷ�
		tempSwapChain.Swap(mD3D11SwapChain);
	}

	/** ʹRenderWindowȫ��
	*/
	void D3D11RenderWindow::SetFullscreenState(bool enabled)
	{
		HRESULT hr = mD3D11SwapChain->SetFullscreenState(enabled, nullptr);
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderWindow::SetFullScreen");

		// ���ú�̨����
		ResizeRenderWindow();
		
		SetFullScreen(enabled);
	}

	/** ����ȾĿ�굼���ɾ�̬����
	*/
	TexturePtr D3D11RenderWindow::ExportAsStaticTexture(DRE_BUFFER_USAGE usage)
	{
		D3D11ComPtr<ID3D11Texture2D> renderTexture;
		// ȡ�ײ�RenderTexture
		
		// renderTexture->AddRef
		mD3D11RenderTarget->GetResource((ID3D11Resource**)renderTexture.GetReference());
		if (renderTexture == nullptr)
		{
			DRE_EXCEPT(DRE_EXCEPTION_RENDERINGAPI_ERROR, "ȡ��RenderTarget�ײ�Texture2Dʧ��",
				"D3D11RenderTarget::ExportAsStaticTexture");
		}

		// ȡrenderTexture����
		D3D11_TEXTURE2D_DESC renderTextureDesc = {0};
		renderTexture->GetDesc(&renderTextureDesc);

		renderTextureDesc.Usage = D3D11RenderMapping::Get(usage);
		renderTextureDesc.CPUAccessFlags = D3D11RenderMapping::GetCPUAccess(usage);
		renderTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		renderTextureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
		
		D3D11ComPtr<ID3D11Texture2D> staticTexture;
		// staticTexture->AddRef
		HRESULT hr = mD3D11Device->CreateTexture2D(&renderTextureDesc, nullptr,
			staticTexture.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderTarget::ExportAsStaticTexture");

		// ��������
		mD3D11Context->CopyResource(staticTexture.Get(), renderTexture.Get());

		D3D11ComPtr<ID3D11ShaderResourceView> shaderResource;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc;
		ZeroMemory(&shaderResource, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		shaderResourceDesc.Format = renderTextureDesc.Format;
		if(renderTextureDesc.SampleDesc.Count > 1)
		{
			shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceDesc.Texture2D.MipLevels = D3D11_MIP_LEVELS;
			shaderResourceDesc.Texture2D.MostDetailedMip = D3D11_MOST_DETAILED_MIP;
		}

		hr = mD3D11Device->CreateShaderResourceView(staticTexture.Get(), &shaderResourceDesc,
			shaderResource.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderTarget::ExportAsStaticTexture");

		u32 dataSize = renderTextureDesc.Width * renderTextureDesc.Height * 
			PixelUtil::GetPixelFormatBpp(D3D11RenderMapping::Get(renderTextureDesc.Format));
		DRE_BUFFER_USAGE bufferUsage = D3D11RenderMapping::Get(renderTextureDesc.Usage, renderTextureDesc.CPUAccessFlags);

		return TexturePtr (
			new D3D11Texture(
				staticTexture, shaderResource, mD3D11Device,
				dataSize, bufferUsage, false, 
				renderTextureDesc.SampleDesc.Count, renderTextureDesc.SampleDesc.Quality
				)
			);
	}

	/** ����ȾĿ�굼���ɶ�̬����
	*/
	TexturePtr D3D11RenderWindow::ExportAsDynamicTexture()
	{
		D3D11ComPtr<ID3D11Texture2D> renderTexture;
		// ȡ�ײ�RenderTexture
		
		// renderTexture->AddRef
		mD3D11RenderTarget->GetResource((ID3D11Resource**)renderTexture.GetReference());
		if (renderTexture == nullptr)
		{
			DRE_EXCEPT(DRE_EXCEPTION_RENDERINGAPI_ERROR, "ȡ��RenderTarget�ײ�Texture2Dʧ��",
				"D3D11RenderTarget::ExportAsDynamicTexture");
		}

		// ȡrenderTexture����
		D3D11_TEXTURE2D_DESC renderTextureDesc = {0};
		renderTexture->GetDesc(&renderTextureDesc);
		if(!(renderTextureDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE))
		{
			DRE_EXCEPT(DRE_EXCEPTION_RENDERINGAPI_ERROR, "��RenderTarget���ܱ�������̬Texture",
				"D3D11RenderTarget::ExportAsDynamicTexture");
		}

		D3D11ComPtr<ID3D11ShaderResourceView> shaderResource;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc;
		ZeroMemory(&shaderResource, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		shaderResourceDesc.Format = renderTextureDesc.Format;
		if(renderTextureDesc.SampleDesc.Count > 1)
		{
			shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceDesc.Texture2D.MipLevels = D3D11_MIP_LEVELS;
			shaderResourceDesc.Texture2D.MostDetailedMip = D3D11_MOST_DETAILED_MIP;
		}

		HRESULT hr = mD3D11Device->CreateShaderResourceView(renderTexture.Get(),
			&shaderResourceDesc, shaderResource.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderTarget::ExportAsStaticTexture");

		u32 dataSize = renderTextureDesc.Width * renderTextureDesc.Height * 
			PixelUtil::GetPixelFormatBpp(D3D11RenderMapping::Get(renderTextureDesc.Format));
		DRE_BUFFER_USAGE bufferUsage = D3D11RenderMapping::Get(renderTextureDesc.Usage, renderTextureDesc.CPUAccessFlags);

		return D3D11TexturePtr (
			new D3D11Texture(
				renderTexture, shaderResource, mD3D11Device,
				dataSize, bufferUsage, false, 
				renderTextureDesc.SampleDesc.Count, renderTextureDesc.SampleDesc.Quality
				)
			);
	}

	HWND D3D11RenderWindow::GetWindowHandle()
	{
		return mHWindow;
	}

}	// end namespace dream