#ifndef __DRERENDERSYSTEMCAPABILITIES_H__
#define __DRERENDERSYSTEMCAPABILITIES_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	class DRE_EXPORT_CLASS RenderSystemCapabilities
	{
	private:
		/// ��Ⱦ����
		set<string> mShaderProfileSet;

		/// ���Լ�
		u32 mCapabilitiesSet[DRE_CAPABILITIES_CATEGORY_COUNT];

		/// ConstantBuffer������
		u32 mNumOfConstantBuffer;
		                
		/// Sampler������
		u32 mNumOfSampler;

		/// Texture������
		u32 mNumOfTexture;

	public:
		/// ���һ����Ⱦ�ļ�����
		void AddShaderProfiles(const string& shaderProfile)
		{
			mShaderProfileSet.insert(shaderProfile);
		}

		void AddSupportedCapabilitie(DRE_CAPABILITIES_FEATURE capabilitie)
		{
			// �ҵ����Զ�Ӧ���
			u32 index = (CAPS_CATEGORY_MASK & capabilitie) >> CAPS_BITSHIFT;
			// ����֧��ĳ����
			mCapabilitiesSet[index] |= (capabilitie & ~CAPS_CATEGORY_MASK);
		}

		/** ����ConstantBuffer���������
		*/
		void SetNumOfConstantBuffer(u32 numOfConstantBuffer)
		{
			mNumOfConstantBuffer = numOfConstantBuffer;
		}

		/** ����Sampler���������
		*/
		void SetNumOfSampler(u32 numOfSampler)
		{
			mNumOfSampler = numOfSampler;
		}

		/** ����Texture���������
		*/
		void SetNumOfTexture(u32 numOfTexture)
		{
			mNumOfTexture = numOfTexture;
		}

		/** ����Ƿ����ĳ����Ⱦ�ļ�����
		*/
		bool HasShaderProfile(const string& shaderProfile)
		{
			ShaderProfileSet::iterator ite = mShaderProfileSet.find(shaderProfile);
			if(ite != mShaderProfileSet.end())
				return true;

			return false;
		}

		/** ����Ƿ�֧��ĳ������
		*/
		bool HasSupportedCapabilitie(DRE_CAPABILITIES_FEATURE capabilitie)
		{
			// �ҵ����Զ�Ӧ���
			u32 index = (CAPS_CATEGORY_MASK & capabilitie) >> CAPS_BITSHIFT;
			
			if (mCapabilitiesSet[index] & (capabilitie & ~CAPS_CATEGORY_MASK))
				return true;

			return false;
		}

		/** ��ȡConstantBuffer���������
		*/
		u32 GetNumOfConstantBuffer(void) { return mNumOfConstantBuffer; }

		/** ��ȡSampler���������
		*/
		u32 GetNumOfSampler(void) { return mNumOfSampler; }

		/** ��ȡTexture���������
		*/
		u32 GetNumOfTexture(void) { return mNumOfTexture; }

	};	// end class RenderSystemCapabilities

}	// end namespace dream

#endif	// end of __DRERENDERSYSTEMCAPABILITIES_H__