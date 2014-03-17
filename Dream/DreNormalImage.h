#ifndef __DRENORMALIMAGE_H__
#define __DRENORMALIMAGE_H__

#include "DreIOSystemDeclaration.h"

#include "DreImage.h"

namespace dream
{

	class NormalImage : public Image
	{
	public:
		/** 构造函数
		*/
		NormalImage(u8Array data, u32 width, u32 height, DRE_PIXEL_FORMAT format,
			bool isCopy = false);

		/** 析构函数
 		*/
		~NormalImage();

		/** 复制构造函数
		*/
		NormalImage(const NormalImage& rh);

		/** 赋值操作符
 		*/
		NormalImage& operator = (const NormalImage& rh);

		const u8* GetDataPtr() const override;

		ImagePtr Copy() const override;

	private:
		/// 图片数据
		u8Array mData;
	};	// end class NormalImage

}	// end namespace dream

#endif	// end __DRENORMALIMAGE_H__