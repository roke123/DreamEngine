#include "DreFreeImageLoader.h"
#include "DreImage.h"
#include "DreException.h"

namespace dream
{

	FreeImageLoader::FreeImageLoader(FREE_IMAGE_FORMAT fif)
		: mFIF(fif)
	{
		// ����
	}

	ImagePtr FreeImageLoader::Load_Impl(const char* file)
	{
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file);
		if(fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(file);
			if(fif == FIF_UNKNOWN || FreeImage_FIFSupportsReading(fif))
			{	
				DRE_EXCEPT(DRE_EXCEPTION_INTERNAL_ERROR, string("���ܼ���").append(file).append("���͵��ļ�"),
					"FreeImageLoader::Loader");
			}
		}

		FIBITMAP* fiBitmap = FreeImage_Load(fif, file);
		if(fiBitmap == nullptr)
		{
			DRE_EXCEPT(DRE_EXCEPTION_INTERNAL_ERROR, string("�����ļ�").append(file).append("ʧ��"),
					"FreeImageLoader::Loader");
		}

		DRE_PIXEL_FORMAT imageFormat = DRE_PIXEL_FORMAT_UNKNOWN;
		u32 bpp = FreeImage_GetBPP(fiBitmap);
		FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(fiBitmap);
		FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(fiBitmap);

		switch (imageType)
		{
		case FIT_UNKNOWN:
		case FIT_UINT32:
		case FIT_INT32:
		case FIT_FLOAT:
		case FIT_DOUBLE:
		case FIT_COMPLEX:
		case FIT_RGBF:
		case FIT_RGBAF:
		default:
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, string("Dream�ݲ�֧���ļ�").append(file).append("�����ظ�ʽ"),
				"FreeImageLoader::Load")
			break;

