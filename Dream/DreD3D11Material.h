///////////////////////////////
// date: 2014/9/2 18:24
// author: zoulei
//////////////////////////////

#ifndef __DRED3D11MATERIAL_H__
#define __DRED3D11MATERIAL_H__


#include "DreD3D11RenderDeclaration.h"

#include "DreMaterial.h"

namespace dream
{

	class D3D11Material : public Material
	{
		friend class D3D11RenderSystem;
	private:
		/// D3D11
		ID3D11DevicePtr								mD3D11Device;
		ID3D11DeviceContextPtr						mD3D11Context;

		/// D3D11 HLSL
		D3D11ShaderPtr								mShader;

		/// D3D11纹理数组
		D3D11TexturePtrMap							mTextureMap;
		typedef D3D11TexturePtrMap::iterator		D3D11TexturePtrMapIte;

		/// 采样器数组
		D3D11SamplerPtrMap							mSamplerMap;
		typedef D3D11SamplerPtrMap::iterator		D3D11SamplerPtrMapIte;

		/// 渲染参数集
		ID3D11BufferPtrMap							mRenderParamMap;
		typedef ID3D11BufferPtrMap::iterator		ID3D11BufferPtrMapIte;

	public:
		D3D11Material(ID3D11DeviceContextPtr context, D3D11ShaderPtr shader);

		/** 添加一个渲染参数
		* @param paramName 渲染管道使用的参数名
		* @param param 渲染参数
		*/
		void SetRenderParam(const string& paramName, RenderParamPtr& param) override;
		RenderParamPtr GetRenderParam(const string& param) override;

		/** 设置一个语义为sematics的sampler
		* @param	sematics	hlsl语义
		* @param	sampler		采样器
		*/
		SamplerPtr GetSampler(const c8* sematics) override;
		void SetSampler(const c8* sematics, SamplerPtr& sampler) override;

		/** 设置一个语义为sematics的texture
		* @param	sematics	hlsl语义
		* @param	texture		纹理
		*/
		TexturePtr GetTexture(const c8* sematics) override;
		void SetTexture(const c8* sematics, TexturePtr& texture) override;

		/** 设置Material对应的Shader
		*/
		ShaderPtr GetShader() override;
		void SetShader(ShaderPtr shader) override;
	};

}

#endif	// end of __DRED3D11MATERIAL_H__