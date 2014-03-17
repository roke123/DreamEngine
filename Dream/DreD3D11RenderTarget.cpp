#include "DreD3D11RenderTarget.h"

#include "DreD3D11RenderMapping.h"
#include "DreD3D11Texture.h"

namespace dream
{

	/** ���캯��
	* @param		/		width			��ȾĿ����
	* @param		/		height			��ȾĿ�곤��
	* @param	optional	hasDepth		�Ƿ������Ȼ���
	* @param	optional	hasStencil		�Ƿ����ģ�建��
	* @param	optional	fsaa			���ز�������
	* @param	optional	fassQuality		���ز�������
	*
	* @remark	��hasDepthΪtrue��hasStencilΪfalseʱ���Դ�����Ȼ��壬��DirectX11Ϊ��
	*			������ʽΪDXGI_FORMAT_D32_FLOAT������ΪDXGI_FORMAT_D24_UNORM_S8_UINT
	*/
	D3D11RenderTarget::D3D11RenderTarget(
		ID3D11RenderTargetViewPtr renderTarget, ID3D11DepthStencilViewPtr depthBuffer,
		ID3D11DevicePtr d3dDevice, u32 width, u32 height,
		bool hasDepth /* = false */, bool hasStencil /* = false */,
		u32 fsaa /* = 1 */, u32 fassQuality /* = 0 */) :
	//----------------------------------------------------------------------------
	RenderTarget(width, height, hasDepth, hasStencil, fsaa, fassQuality),
		mD3D11Device(d3dDevice),
		mD3D11RenderTarget(renderTarget), mD3D11DepthStencilView(depthBuffer)
	{
		mD3D11Device->GetImmediateContext(mD3D11Context.GetReference());
	}

	/** ����������
	*/
	D3D11RenderTarget::~D3D11RenderTarget()
	{
		// ����
	}

	/** ����RenderTarget
	* @param		/		width			��ȾĿ����
	* @param		/		height			��ȾĿ�곤��
	* @param	optional	hasDepth		�Ƿ������Ȼ���
	* @param	optional	hasStencil		�Ƿ����ģ�建��
	*
	* @remark	����RenderTarget���ʹԴRenderTargetʧЧ��Ҫ���°󶨵�RenderSystem
	*/
	void D3D11RenderTarget::ResizeRenderTarget(u32 width, u32 height)
	{
		D3D11ComPtr<ID3D11Texture2D> renderTexture;
		// ȡ�ײ�RenderTexture
		
		// renderTexture->AddRef
		mD3D11RenderTarget->GetResource((ID3D11Resource**)renderTexture.GetReference());
		if (renderTexture == nullptr)
		{
			DRE_EXCEPT(DRE_EXCEPTION_RENDERINGAPI_ERROR, "ȡ��RenderTarget�ײ�Texture2Dʧ��",
				"D3D11RenderTarget::ResizeRenderTarget");
		}

		// ȡrenderTexture����
		D3D11_TEXTURE2D_DESC renderTextureDesc = {0};
		renderTexture->GetDesc(&renderTextureDesc);
		// resize
		renderTextureDesc.Width = width;
		renderTextureDesc.Height = height;

		// renderTexture->AddRef
		HRESULT hr = mD3D11Device->CreateTexture2D(&renderTextureDesc, 0,
			renderTexture.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderTarget::ResizeRenderTarget");

		// ȡrenderTarget����
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		ZeroMemory(&renderTargetDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		mD3D11RenderTarget->GetDesc(&renderTargetDesc);

		D3D11ComPtr<ID3D11RenderTargetView> tempRenderTarget;
		// tempRenderTarget->AddRef
		hr = mD3D11Device->CreateRenderTargetView(renderTexture.Get(), &renderTargetDesc,
			tempRenderTarget.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderTarget::ResizeRenderTarget");
		
		if(HasDepthBuffer() || HasStencilBuffer())
		{
			DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_UNKNOWN;
			u32 flag = 0;
			if (HasDepthBuffer() && !HasStencilBuffer())
			{
				depthStencilFormat = DXGI_FORMAT_D32_FLOAT;
				flag = D3D11_DSV_READ_ONLY_DEPTH;
			}
			if (!HasDepthBuffer() && HasStencilBuffer())
			{
				depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = D3D11_DSV_READ_ONLY_STENCIL;
			}
			else // if(HasDepthBuffer() && HasStencilBuffer())
			{
				depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = 0;
			}

			D3D11_TEXTURE2D_DESC depthStencilTextureDesc = {0};
			depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilTextureDesc.CPUAccessFlags = 0;
			depthStencilTextureDesc.ArraySize = 0;
			depthStencilTextureDesc.Format = depthStencilFormat;
			depthStencilTextureDesc.Height = height;
			depthStencilTextureDesc.Width = width;
			depthStencilTextureDesc.MipLevels = 0;
			depthStencilTextureDesc.MiscFlags = 0;
			depthStencilTextureDesc.SampleDesc = renderTextureDesc.SampleDesc;

			D3D11ComPtr<ID3D11Texture2D> depthStencilTexture; 
			// renderTexture->AddRef
			HRESULT hr = mD3D11Device->CreateTexture2D(&depthStencilTextureDesc, 0,
				depthStencilTexture.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderTarget::ResizeRenderTarget");

			D3D11ComPtr<ID3D11DepthStencilView> tempDepthStencil;
			// ����depthStencil����
			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
			ZeroMemory( &depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC) );
			depthStencilDesc.Format = depthStencilFormat;
			if(depthStencilTextureDesc.SampleDesc.Count > 1)
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			else
			{
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilDesc.Texture2D.MipSlice = 0;
			}

			// tempDepthStencil->AddRef
			hr = mD3D11Device->CreateDepthStencilView(depthStencilTexture.Get(), &depthStencilDesc,
				tempDepthStencil.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderTarget::ResizeRenderTarget");

			// ת��resize���RenderTarget
			tempDepthStencil.Swap(mD3D11DepthStencilView);
		
		}

		SetWidth(width);
		SetHeight(height);

		tempRenderTarget.Swap(mD3D11RenderTarget);
	}

	/** ����ȾĿ�굼���ɾ�̬����
	*/
	TexturePtr D3D11RenderTarget::ExportAsStaticTexture(DRE_BUFFER_USAGE usage)
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

		return D3D11TexturePtr (
			new D3D11Texture(
				staticTexture, shaderResource, mD3D11Device,
				dataSize, bufferUsage, false, 
				renderTextureDesc.SampleDesc.Count, renderTextureDesc.SampleDesc.Quality
				)
			);
	}

	/** ����ȾĿ�굼���ɶ�̬����
	*/
	TexturePtr D3D11RenderTarget::ExportAsDynamicTexture()
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

}	// end namespace dream