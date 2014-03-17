#ifndef __DRED3D11HARDWAREINDEXBUFFER_H__
#define __DRED3D11HARDWAREINDEXBUFFER_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreHardwareIndexBuffer.h"

namespace dream
{

	class D3D11HardwareIndexBuffer final : public HardwareIndexBuffer
	{
		friend class D3D11RenderSystem;
	private:
		/** 构造函数
		*/
		D3D11HardwareIndexBuffer(
			ID3D11BufferPtr indexBuffer, ID3D11DevicePtr d3dDevice,
			DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage);

	public:
		/** 析构函数
		*/
		~D3D11HardwareIndexBuffer();

		/** 获取对应的D3D11的实体
		*/
		ID3D11BufferPtr GetIndexBuffer() { mIndexBuffer->AddRef(); return mIndexBuffer; }

	private:

		/** 锁定缓冲区的实现方法
		* @param offset 锁定缓冲区的开始端偏移
		* @param length 锁定缓冲区长度
		* @param options 锁定缓冲区方式
		*/
		void* LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS options) override;

		/** 解锁通过lockImpl锁定的缓冲区
		*/
		void UnlockImpl(void) override;

		/** 把顶点缓冲区数据复制到影子缓冲区
		* @remark	因为D3D11_USAGE_DEFAULT与D3D11_USAGE_DYNAM
		*			IC的缓冲区有部分读写操作不能直接完成，必须通
		*			过一个间接的影子缓冲区完成
		*/
		void CopyToShadowResource();

	private:
		/// D3D11索引缓冲
		ID3D11BufferPtr mIndexBuffer;
		/// D3D11顶点的影子缓冲
		ID3D11BufferPtr mIndexShadowBuffer;
		/// D3D11渲染设备
		ID3D11DevicePtr mD3D11Device;
		/// D3D11渲染设备内容
		ID3D11DeviceContextPtr mD3D11Context;
		/// 映射到CPU数据
		D3D11_MAPPED_SUBRESOURCE mSubResource;
		// 当前锁定选项
		DRE_LOCK_OPTIONS mLockOption;

	};	// end class D3D11HardwareIndexBuffer

}	// end namespace dream

#endif	// end __DRED3D11HARDWAREINDEXBUFFER_H__