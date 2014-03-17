#ifndef __DREHAREWAREBUFFER_H__
#define __DREHAREWAREBUFFER_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	class DRE_EXPORT_CLASS HardwareBuffer
    {
	private:
		/// 以字节为单位的长度
		u32 mSizeInBytes;
		/// 缓冲区的使用方式
		DRE_BUFFER_USAGE mUsage;
		/// 被锁定缓冲区的开始端偏移
		u32 mLockStart;
		/// 被锁定缓冲区长度
		u32 mLockSize;
    	/// 缓冲区内存当前是否被锁定
		bool mIsLocked;

	protected:
		/** 锁定缓冲区的实现方法
		* @param offset 锁定缓冲区的开始端偏移
		* @param length 锁定缓冲区长度
		* @param options 锁定缓冲区方式
		*/
		virtual void * LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS options) = 0;

		/** 解锁通过lockImpl锁定的缓冲区
		*/
		virtual void UnlockImpl(void) = 0;

	public:
		/// 构造函数
		HardwareBuffer(u32 sizeInBytes, DRE_BUFFER_USAGE usage)
			: mSizeInBytes(sizeInBytes), mUsage(usage), mIsLocked(false)
		{
			/// 留空
		}

	private:
		HardwareBuffer(const HardwareBuffer&);
		HardwareBuffer& operator = (const HardwareBuffer&);
		    
	public:

		/// 虚析构函数
		virtual ~HardwareBuffer() {}

		/** 锁定缓冲区方法
		* @param offset 锁定缓冲区的开始端偏移
		* @param length 锁定缓冲区长度
		* @param options 锁定缓冲区方式
		* @note 内部转向调用LockImpl
		*/
		void* Lock(size_t offset, size_t length, DRE_LOCK_OPTIONS options)
		{
			DreAssert(!IsLocked(), "锁定当前缓冲区，当前缓冲区已被锁定");

			void* ret = NULL;
			if ((length + offset) > mSizeInBytes)
			{
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_PARAMS, "锁定长度超过缓冲区长度",
					"HardwareBuffer::lock");
			}
			else
			{
				// 通过定制的lockImpl方法锁定缓冲区
				ret = LockImpl(offset, length, options);
				mIsLocked = true;
			}

			mLockStart = offset;
			mLockSize = length;

			return ret;
		}

		/** 锁定整个缓冲区
		* @note 相当于lock(0, mSizeInBytes, options)
		*/
		void* Lock(DRE_LOCK_OPTIONS options)
		{
			return this->Lock(0, mSizeInBytes, options);
		}

		/** 释放Lock锁定的内存
		* @note 内部转向调用UnlockImpl
		*/
		void Unlock(void)
		{
			DreAssert(IsLocked(), "不能解锁当前缓冲区，当前缓冲区未被锁定");

			UnlockImpl();
			mIsLocked = false;
		}

		/** 读取数据并把数据复制到pDest中
		* @param offset 读取缓冲区数据的开始位置偏移
		* @param length 读取缓冲区数据大小
		* @param pDest 分配的空间必须大于length
		*/
		void ReadData(u32 offset, u32 length, void* pDest)
		{
			const void* data = this->Lock(offset, length, HDRE_LOCK_READ_ONLY);
			memcpy(pDest, data, length / 2);
			this->Unlock();
		}

		/** 把数据写入缓冲区
		* @param offset 读取缓冲区数据的开始位置偏移
		* @param length 读取缓冲区数据大小
		* @param pDest 分配的空间必须大于length
		* @param discardBuffer 是否抛弃当前缓冲区
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

		/** 复制缓冲区
		* @param srcOffset 源缓冲区数据的开始位置偏移
		* @param dstOffset 目标缓冲区数据的开始位置偏移
		* @param length 复制缓冲区数据大小
		* @param pDest 分配的空间必须大于length
		* @param discardBuffer 是否抛弃当前缓冲区
		*/
		void CopyDataFrom( u32 srcOffset, u32 dstOffset, u32 length,
			HardwareBuffer& srcBuffer, bool discardBuffer = false)
		{
			const void *srcData = srcBuffer.Lock(srcOffset, length, HDRE_LOCK_READ_ONLY);
			this->WriteData(dstOffset, length, srcData, discardBuffer);
			srcBuffer.Unlock();
		}

		/** 复制缓冲区
		*/
		void CopyDataFrom(HardwareBuffer& srcBuffer)
		{
			DreAssert(GetSizeInBytes() != srcBuffer.GetSizeInBytes(),  "缓冲区长度不相等"); 
			this->CopyDataFrom(0, 0, GetSizeInBytes(), srcBuffer, true);
		}

		/** 返回缓冲区长度
		*/
		u32 GetSizeInBytes(void) const { return mSizeInBytes; }

		/** 返回缓冲区使用方式
		*/
		DRE_BUFFER_USAGE GetUsage(void) const { return mUsage; }

		/** 返回缓冲区是否被锁定
		*/
		bool IsLocked(void) const { return mIsLocked; }
	};	// end class DreHarewareBuffer

}

#endif	// end of __DREHARDWAREBUFFER_H__