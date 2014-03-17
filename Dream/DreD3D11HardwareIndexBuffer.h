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
		/** ���캯��
		*/
		D3D11HardwareIndexBuffer(
			ID3D11BufferPtr indexBuffer, ID3D11DevicePtr d3dDevice,
			DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage);

	public:
		/** ��������
		*/
		~D3D11HardwareIndexBuffer();

		/** ��ȡ��Ӧ��D3D11��ʵ��
		*/
		ID3D11BufferPtr GetIndexBuffer() { mIndexBuffer->AddRef(); return mIndexBuffer; }

	private:

		/** ������������ʵ�ַ���
		* @param offset �����������Ŀ�ʼ��ƫ��
		* @param length ��������������
		* @param options ������������ʽ
		*/
		void* LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS options) override;

		/** ����ͨ��lockImpl�����Ļ�����
		*/
		void UnlockImpl(void) override;

		/** �Ѷ��㻺�������ݸ��Ƶ�Ӱ�ӻ�����
		* @remark	��ΪD3D11_USAGE_DEFAULT��D3D11_USAGE_DYNAM
		*			IC�Ļ������в��ֶ�д��������ֱ����ɣ�����ͨ
		*			��һ����ӵ�Ӱ�ӻ��������
		*/
		void CopyToShadowResource();

	private:
		/// D3D11��������
		ID3D11BufferPtr mIndexBuffer;
		/// D3D11�����Ӱ�ӻ���
		ID3D11BufferPtr mIndexShadowBuffer;
		/// D3D11��Ⱦ�豸
		ID3D11DevicePtr mD3D11Device;
		/// D3D11��Ⱦ�豸����
		ID3D11DeviceContextPtr mD3D11Context;
		/// ӳ�䵽CPU����
		D3D11_MAPPED_SUBRESOURCE mSubResource;
		// ��ǰ����ѡ��
		DRE_LOCK_OPTIONS mLockOption;

	};	// end class D3D11HardwareIndexBuffer

}	// end namespace dream

#endif	// end __DRED3D11HARDWAREINDEXBUFFER_H__