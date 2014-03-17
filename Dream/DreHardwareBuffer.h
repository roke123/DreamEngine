#ifndef __DREHAREWAREBUFFER_H__
#define __DREHAREWAREBUFFER_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	class DRE_EXPORT_CLASS HardwareBuffer
    {
	private:
		/// ���ֽ�Ϊ��λ�ĳ���
		u32 mSizeInBytes;
		/// ��������ʹ�÷�ʽ
		DRE_BUFFER_USAGE mUsage;
		/// �������������Ŀ�ʼ��ƫ��
		u32 mLockStart;
		/// ����������������
		u32 mLockSize;
    	/// �������ڴ浱ǰ�Ƿ�����
		bool mIsLocked;

	protected:
		/** ������������ʵ�ַ���
		* @param offset �����������Ŀ�ʼ��ƫ��
		* @param length ��������������
		* @param options ������������ʽ
		*/
		virtual void * LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS options) = 0;

		/** ����ͨ��lockImpl�����Ļ�����
		*/
		virtual void UnlockImpl(void) = 0;

	public:
		/// ���캯��
		HardwareBuffer(u32 sizeInBytes, DRE_BUFFER_USAGE usage)
			: mSizeInBytes(sizeInBytes), mUsage(usage), mIsLocked(false)
		{
			/// ����
		}

	private:
		HardwareBuffer(const HardwareBuffer&);
		HardwareBuffer& operator = (const HardwareBuffer&);
		    
	public:

		/// ����������
		virtual ~HardwareBuffer() {}

		/** ��������������
		* @param offset �����������Ŀ�ʼ��ƫ��
		* @param length ��������������
		* @param options ������������ʽ
		* @note �ڲ�ת�����LockImpl
		*/
		void* Lock(size_t offset, size_t length, DRE_LOCK_OPTIONS options)
		{
			DreAssert(!IsLocked(), "������ǰ����������ǰ�������ѱ�����");

			void* ret = NULL;
			if ((length + offset) > mSizeInBytes)
			{
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "�������ȳ�������������",
					"HardwareBuffer::lock");
			}
			else
			{
				// ͨ�����Ƶ�lockImpl��������������
				ret = LockImpl(offset, length, options);
				mIsLocked = true;
			}

			mLockStart = offset;
			mLockSize = length;

			return ret;
		}

		/** ��������������
		* @note �൱��lock(0, mSizeInBytes, options)
		*/
		void* Lock(DRE_LOCK_OPTIONS options)
		{
			return this->Lock(0, mSizeInBytes, options);
		}

		/** �ͷ�Lock�������ڴ�
		* @note �ڲ�ת�����UnlockImpl
		*/
		void Unlock(void)
		{
			DreAssert(IsLocked(), "���ܽ�����ǰ����������ǰ������δ������");

			UnlockImpl();
			mIsLocked = false;
		}

		/** ��ȡ���ݲ������ݸ��Ƶ�pDest��
		* @param offset ��ȡ���������ݵĿ�ʼλ��ƫ��
		* @param length ��ȡ���������ݴ�С
		* @param pDest ����Ŀռ�������length
		*/
		void ReadData(u32 offset, u32 length, void* pDest)
		{
			const void* data = this->Lock(offset, length, HDRE_LOCK_READ_ONLY);
			memcpy(pDest, data, length / 2);
			this->Unlock();
		}

		/** ������д�뻺����
		* @param offset ��ȡ���������ݵĿ�ʼλ��ƫ��
		* @param length ��ȡ���������ݴ�С
		* @param pDest ����Ŀռ�������length
		* @param discardBuffer �Ƿ�������ǰ������
		*/
		void WriteData(size_t offset, size_t length, const void* pSource, bool discardBuffer = false)
		{
			DRE_LOCK_OPTIONS option = DRE_LOCK_WRITE_ONLY;

			if(discardBuffer)
				option = DRE_LOCK_DISCARD;

			void* data = this->Lock(offset, length, option);
			memcpy(data, pSource, length);
			this->Unlock();
		}

		/** ���ƻ�����
		* @param srcOffset Դ���������ݵĿ�ʼλ��ƫ��
		* @param dstOffset Ŀ�껺�������ݵĿ�ʼλ��ƫ��
		* @param length ���ƻ��������ݴ�С
		* @param pDest ����Ŀռ�������length
		* @param discardBuffer �Ƿ�������ǰ������
		*/
		void CopyDataFrom( u32 srcOffset, u32 dstOffset, u32 length,
			HardwareBuffer& srcBuffer, bool discardBuffer = false)
		{
			const void *srcData = srcBuffer.Lock(srcOffset, length, HDRE_LOCK_READ_ONLY);
			this->WriteData(dstOffset, length, srcData, discardBuffer);
			srcBuffer.Unlock();
		}

		/** ���ƻ�����
		*/
		void CopyDataFrom(HardwareBuffer& srcBuffer)
		{
			DreAssert(GetSizeInBytes() != srcBuffer.GetSizeInBytes(),  "���������Ȳ����"); 
			this->CopyDataFrom(0, 0, GetSizeInBytes(), srcBuffer, true);
		}

		/** ���ػ���������
		*/
		u32 GetSizeInBytes(void) const { return mSizeInBytes; }

		/** ���ػ�����ʹ�÷�ʽ
		*/
		DRE_BUFFER_USAGE GetUsage(void) const { return mUsage; }

		/** ���ػ������Ƿ�����
		*/
		bool IsLocked(void) const { return mIsLocked; }
	};	// end class DreHarewareBuffer

}

#endif	// end of __DREHARDWAREBUFFER_H__