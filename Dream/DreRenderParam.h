#ifndef __DRERENDERPARAM_H__
#define __DRERENDERPARAM_H__

#include "DreRenderDeclaration.h"

namespace dream
{
	/**
	* 用于渲染的参数
	*/
	class DRE_EXPORT_CLASS RenderParam
	{
	public:
		/** 构造函数
		* @param param 输入的渲染数据
		* @param size 渲染数据长度
		* @param isCopy 是否重新分配内存并创建副本
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
					DRE_EXCEPT(DRE_EXCEPTION_OUT_OF_MEMORY, "无剩余可分配内存", "RenderParam::RenderParam");
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
		/** 析构函数
		*/
		~RenderParam()
		{
			if(mIsCopy)
			{
				free(mParam);
			}
		}

		/** 取出数据指针
		* @return 输出的渲染数据
		*/
		template<class T>
		T* GetParamAs() { return static_cast<T*>(mParam); }

		void* GetParam() { return mParam; }

		u32 GetSize() { return mSizeInByte;}

	private:
		/// 渲染用数据
		void* mParam;
		/// 渲染用数据长度
		u32 mSizeInByte;
		/// 是否对数据进行复制标志
		bool mIsCopy;
	};	// end class RenderParam

}	// end namespace dream

#endif	// end og __DREMATERIAL_H__