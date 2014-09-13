#include "DreD3D11Shader.h"

namespace dream
{

	/** 构造函数
	*/
	D3D11Shader::D3D11Shader(
		ID3D10BlobPtr shaderBuffer,
		ID3D11VertexShaderPtr vs, ID3D11ShaderReflectionPtr vsReflect,
		ID3D11DomainShaderPtr ds, ID3D11ShaderReflectionPtr dsReflect,
		ID3D11HullShaderPtr hs, ID3D11ShaderReflectionPtr hsReflect,
		ID3D11GeometryShaderPtr gs, ID3D11ShaderReflectionPtr gsReflect,
		ID3D11PixelShaderPtr ps, ID3D11ShaderReflectionPtr psReflect) :
	//---------------------------------------------------------------
		mShaderBuffer(shaderBuffer),
		mVertexShader(vs),		mVertexShaderReflect(vsReflect),
		mDomainShader(ds),		mDomainShaderReflect(dsReflect),
		mHullShader(hs),		mHullShaderReflect(hsReflect),
		mGeometryShader(gs),	mGeometryShaderReflect(gsReflect),
		mPixelShader(ps),		mPixelShaderReflect(psReflect)
	{
		// 留空
	}

	/** 析构函数
	*/
	D3D11Shader::~D3D11Shader()
	{
		// 留空
	}

}	// end namespace dream