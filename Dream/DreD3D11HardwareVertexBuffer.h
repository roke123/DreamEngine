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
		/** ���캯��
		*/
		D3D11HardwareVertexBuffer(
			ID3D11BufferPtr vertexBuffer, ID3D11DevicePtr d3d11Device,
			u32 vertexSize, u32 numVertices,
			DRE_PRIMITIVE_TOPOLOGY vertexType, 
			DRE_BUFFER_USAGE usage,
			bool haSinstanceData = false, u32 instanceDataStepRate = 0) throw();
	public:
		/** ����������
		*/
		~D3D11HardwareVertexBuffer();

		/** ��ȡ��Ӧ��D3D11��ʵ��
		*/
		ID3D11BufferPtr GetVertexBuffer() { return mVertexBuffer; };

	private:
		/** ������������ʵ�ַ���
		* @param offset �����������Ŀ�ʼ��ƫ��
		* @param length ��������������
		* @param options ������������ʽ
		*/
		void * LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS options) override;

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
		/// D3D11���㻺��
		ID3D11BufferPtr					mVertexBuffer;
		/// D3D11�����Ӱ�ӻ���
		ID3D11BufferPtr					mVertexShadowBuffer;
		/// D3D11�����豸
		ID3D11DevicePtr					mD3D11Device;
		/// D3D11�����豸����
		ID3D11DeviceContextPtr			mD3D11Context;
		/// ӳ�䵽CPU����
		D3D11_MAPPED_SUBRESOURCE		mSubResource;
		/// ��ǰ����ѡ��
		DRE_LOCK_OPTIONS				mLockOption;
	};	// end class D3D11HardwareVertexBuffer

};	// end namespace dream 

#endif	// end __DRED3D11HARDWAREVERTEXBUFFER_H__