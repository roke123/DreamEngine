#ifndef __DRENORMALIMAGE_H__
#define __DRENORMALIMAGE_H__

#include "DreIOSystemDeclaration.h"

#include "DreImage.h"

namespace dream
{

	class NormalImage : public Image
	{
	public:
		/** ���캯��
		*/
		NormalImage(u8Array data, u32 width, u32 height, DRE_PIXEL_FORMAT format,
			bool isCopy = false);

		/** ��������
 		*/
		~NormalImage();

		/** ���ƹ��캯��
		*/
		NormalImage(const NormalImage& rh);

		/** ��ֵ������
 		*/
		NormalImage& operator = (const NormalImage& rh);

		const u8* GetDataPtr() const override;

		ImagePtr Copy() const override;

	private:
		/// ͼƬ����
		u8Array mData;
	};	// end class NormalImage

}	// end namespace dream

#endif	// end __DRENORMALIMAGE_H__