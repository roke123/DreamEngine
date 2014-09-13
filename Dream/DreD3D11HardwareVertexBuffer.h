#ifndef __DRED3D11HARDWAREVERTEXBUFFER_H__
#define __DRED3D11HARDWAREVERTEXBUFFER_H__

#include "DreD3D11RenderDeclaration.h"
#include "DreHardwareVertexBuffer.h"

namespace dream
{

	class D3D11HardwareVertexBuffer final : public HardwareVertexBuffer 
	{
		friend class D3D11RenderSystem;
	private:
		/** 构造函数
		*/
		D3D11HardwareVertexBuffer(
			ID3D11BufferPtr vertexBuffer, ID3D11DevicePtr d3d11Device,
			u32 vertexSize, u32 numVertices,
			DRE_PRIMITIVE_TOPOLOGY vertexType, 
			DRE_BUFFER_USAGE usage,
			bool haSinstanceData = false, u32 instanceDataStepRate = 0) throw();
	public:
		/** 虚析构函数
		*/
		~D3D11HardwareVertexBuffer();

		/** 获取对应的D3D11的实体
		*/
		ID3D11BufferPtr GetVertexBuffer() { return mVertexBuffer; };

	private:
		/** 锁定缓冲区的实现方法
		* @param offset 锁定缓冲区的开始端偏移
		* @param length 锁定缓冲区长度
		* @param options 锁定缓冲区方式
		*/
		void * LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS options) override;

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
		/// D3D11顶点缓冲
		ID3D11BufferPtr					mVertexBuffer;
		/// D3D11顶点的影子缓冲
		ID3D11BufferPtr					mVertexShadowBuffer;
		/// D3D11顶点设备
		ID3D11DevicePtr					mD3D11Device;
		/// D3D11顶点设备内容
		ID3D11DeviceContextPtr			mD3D11Context;
		/// 映射到CPU数据
		D3D11_MAPPED_SUBRESOURCE		mSubResource;
		/// 当前锁定选项
		DRE_LOCK_OPTIONS				mLockOption;
	};	// end class D3D11HardwareVertexBuffer

};	// end namespace dream 

#endif	// end __DRED3D11HARDWAREVERTEXBUFFER_H__