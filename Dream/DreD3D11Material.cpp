#include "DreD3D11Material.h"

#include "DreD3D11Texture.h"
#include "DreD3D11Sampler.h"
#include "DreD3D11Shader.h"

#include "DreMemoryAllocatorConfig.h"

namespace dream
{
	void D3D11Material::SetRenderParam(const string& paramName, RenderParamPtr& param)
	{
		ID3D11BufferPtrMapIte ite = mRenderParamMap.find(paramName);	

		if (param == nullptr)
		{
			if (ite != mRenderParamMap.end())
			{
				mRenderParamMap.erase(ite);
			}
		}
		else 
		{
			if (ite == mRenderParamMap.end())
			{
				D3D11_BUFFER_DESC bufferDesc = { 0 };														
				bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;										
				bufferDesc.CPUAccessFlags = 0;															
				bufferDesc.ByteWidth = param->GetSize();
				bufferDesc.MiscFlags = 0;																
				bufferDesc.StructureByteStride = 0;				
				// 感觉通过CPU访问还是比较少的，所以还是用 DEFAULT 吧
				bufferDesc.Usage = D3D11_USAGE_DEFAULT;
					
				D3D11_SUBRESOURCE_DATA bufferData = { 0 };												
				bufferData.pSysMem = param->GetParam();
					
				ID3D11BufferPtr buffer;																	
				HRESULT hr = mD3D11Device->CreateBuffer(&bufferDesc, &bufferData, buffer.GetReference());
				D3D11_IF_FAILED_THROW(hr, "D3D11Material::SetRenderParam");

				string _clone = paramName;
				mRenderParamMap.insert(make_pair<string, ID3D11BufferPtr>(std::move(_clone), std::move(buffer)));
			}
			else 
			{
				D3D11_BUFFER_DESC bufferDesc = { 0 };
				bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				bufferDesc.CPUAccessFlags = 0;
				bufferDesc.ByteWidth = param->GetSize();
				bufferDesc.MiscFlags = 0;
				bufferDesc.StructureByteStride = 0;
				// 初始化 然后 GPU读 并复制
				bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

				D3D11_SUBRESOURCE_DATA bufferData = { 0 };
				bufferData.pSysMem = param->GetParam();

				// 创建新的GPU缓冲
				ID3D11BufferPtr buffer;
				HRESULT hr = mD3D11Device->CreateBuffer(&bufferDesc, &bufferData, buffer.GetReference());
				D3D11_IF_FAILED_THROW(hr, "D3D11Material::SetRenderParam");

				mD3D11Context->CopyResource(ite->second.Get(), buffer.Get());
			}
		}
	}

	RenderParamPtr D3D11Material::GetRenderParam(const string& param)
	{
		ID3D11BufferPtrMapIte ite = mRenderParamMap.find(param);
		if (ite != mRenderParamMap.end())
		{
			// 取得源缓冲区描述
			D3D11_BUFFER_DESC bufferDesc = { 0 };
			ite->second->GetDesc(&bufferDesc);
	
			// 转换为 CPU READ 并且 为 STAGING
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			bufferDesc.Usage = D3D11_USAGE_STAGING;

			D3D11_SUBRESOURCE_DATA bufferData = { 0 };
			bufferData.pSysMem = nullptr;

			// 创建新的GPU缓冲
			ID3D11BufferPtr buffer;
			HRESULT hr = mD3D11Device->CreateBuffer(&bufferDesc, &bufferData, buffer.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11Material::SetRenderParam");
		
			// 取得数据
			mD3D11Context->CopyResource(buffer.Get(), ite->second.Get());

			D3D11_MAPPED_SUBRESOURCE resource = { 0 };
			// 锁定缓冲区
			hr = mD3D11Context->Map(buffer.Get(), 0, D3D11_MAP_READ, 0, &resource);
			D3D11_IF_FAILED_THROW(hr, "D3D11Material::SetRenderParam");

			RenderParamPtr renderParam(DREAM_NEW RenderParam(resource.pData, resource.RowPitch));

			// 解锁缓冲区
			mD3D11Context->Unmap(buffer.Get(), 0);

			// 返回参数值
			return renderParam;
		} 

		return nullptr;
	}

	/** 设置一个语义为sematics的sampler
	* @param	index		hlsl语义
	* @param	sampler		采样器
	*/
	void D3D11Material::SetSampler(const c8* sematics, SamplerPtr& sampler)
	{
		D3D11SamplerPtrMapIte ite = mSamplerMap.find(sematics);

		if (sampler == nullptr)
		{
			if (ite != mSamplerMap.end())
			{
				mSamplerMap.erase(ite);
			}
		}
		else
		{
			if (ite == mSamplerMap.end())
			{
				string _cloneSematics = string(sematics);
				D3D11SamplerPtr _cloneSampler = dynamic_pointer_cast<D3D11Sampler>(sampler);

				mSamplerMap.insert(make_pair<string, D3D11SamplerPtr>(std::move(_cloneSematics), std::move(_cloneSampler)));
			}
			else
			{
				ite->second = dynamic_pointer_cast<D3D11Sampler>(sampler);
			}
		}
	}

	SamplerPtr D3D11Material::GetSampler(const c8* sematics)
	{
		D3D11SamplerPtrMapIte ite = mSamplerMap.find(string(sematics));
		if (ite != mSamplerMap.end())
		{
			return ite->second;
		}

		return nullptr;
	}

	/** 设置一个语义为sematics的texture
	* @param	index		hlsl语义
	* @param	texture		纹理
	*/
	void D3D11Material::SetTexture(const c8* sematics, TexturePtr& texture)
	{
		D3D11TexturePtrMapIte ite = mTextureMap.find(sematics);

		if (texture == nullptr)
		{
			if (ite != mTextureMap.end())
			{
				mTextureMap.erase(ite);
			}
		}
		else
		{
			if (ite == mTextureMap.end())
			{
				string _cloneSematics = string(sematics);
				D3D11TexturePtr _cloneTexture = dynamic_pointer_cast<D3D11Texture>(texture);

				mTextureMap.insert(make_pair<string, D3D11TexturePtr>(std::move(_cloneSematics), std::move(_cloneTexture)));
			}
			else
			{
				ite->second = dynamic_pointer_cast<D3D11Texture>(texture);
			}
		}
	}

	TexturePtr D3D11Material::GetTexture(const c8* sematics)
	{
		D3D11TexturePtrMapIte ite = mTextureMap.find(string(sematics));
		if (ite != mTextureMap.end())
		{
			return ite->second;
		}

		return nullptr;
	}

	ShaderPtr D3D11Material::GetShader() { return mShader;  };
	void D3D11Material::SetShader(ShaderPtr shader) { mShader = dynamic_pointer_cast<D3D11Shader>(shader); };



}