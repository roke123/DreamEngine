#include "DreImageLoader.h"

#include "DreFreeImageLoader.h"

namespace dream
{

	map<string, ImageLoaderPtr> ImageLoader::sImageLoaderMap;

	/** �����ļ�������ͼƬ
	*/
	ImagePtr ImageLoader::Load(const char* file)
	{
		return Load(string(file));
	}

	/** �����ļ�������ͼƬ
	*/
	ImagePtr ImageLoader::Load(const string& file)
	{
		// ȡ����չ��
		string ext = file.substr(file.find_last_of('.') + 1, file.length());

		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		if((ite = sImageLoaderMap.find(ext)) == sImageLoaderMap.end())
		{
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, string("�Ҳ���").append(file).append("��ͼƬ������"),
				"ImageLoader::Load");
		}

		ImageLoaderPtr loader = ite->second;
		return loader->Load_Impl(file.c_str());
	}

	/** ���ڴ�������ͼƬ
	* @param	data		���ݻ�����
	* @param	sizeInbyte	���ݻ���������
	*/
	ImagePtr ImageLoader::Load(u8Array data, u32 sizeInByte)
	{
		ImagePtr ret = nullptr;

		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		// �������м�����
		while (ret == nullptr && ite != sImageLoaderMap.end())
		{
			try {
				ret = ite->second->Load(data, sizeInByte);
			}
			// ��׽�����쳣
			catch (...) {
				// �����д���
			}

			++ ite;
		}

		if (ret == nullptr)
		{
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "�޶�Ӧ��ͼƬ���ݼ�����",
				"ImageLoader::Loader");
		}

		return ret;
	}

	/** ����ͼƬ���ļ���
	* @param	image		ͼƬָ��
	* @param	file		�ļ���
	* @remark ���ر���󳤶�
	*/
	u32 ImageLoader::Save(ImagePtr image, const char* file)
	{
		return Save(image, string(file));
	}

	/** ����ͼƬ���ļ���
	* @param	image		ͼƬָ��
	* @param	file		�ļ���
	* @remark ���ر���󳤶�
	*/
	u32 ImageLoader::Save(ImagePtr image, const string& file)
	{
		// ȡ����չ��
		string ext = file.substr(file.find_last_of('.') + 1, file.length());

		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		if((ite = sImageLoaderMap.find(ext)) == sImageLoaderMap.end())
		{
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, string("�Ҳ���").append(file).append("��ͼƬ������"),
				"ImageLoader::Load");
		}

		ImageLoaderPtr loader = ite->second;
		return loader->Save_Impl(image, file.c_str());
	}

	/** Load��ʵ��
	*/
	ImagePtr ImageLoader::Load_Impl(const char* file)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "�޶�Ӧʵ��", 
			"ImageLoader::Load_Impl");
	}

	/** Load��ʵ��
	* @param	data		���ݻ�����
	* @param	sizeInbyte	���ݻ���������
	*/
	ImagePtr ImageLoader::Load_Impl(u8Array data, u32 sizeInByte)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "�޶�Ӧʵ��", 
			"ImageLoader::Load_Impl");
	}

	/** Save��ʵ��
	* @param	image		ͼƬָ��
	* @param	file		�ļ���
	* @remark ���ر���󳤶�
	*/
	u32 ImageLoader::Save_Impl(ImagePtr image, const char* file)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "�޶�Ӧʵ��", 
			"ImageLoader::Load_Impl");
	}

	/** ע��ĳһͼƬ����չ������ImageLoader
	*/
	bool ImageLoader::RegisterImageLoader(const string& ext, ImageLoaderPtr loader)
	{
		if(sImageLoaderMap.find(ext) == sImageLoaderMap.end())
		{
			sImageLoaderMap.insert(stlport::make_pair(ext, loader));
			return true;
		}

		return false;
	}

	/** ע��ĳһͼƬ����չ������ImageLoader
	*/
	bool ImageLoader::UnregisterImageLoader(const string& ext)
	{
		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		if((ite = sImageLoaderMap.find(ext)) != sImageLoaderMap.end())
		{
			sImageLoaderMap.erase(ite);
			return true;
		}

		return false;
	}

	/** ����Ƿ���ע��ĳͼƬ���͵�ImageLoader
	*/
	bool ImageLoader::IsRegisterImageLoader(const string& ext)
	{
		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		if((ite = sImageLoaderMap.find(ext)) != sImageLoaderMap.end())
		{
			return true;
		}

		return false;
	}

	/** ����ĳһ��չ����ȡImageLoader
	*/
	ImageLoaderPtr ImageLoader::GetImageLoaderFromExt(const string& ext)
	{
		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		if((ite = sImageLoaderMap.find(ext)) != sImageLoaderMap.end())
		{
			return ite->second;
		}

		return nullptr;
	}

	/** ��װImageLoader
	*/
	void ImageLoader::StartUp()
	{
		FreeImageLoader::StartUp();
	}

	/** ж��ImageLoader
	*/
	void ImageLoader::ShutDown()
	{
		FreeImageLoader::ShutDown();
	}

	/** ��ʵ������
	*/
	ImageLoader& ImageLoader::GetInstance()
	{
		static ImageLoader instance;
		return instance;
	}

}