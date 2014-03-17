#ifndef __DREIMAGELOADER_H__
#define __DREIMAGELOADER_H__

#include "DreIOSystemDeclaration.h"

namespace dream
{
	/** ���ڼ���ͼƬ
	*/
	class DRE_EXPORT_CLASS ImageLoader
	{
	public:
		/** ����������
		*/
		virtual ~ImageLoader() {}

		/** �����ļ�������ͼƬ
		*/
		ImagePtr Load(const char* file);

		/** �����ļ�������ͼƬ
		*/
		ImagePtr Load(const string& file);

		/** ���ڴ�������ͼƬ
		* @param	data		���ݻ�����
		* @param	sizeInbyte	���ݻ���������
		*/
		ImagePtr Load(u8Array data, u32 sizeInByte);

		/** ����ͼƬ���ļ���
		* @param	image		ͼƬָ��
		* @param	file		�ļ���
		* @remark ���ر���󳤶�
		*/
		u32 Save(ImagePtr image, const char* file);

		/** ����ͼƬ���ļ���
		* @param	image		ͼƬָ��
		* @param	file		�ļ���
		* @remark ���ر���󳤶�
		*/
		u32 Save(ImagePtr image, const string& file);

	protected:
		/** Load��ʵ��
		*/
		virtual ImagePtr Load_Impl(const char* file);

		/** Load��ʵ��
		* @param	data		���ݻ�����
		* @param	sizeInbyte	���ݻ���������
		*/
		virtual ImagePtr Load_Impl(u8Array data, u32 sizeInByte);

		/** Save��ʵ��
		* @param	image		ͼƬָ��
		* @param	file		�ļ���
		* @remark ���ر���󳤶�
		*/
		virtual u32 Save_Impl(ImagePtr image, const char* file);

	public:
		/** ע��ĳһͼƬ����չ������ImageLoader
		*/
		static bool RegisterImageLoader(const string& ext, ImageLoaderPtr loader);

		/** ע��ĳһͼƬ����չ������ImageLoader
		*/
		static bool UnregisterImageLoader(const string& ext);

		/** ����Ƿ���ע��ĳͼƬ���͵�ImageLoader
		*/
		static bool IsRegisterImageLoader(const string& ext);

		/** ����ĳһ��չ����ȡImageLoader
		*/
		static ImageLoaderPtr GetImageLoaderFromExt(const string& ext);

		/** ��װImageLoader
		*/
		static void StartUp();

		/** ж��ImageLoader
		*/
		static void ShutDown();

		/** ��ʵ������
		*/
		static ImageLoader& GetInstance();

	private:
		static map<string, ImageLoaderPtr> sImageLoaderMap;
	};

}	// end namesapce dream

#endif	// end __DREIMAGELOADER_H__