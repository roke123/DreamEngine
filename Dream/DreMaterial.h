///////////////////////////////
// date�� 2014/9/2 17:06
// author��zoulei
//////////////////////////////

#ifndef __DREMATERIAL_H__
#define __DREMATERIAL_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	/**
	* ��Ⱦ���ʣ����� shader �Լ� ������
	*/
	class Material {
	private:
		/// RenderSystem
		RenderSystemPtr mRenderSystem;

		/// ��Ⱦ������
		RenderParamPtrMap mRenderParamMap;

	public:
		Material(RenderSystemPtr& renderSystem);

		/// ����������
		virtual ~Material() {}

		/** ���һ����Ⱦ����
		* @param paramName ��Ⱦ�ܵ�ʹ�õĲ�����
		* @param param ��Ⱦ����
		*/
		virtual void SetRenderParam(const string& paramName, RenderParamPtr& param) = 0;

		/** ȡ��һ����Ⱦ����
		*/
		virtual RenderParamPtr GetRenderParam(const string& param) = 0;

		/** ����һ������Ϊsematics��sampler
		* @param	sematics	hlsl����
		* @param	sampler		������
		*/	
		virtual SamplerPtr GetSampler(const c8* sematics) = 0;
		virtual void SetSampler(const c8* sematics, SamplerPtr& sampler) = 0;

		/** ����һ������Ϊsematics��texture
		* @param	sematics	hlsl����
		* @param	texture		����
		*/
		virtual TexturePtr GetTexture(const c8* sematics) = 0;
		virtual void SetTexture(const c8* sematics, TexturePtr& texture) = 0;

		/** ����Material��Ӧ��Shader
		*/
		virtual ShaderPtr GetShader() = 0;
		virtual void SetShader(ShaderPtr shader) = 0;
	};

}

#endif	// end __DREMATERIAL_H__