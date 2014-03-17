#include "DreNormalImage.h"

namespace dream
{

	NormalImage::NormalImage(u8Array data, u32 width, u32 height, DRE_PIXEL_FORMAT format,
		bool isCopy /* = false */) :
	//------------------------------------------------------------------------------------
	Image(width, height, format, isCopy),
		mData(data)
	{
		if (mIsCopy)
		{
			u32 dataSize = width * height * PixelUtil::GetPixelFormatBpp(mFormat);
			mData = u8Array(dataSize);
			memcpy(&mData[0], &data[0], sizeof(u8) * dataSize);
		}
	}

	NormalImage::NormalImage(const NormalImage& rh) :
	//-------------------------------------------------------------------------------------
	Image(rh.mWidth, rh.mHeight, rh.mFormat, true),
		mData(rh.GetSize())
	{
		memcpy(&mData[0], &rh.mData[0], sizeof(u8) * rh.GetSize());
	}

	NormalImage& NormalImage::operator = (const NormalImage& rh)
	{
		// ��ͬ��ʲô����������ֹ�ظ��ͷ��ڴ�
		if (this == &rh)
			return *this;

		mIsCopy = true;
		mData = u8Array(this->GetSize());
		memcpy(&mData[0], &rh.mData[0], sizeof(u8) * rh.GetSize());
		mWidth = rh.mWidth;
		mHeight = rh.mHeight;
		mFormat = rh.mFormat;

		return *this;
	}

	NormalImage::~NormalImage()
	{
		// ����
	}

	const u8* NormalImage::GetDataPtr() const
	{
		return &mData[0];
	}

	ImagePtr NormalImage::Copy() const
	{
		return NormalImagePtr(
			new NormalImage(
				mData, mWidth, mHeight, mFormat, true
			)
		);
	}
}