#ifndef __DREIMAGELOADER_H__
#define __DREIMAGELOADER_H__

#include "DreIOSystemDeclaration.h"

namespace dream
{
	/** 用于加载图片
	*/
	class DRE_EXPORT_CLASS ImageLoader
	{
	public:
		/** 虚析构函数
		*/
		virtual ~ImageLoader() {}

		/** 根据文件名载入图片
		*/
		ImagePtr Load(const char* file);

		/** 根据文件名载入图片
		*/
		ImagePtr Load(const string& file);

		/** 从内存中载入图片
		* @param	data		数据缓冲区
		* @param	sizeInbyte	数据缓冲区长度
		*/
		ImagePtr Load(u8Array data, u32 sizeInByte);

		/** 保存图片到文件中
		* @param	image		图片指针
		* @param	file		文件名
		* @remark 返回编码后长度
		*/
		u32 Save(ImagePtr image, const char* file);

		/** 保存图片到文件中
		* @param	image		图片指针
		* @param	file		文件名
		* @remark 返回编码后长度
		*/
		u32 Save(ImagePtr image, const string& file);

	protected:
		/** Load的实现
		*/
		virtual ImagePtr Load_Impl(const char* file);

		/** Load的实现
		* @param	data		数据缓冲区
		* @param	sizeInbyte	数据缓冲区长度
		*/
		virtual ImagePtr Load_Impl(u8Array data, u32 sizeInByte);

		/** Save的实现
		* @param	image		图片指针
		* @param	file		文件名
		* @remark 返回编码后长度
		*/
		virtual u32 Save_Impl(ImagePtr image, const char* file);

	public:
		/** 注册某一图片（扩展名）的ImageLoader
		*/
		static bool RegisterImageLoader(const string& ext, ImageLoaderPtr loader);

		/** 注册某一图片（扩展名）的ImageLoader
		*/
		static bool UnregisterImageLoader(const string& ext);

		/** 检查是否以注册某图片类型的ImageLoader
		*/
		static bool IsRegisterImageLoader(const string& ext);

		/** 根据某一扩展名获取ImageLoader
		*/
		static ImageLoaderPtr GetImageLoaderFromExt(const string& ext);

		/** 安装ImageLoader
		*/
		static void StartUp();

		/** 卸载ImageLoader
		*/
		static void ShutDown();

		/** 单实例函数
		*/
		static ImageLoader& GetInstance();

	private:
		static map<string, ImageLoaderPtr> sImageLoaderMap;
	};

}	// end namesapce dream

#endif	// end __DREIMAGELOADER_H__