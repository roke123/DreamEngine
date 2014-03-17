#ifndef __DRED3D11HLSLPROGRAM_H__
#define __DRED3D11HLSLPROGRAM_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreHLSLProgram.h"

namespace dream
{

	class D3D11HLSLProgram : public HLSLProgram
	{
		friend class D3D11RenderSystem;
	private:
		/** ππ‘Ï∫Ø ˝
		*/
		D3D11HLSLProgram(
			ID3D10BlobPtr shaderBuffer,
			ID3D11VertexShaderPtr vs,	ID3D11ShaderReflectionPtr vsReflect,
			ID3D11DomainShaderPtr ds,	ID3D11ShaderReflectionPtr dsReflect,
			ID3D11HullShaderPtr hs,		ID3D11ShaderReflectionPtr hsReflect,
			ID3D11GeometryShaderPtr gs, ID3D11ShaderReflectionPtr gsReflect,
			ID3D11PixelShaderPtr ps,	ID3D11ShaderReflectionPtr psReflect);

	public:
		/** Œˆππ∫Ø ˝
		*/
		~D3D11HLSLProgram() override;

		D3D11ComPtr<ID3D10Blob>	GetShaderBlob()		
		{ 
			return mShaderBuffer;
		};

		ID3D11VertexShaderPtr			GetVertexShader()	{ return mVertexShader; };
		ID3D11DomainShaderPtr			GetDomainShader()	{ return mDomainShader; };
		ID3D11HullShaderPtr				GetHullShader()		{ return mHullShader; };
		ID3D11GeometryShaderPtr			GetGeometryShader()	{ return mGeometryShader; };
		ID3D11PixelShaderPtr			GetPixelShader()	{ return mPixelShader; };

		ID3D11ShaderReflectionPtr		GetVertexShaderReflect()	{ return mVertexShaderReflect; };
		ID3D11ShaderReflectionPtr		GetDomainShaderReflect()	{ return mDomainShaderReflect; };
		ID3D11ShaderReflectionPtr		GetHullShaderReflect()		{ return mHullShaderReflect; };
		ID3D11ShaderReflectionPtr		GetGeometryShaderReflect()	{ return mGeometryShaderReflect; };
		ID3D11ShaderReflectionPtr		GetPixelShaderReflect()		{ return mPixelShaderReflect; };

	private:
		/// D3D11‰÷»æŒƒº˛±‡¬Î∫Ûª∫≥Â«¯
		ID3D10BlobPtr				mShaderBuffer;
		/// D3D11∂•µ„‰÷»æ
		ID3D11VertexShaderPtr		mVertexShader;
		/// D3D11”Ú‰÷»æ
		ID3D11DomainShaderPtr		mDomainShader;
		/// D3D11»•ø«‰÷»æ
		ID3D11HullShaderPtr		mHullShader;
		/// D3D11º∏∫Œ‰÷»æ
		ID3D11GeometryShaderPtr	mGeometryShader;
		/// D3D11œÒÀÿ‰÷»æ
		ID3D11PixelShaderPtr		mPixelShader;

		/// D3D11∂•µ„‰÷»æ∑¥…‰
		ID3D11ShaderReflectionPtr		mVertexShaderReflect;
		/// D3D11”Ú‰÷»æ∑¥…‰
		ID3D11ShaderReflectionPtr		mDomainShaderReflect;
		/// D3D11»•ø«‰÷»æ∑¥…‰
		ID3D11ShaderReflectionPtr		mHullShaderReflect;
		/// D3D11º∏∫Œ‰÷»æ∑¥…‰
		ID3D11ShaderReflectionPtr		mGeometryShaderReflect;
		/// D3D11œÒÀÿ‰÷»æ∑¥…‰
		ID3D11ShaderReflectionPtr		mPixelShaderReflect;

	};	// end class D3D11HLSLProgram

}	// end namespace dream

#endif	// end __DRED3D11HLSLPROGRAM_H__