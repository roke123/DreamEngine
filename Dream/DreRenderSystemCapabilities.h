#ifndef __DRERENDERSYSTEMCAPABILITIES_H__
#define __DRERENDERSYSTEMCAPABILITIES_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	class DRE_EXPORT_CLASS RenderSystemCapabilities
	{
	private:
		/// 渲染配置
		set<string> mShaderProfileSet;

		/// 特性集
		u32 mCapabilitiesSet[DRE_CAPABILITIES_CATEGORY_COUNT];

		/// ConstantBuffer的数量
		u32 mNumOfConstantBuffer;
		                
		/// Sampler的数量
		u32 mNumOfSampler;

		/// Texture的数量
		u32 mNumOfTexture;

	public:
		/// 添加一个渲染文件配置
		void AddShaderProfiles(const string& shaderProfile)
		{
			mShaderProfileSet.insert(shaderProfile);
		}

		void AddSupportedCapabilitie(DRE_CAPABILITIES_FEATURE capabilitie)
		{
			// 找到特性对应组别
			u32 index = (CAPS_CATEGORY_MASK & capabilitie) >> CAPS_BITSHIFT;
			// 设置支持某特性
			mCapabilitiesSet[index] |= (capabilitie & ~CAPS_CATEGORY_MASK);
		}

		/** 设置ConstantBuffer的最大数量
		*/
		void SetNumOfConstantBuffer(u32 numOfConstantBuffer)
		{
			mNumOfConstantBuffer = numOfConstantBuffer;
		}

		/** 设置Sampler的最大数量
		*/
		void SetNumOfSampler(u32 numOfSampler)
		{
			mNumOfSampler = numOfSampler;
		}

		/** 设置Texture的最大数量
		*/
		void SetNumOfTexture(u32 numOfTexture)
		{
			mNumOfTexture = numOfTexture;
		}

		/** 检查是否存在某个渲染文件配置
		*/
		bool HasShaderProfile(const string& shaderProfile)
		{
			ShaderProfileSet::iterator ite = mShaderProfileSet.find(shaderProfile);
			if(ite != mShaderProfileSet.end())
				return true;

			return false;
		}

		/** 检查是否支持某个特性
		*/
		bool HasSupportedCapabilitie(DRE_CAPABILITIES_FEATURE capabilitie)
		{
			// 找到特性对应组别
			u32 index = (CAPS_CATEGORY_MASK & capabilitie) >> CAPS_BITSHIFT;
			
			if (mCapabilitiesSet[index] & (capabilitie & ~CAPS_CATEGORY_MASK))
				return true;

			return false;
		}

		/** 获取ConstantBuffer的最大数量
		*/
		u32 GetNumOfConstantBuffer(void) { return mNumOfConstantBuffer; }

		/** 获取Sampler的最大数量
		*/
		u32 GetNumOfSampler(void) { return mNumOfSampler; }

		/** 获取Texture的最大数量
		*/
		u32 GetNumOfTexture(void) { return mNumOfTexture; }

	};	// end class RenderSystemCapabilities

}	// end namespace dream

#endif	// end of __DRERENDERSYSTEMCAPABILITIES_H__