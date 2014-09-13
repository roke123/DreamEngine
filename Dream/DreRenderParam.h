#ifndef __DRERENDERPARAM_H__
#define __DRERENDERPARAM_H__

#include "DreRenderDeclaration.h"

namespace dream
{
	/**
	* ������Ⱦ�Ĳ���
	*/
	class DRE_EXPORT_CLASS RenderParam
	{
	public:
		/** ���캯��
		* @param param �������Ⱦ����
		* @param size ��Ⱦ���ݳ���
		* @param isCopy �Ƿ����·����ڴ沢��������
		*/
		RenderParam(void * param, u32 sizeInByte, bool isCopy = true )
		{
			mIsCopy = isCopy;
			mSizeInByte = sizeInByte;

			if (isCopy)
			{
				param = malloc(sizeInByte);
				if(param == nullptr)
				{
					DRE_EXCEPT(DRE_EXCEPTION_OUT_OF_MEMORY, "��ʣ��ɷ����ڴ�", "RenderParam::RenderParam");
				}

				memcpy(mParam, param, sizeInByte);
			}
			else
			{
				mParam = param;
			}
		}

	private:
		RenderParam(const RenderParam&);
		RenderParam& operator = (const RenderParam&);

	public:
		/** ��������
		*/
		~RenderParam()
		{
			if(mIsCopy)
			{
				free(mParam);
			}
		}

		/** ȡ������ָ��
		* @return �������Ⱦ����
		*/
		template<class T>
		T* GetParamAs() { return static_cast<T*>(mParam); }

		void* GetParam() { return mParam; }

		u32 GetSize() { return mSizeInByte;}

	private:
		/// ��Ⱦ������
		void* mParam;
		/// ��Ⱦ�����ݳ���
		u32 mSizeInByte;
		/// �Ƿ�����ݽ��и��Ʊ�־
		bool mIsCopy;
	};	// end class RenderParam

}	// end namespace dream

#endif	// end og __DREMATERIAL_H__