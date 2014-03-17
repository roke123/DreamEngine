#include "DreImageLoader.h"

#include "DreFreeImageLoader.h"

namespace dream
{

	map<string, ImageLoaderPtr> ImageLoader::sImageLoaderMap;

	/** 根据文件名载入图片
	*/
	ImagePtr ImageLoader::Load(const char* file)
	{
		return Load(string(file));
	}

	/** 根据文件名载入图片
	*/
	ImagePtr ImageLoader::Load(const string& file)
	{
		// 取得扩展名
		string ext = file.substr(file.find_last_of('.') + 1, file.length());

		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		if((ite = sImageLoaderMap.find(ext)) == sImageLoaderMap.end())
		{
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, string("找不到").append(file).append("的图片加载器"),
				"ImageLoader::Load");
		}

		ImageLoaderPtr loader = ite->second;
		return loader->Load_Impl(file.c_str());
	}

	/** 从内存中载入图片
	* @param	data		数据缓冲区
	* @param	sizeInbyte	数据缓冲区长度
	*/
	ImagePtr ImageLoader::Load(u8Array data, u32 sizeInByte)
	{
		ImagePtr ret = nullptr;

		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		// 测试所有加载器
		while (ret == nullptr && ite != sImageLoaderMap.end())
		{
			try {
				ret = ite->second->Load(data, sizeInByte);
			}
			// 捕捉所有异常
			catch (...) {
				// 不进行处理
			}

			++ ite;
		}

		if (ret == nullptr)
		{
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "无对应的图片数据加载器",
				"ImageLoader::Loader");
		}

		return ret;
	}

	/** 保存图片到文件中
	* @param	image		图片指针
	* @param	file		文件名
	* @remark 返回编码后长度
	*/
	u32 ImageLoader::Save(ImagePtr image, const char* file)
	{
		return Save(image, string(file));
	}

	/** 保存图片到文件中
	* @param	image		图片指针
	* @param	file		文件名
	* @remark 返回编码后长度
	*/
	u32 ImageLoader::Save(ImagePtr image, const string& file)
	{
		// 取得扩展名
		string ext = file.substr(file.find_last_of('.') + 1, file.length());

		map<string, ImageLoaderPtr>::iterator ite = sImageLoaderMap.begin();
		if((ite = sImageLoaderMap.find(ext)) == sImageLoaderMap.end())
		{
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, string("找不到").append(file).append("的图片加载器"),
				"ImageLoader::Load");
		}

		ImageLoaderPtr loader = ite->second;
		return loader->Save_Impl(image, file.c_str());
	}

	/** Load的实现
	*/
	ImagePtr ImageLoader::Load_Impl(const char* file)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "无对应实现", 
			"ImageLoader::Load_Impl");
	}

	/** Load的实现
	* @param	data		数据缓冲区
	* @param	sizeInbyte	数据缓冲区长度
	*/
	ImagePtr ImageLoader::Load_Impl(u8Array data, u32 sizeInByte)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "无对应实现", 
			"ImageLoader::Load_Impl");
	}

	/** Save的实现
	* @param	image		图片指针
	* @param	file		文件名
	* @remark 返回编码后长度
	*/
	u32 ImageLoader::Save_Impl(ImagePtr image, const char* file)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "无对应实现", 
			"ImageLoader::Load_Impl");
	}

	/** 注册某一图片（扩展名）的ImageLoader
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

	/** 注册某一图片（扩展名）的ImageLoader
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

	/** 检查是否以注册某图片类型的ImageLoader
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

	/** 根据某一扩展名获取ImageLoader
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

	/** 安装ImageLoader
	*/
	void ImageLoader::StartUp()
	{
		FreeImageLoader::StartUp();
	}

	/** 卸载ImageLoader
	*/
	void ImageLoader::ShutDown()
	{
		FreeImageLoader::ShutDown();
	}

	/** 单实例函数
	*/
	ImageLoader& ImageLoader::GetInstance()
	{
		static ImageLoader instance;
		return instance;
	}

}