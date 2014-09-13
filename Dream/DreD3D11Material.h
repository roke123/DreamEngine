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

		/// D3D11��������
		D3D11TexturePtrMap							mTextureMap;
		typedef D3D11TexturePtrMap::iterator		D3D11TexturePtrMapIte;

		/// ����������
		D3D11SamplerPtrMap							mSamplerMap;
		typedef D3D11SamplerPtrMap::iterator		D3D11SamplerPtrMapIte;

		/// ��Ⱦ������
		ID3D11BufferPtrMap							mRenderParamMap;
		typedef ID3D11BufferPtrMap::iterator		ID3D11BufferPtrMapIte;

	public:
		D3D11Material(ID3D11DeviceContextPtr context, D3D11ShaderPtr shader);

		/** ���һ����Ⱦ����
		* @param paramName ��Ⱦ�ܵ�ʹ�õĲ�����
		* @param param ��Ⱦ����
		*/
		void SetRenderParam(const string& paramName, RenderParamPtr& param) override;
		RenderParamPtr GetRenderParam(const string& param) override;

		/** ����һ������Ϊsematics��sampler
		* @param	sematics	hlsl����
		* @param	sampler		������
		*/
		SamplerPtr GetSampler(const c8* sematics) override;
		void SetSampler(const c8* sematics, SamplerPtr& sampler) override;

		/** ����һ������Ϊsematics��texture
		* @param	sematics	hlsl����
		* @param	texture		����
		*/
		TexturePtr GetTexture(const c8* sematics) override;
		void SetTexture(const c8* sematics, TexturePtr& texture) override;

		/** ����Material��Ӧ��Shader
		*/
		ShaderPtr GetShader() override;
		void SetShader(ShaderPtr shader) override;
	};

}

#endif	// end of __DRED3D11MATERIAL_H__