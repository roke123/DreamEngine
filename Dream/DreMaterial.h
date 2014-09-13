///////////////////////////////
// date： 2014/9/2 17:06
// author：zoulei
//////////////////////////////

#ifndef __DREMATERIAL_H__
#define __DREMATERIAL_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	/**
	* 渲染材质（包括 shader 以及 参数）
	*/
	class Material {
	private:
		/// RenderSystem
		RenderSystemPtr mRenderSystem;

		/// 渲染参数集
		RenderParamPtrMap mRenderParamMap;

	public:
		Material(RenderSystemPtr& renderSystem);

		/// 虚析构函数
		virtual ~Material() {}

		/** 添加一个渲染参数
		* @param paramName 渲染管道使用的参数名
		* @param param 渲染参数
		*/
		virtual void SetRenderParam(const string& paramName, RenderParamPtr& param) = 0;

		/** 取得一个渲染函数
		*/
		virtual RenderParamPtr GetRenderParam(const string& param) = 0;

		/** 设置一个语义为sematics的sampler
		* @param	sematics	hlsl语义
		* @param	sampler		采样器
		*/	
		virtual SamplerPtr GetSampler(const c8* sematics) = 0;
		virtual void SetSampler(const c8* sematics, SamplerPtr& sampler) = 0;

		/** 设置一个语义为sematics的texture
		* @param	sematics	hlsl语义
		* @param	texture		纹理
		*/
		virtual TexturePtr GetTexture(const c8* sematics) = 0;
		virtual void SetTexture(const c8* sematics, TexturePtr& texture) = 0;

		/** 设置Material对应的Shader
		*/
		virtual ShaderPtr GetShader() = 0;
		virtual void SetShader(ShaderPtr shader) = 0;
	};

}

#endif	// end __DREMATERIAL_H__