		// ��׼λͼ
		case FIT_BITMAP:
			{
				
				// ����Ƿ�Ҷ�ͼ
				if (colorType == FIC_MINISWHITE || colorType == FIC_MINISBLACK)
				{
					// ת���Ҷ�ͼ
					FIBITMAP* newBitmap = FreeImage_ConvertToGreyscale(fiBitmap);
					FreeImage_Unload(fiBitmap);
					fiBitmap = newBitmap;
					bpp = FreeImage_GetBPP(fiBitmap);
				}
				// ����Ƿ��ɫ��λͼ��CMYKλͼ
				else if (bpp < 8 || colorType == FIC_PALETTE || colorType == FIC_CMYK)
				{
					FIBITMAP* newBitmap =  NULL;	
					// ���λͼ�Ƿ��͸��ͨ��
					if (FreeImage_IsTransparent(fiBitmap))
					{
						newBitmap = FreeImage_ConvertTo32Bits(fiBitmap);
					}
					else
					{
						newBitmap = FreeImage_ConvertTo24Bits(fiBitmap);
					}

					FreeImage_Unload(fiBitmap);
					fiBitmap = newBitmap;
					bpp = FreeImage_GetBPP(fiBitmap);
				}

				switch (bpp)
				{
				case 8:
					imageFormat = DRE_PIXEL_FORMAT_L_8;
					break;
				case 16:
					if(FreeImage_GetGreenMask(fiBitmap) == FI16_565_GREEN_MASK)
					{
						imageFormat = DRE_PIXEL_FORMAT_R5G6B5;
					}
					else
					{
						imageFormat = DRE_PIXEL_FORMAT_A1R5G5B5;
					}
					break;
				case 24:
					// ��FreeImage�Ƿ�ʹ��big endian
#					if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
						imageFormat = DRE_PIXEL_FORMAT_R8G8B8;
#					else
						imageFormat = DRE_PIXEL_FORMAT_B8G8R8;
#					endif
					break;
				case 32:
#					if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
						imageFormat = DRE_PIXEL_FORMAT_R8G8B8A8;
#					else
						imageFormat = DRE_PIXEL_FORMAT_A8R8G8B8;
#					endif
				break;

				default:
					break;
				}
			}
			break;
		case FIT_RGB16:
			imageFormat = DRE_PIXEL_FORMAT_R5G6B5;
			break;
		case FIT_RGBA16:
			imageFormat = DRE_PIXEL_FORMAT_A1R5G5B5;
			break;
		case FIT_UINT16:
			imageFormat = DRE_PIXEL_FORMAT_L_16;
			break;
		case FIT_INT16:
			imageFormat = DRE_PIXEL_FORMAT_L_16;
			break;
		}	// end switch

		u32 imageWidth = FreeImage_GetWidth(fiBitmap);
		u32 imageHeight = FreeImage_GetHeight(fiBitmap);
		
		return ImagePtr(new FreeImage(fiBitmap, imageWidth, imageHeight, imageFormat));
	}

	ImagePtr FreeImageLoader::Load_Impl(u8Array data, u32 size)
	{
		FIMEMORY* fiMemory = FreeImage_OpenMemory(&data[0], size);
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(fiMemory);
		if(fif == FIF_UNKNOWN)
		{
			DRE_EXCEPT(DRE_EXCEPTION_INTERNAL_ERROR, "���ܴ��������м���ͼƬ",
				"FreeImageLoader::Loader");
		}

		FIBITMAP* fiBitmap = FreeImage_LoadFromMemory(fif, fiMemory);
		if(fiBitmap == nullptr)
		{
			DRE_EXCEPT(DRE_EXCEPTION_INTERNAL_ERROR, "���ܴ��������м���ͼƬ",
					"FreeImageLoader::Loader");
		}

		DRE_PIXEL_FORMAT imageFormat = DRE_PIXEL_FORMAT_UNKNOWN;
		u32 bpp = FreeImage_GetBPP(fiBitmap);
		FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(fiBitmap);
		FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(fiBitmap);

		switch (imageType)
		{
		case FIT_UNKNOWN:
		case FIT_UINT32:
		case FIT_INT32:
		case FIT_FLOAT:
		case FIT_DOUBLE:
		case FIT_COMPLEX:
		case FIT_RGBF:
		case FIT_RGBAF:
		default:
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "���ܴ��������м���ͼƬ",
				"FreeImageLoader::Load")
			break;

		// ��׼λͼ
		case FIT_BITMAP:
			{
				
				// ����Ƿ�Ҷ�ͼ
				if (colorType == FIC_MINISWHITE || colorType == FIC_MINISBLACK)
				{
					// ת���Ҷ�ͼ
					FIBITMAP* newBitmap = FreeImage_ConvertToGreyscale(fiBitmap);
					FreeImage_Unload(fiBitmap);
					fiBitmap = newBitmap;
					bpp = FreeImage_GetBPP(fiBitmap);
				}
				// ����Ƿ��ɫ��λͼ��CMYKλͼ
				else if (bpp < 8 || colorType == FIC_PALETTE || colorType == FIC_CMYK)
				{
					FIBITMAP* newBitmap =  NULL;	
					// ���λͼ�Ƿ��͸��ͨ��
					if (FreeImage_IsTransparent(fiBitmap))
					{
						newBitmap = FreeImage_ConvertTo32Bits(fiBitmap);
					}
					else
					{
						newBitmap = FreeImage_ConvertTo24Bits(fiBitmap);
					}

					FreeImage_Unload(fiBitmap);
					fiBitmap = newBitmap;
					bpp = FreeImage_GetBPP(fiBitmap);
				}

				switch (bpp)
				{
				case 8:
					imageFormat = DRE_PIXEL_FORMAT_L_8;
					break;
				case 16:
					if(FreeImage_GetGreenMask(fiBitmap) == FI16_565_GREEN_MASK)
					{
						imageFormat = DRE_PIXEL_FORMAT_R5G6B5;
					}
					else
					{
						imageFormat = DRE_PIXEL_FORMAT_A1R5G5B5;
					}
					break;
				case 24:
					// ��FreeImage�Ƿ�ʹ��big endian
#					if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
						imageFormat = DRE_PIXEL_FORMAT_R8G8B8;
#					else
						imageFormat = DRE_PIXEL_FORMAT_B8G8R8;
#					endif
					break;
				case 32:
					// ��FreeImage�Ƿ�ʹ��big endian
#					if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
						imageFormat = DRE_PIXEL_FORMAT_R8G8B8A8;
#					else
						imageFormat = DRE_PIXEL_FORMAT_A8B8G8R8;
#					endif
					break;

				default:
					break;
				}
			}
			break;
		case FIT_RGB16:
			imageFormat = DRE_PIXEL_FORMAT_R5G6B5;
			break;
		case FIT_RGBA16:
			imageFormat = DRE_PIXEL_FORMAT_R5G5B5A1;
			break;
		case FIT_UINT16:
			imageFormat = DRE_PIXEL_FORMAT_L_16;
			break;
		case FIT_INT16:
			imageFormat = DRE_PIXEL_FORMAT_L_16;
			break;
		}	// end switch

		u32 imageWidth = FreeImage_GetWidth(fiBitmap);
		u32 imageHeight = FreeImage_GetHeight(fiBitmap);
		
		return ImagePtr(new FreeImage(fiBitmap, imageWidth, imageHeight, imageFormat));
	}

	FIBITMAP* FreeImageLoader::Encode(ImagePtr image)
	{
		FREE_IMAGE_TYPE imageType = FIT_UNKNOWN;
		u32 imageBpp = 0;
		DRE_PIXEL_FORMAT transframFormat = DRE_PIXEL_FORMAT_UNKNOWN;

		switch (image->GetPixelFormat())
		{
		//------------------------------ֱ�Ӷ�ӦFREE_IMAGE_TYPE�����ظ�ʽ-------------------------------//
		
		// ��ӦFIT_BITMAP��bpp = 8
		case DRE_PIXEL_FORMAT_L_8:
			transframFormat = DRE_PIXEL_FORMAT_L_8;
			imageType = FIT_BITMAP;
			break;

		case DRE_PIXEL_FORMAT_A_8:
			transframFormat = DRE_PIXEL_FORMAT_A_8;
			imageType = FIT_BITMAP;
			break;

		// ��ӦFIT_BITAMP, bpp = 16
		case DRE_PIXEL_FORMAT_A1R5G5B5:
			transframFormat = DRE_PIXEL_FORMAT_A1R5G5B5;
			imageType = FIT_BITMAP;
			break;

		// ��ӦFIT_BITAMP, bpp = 24
#		if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
		case DRE_PIXEL_FORMAT_R8G8B8:
		case DRE_PIXEL_FORMAT_B8G8R8:
			transframFormat = DRE_PIXEL_FORMAT_R8G8B8;
			imageType = FIT_BITMAP;
			break;
#		else
		case DRE_PIXEL_FORMAT_R8G8B8:
		case DRE_PIXEL_FORMAT_B8G8R8:
			transframFormat = DRE_PIXEL_FORMAT_B8G8R8;
			imageType = FIT_BITMAP;
			break;
#		endif

		// ��ӦFIT_BITAMP, bpp = 32
#		if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
		case DRE_PIXEL_FORMAT_R8G8B8A8:
		case DRE_PIXEL_FORMAT_B8G8R8A8:
		case DRE_PIXEL_FORMAT_A8R8G8B8:
		case DRE_PIXEL_FORMAT_A8B8G8R8:	
			transframFormat = DRE_PIXEL_FORMAT_R8G8B8A8;
			imageType = FIT_BITMAP;
			break;
#		else
		case DRE_PIXEL_FORMAT_R8G8B8A8:
		case DRE_PIXEL_FORMAT_B8G8R8A8:
		case DRE_PIXEL_FORMAT_A8R8G8B8:
		case DRE_PIXEL_FORMAT_A8B8G8R8:		
			transframFormat = DRE_PIXEL_FORMAT_A8B8G8R8;
			imageType = FIT_BITMAP;
			break;
#		endif

		// ��ӦFIT_RGB16
		case DRE_PIXEL_FORMAT_R5G6B5:
			transframFormat = DRE_PIXEL_FORMAT_R5G6B5;
			imageType = FIT_RGB16;
			break;

		// ��ӦFIT_RGBA16
		case DRE_PIXEL_FORMAT_R5G5B5A1:
			transframFormat = DRE_PIXEL_FORMAT_R5G5B5A1;
			imageType = FIT_RGBA16;
			break;

		// ��ӦFIT_UINT16
		case DRE_PIXEL_FORMAT_L_16:
			transframFormat = DRE_PIXEL_FORMAT_L_16;
			imageType = FIT_UINT16;
			break;

		//------------------------------����ֱ�Ӷ�ӦFREE_IMAGE_TYPE�����ظ�ʽ-------------------------------//

		//-----------------------------------------����ת��������-------------------------------------------//
		case DRE_PIXEL_FORMAT_UNKNOWN:
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "����ת��ͼƬ��FreeImage��ʽ����", "FreeImageLoader::Encode");
			break;
		}

		if (!FreeImage_FIFSupportsExportType(mFIF, imageType) || 
			!FreeImage_FIFSupportsExportBPP(mFIF, PixelUtil::GetPixelFormatBpp(transframFormat)))
		{
			DRE_EXCEPT(DRE_EXCEPTION_INTERNAL_ERROR, "����ת��ͼƬ��FreeImage��ʽ����", "FreeImageLoader::Encode");
		}

		FIBITMAP* ret = FreeImage_AllocateT(
			imageType, 
			static_cast<int>(image->GetWidth()), 
			static_cast<int>(image->GetHeight()), 
			static_cast<int>(PixelUtil::GetPixelFormatBpp(transframFormat)));

		if(transframFormat == DRE_PIXEL_FORMAT_A_8 ||
			transframFormat == DRE_PIXEL_FORMAT_L_8)
		{
			FIBITMAP* temp = ret;
			ret = FreeImage_ConvertToGreyscale(ret);
			FreeImage_Unload(temp);
		}

		// ת��ͼƬ����
		PixelUtil::Convert(
			image->GetDataPtr(),
			image->GetPixelFormat(),
			image->GetPixelNums(),
			FreeImage_GetBits(ret), 
			transframFormat);

		return ret;
	}

	u32 FreeImageLoader::Save_Impl(ImagePtr image, const char* file)
	{
		FreeImage_Save(mFIF, Encode(image), file);
		return 0;
	}

	void FreeImageLoader::StartUp()
	{
		// ��ʼ��FreeImage
		FreeImage_Initialise(false);

		for(int i = 0; i < FreeImage_GetFIFCount(); ++ i)
		{
			string exts(FreeImage_GetFIFExtensionList((FREE_IMAGE_FORMAT)i));

			// ע�������
			ImageLoader::RegisterImageLoader(exts, ImageLoaderPtr(new FreeImageLoader((FREE_IMAGE_FORMAT)i)));
		}
	}

	void FreeImageLoader::ShutDown()
	{
		for(int i = 0; i < FreeImage_GetFIFCount(); ++ i)
		{
			string exts(FreeImage_GetFIFExtensionList((FREE_IMAGE_FORMAT)i));

			// ж�ؼ�����
			ImageLoader::UnregisterImageLoader(exts);
		}

		// ж��FreeImage
		FreeImage_DeInitialise();
	}

}	// end namespace dream