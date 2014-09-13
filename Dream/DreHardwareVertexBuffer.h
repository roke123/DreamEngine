#ifndef __DREHARDWAREVERTEXBUFFER_H__
#define __DREHARDWAREVERTEXBUFFER_H__

#include "DreRenderDeclaration.h"

#include "DreHardwareBuffer.h"

namespace dream {
	
	struct VertexElement
    {
        /// Ԫ������
        DRE_VERTEX_ELEMENT_TYPE mType;
        /// Ԫ������
        DRE_VERTEX_EMELENT_SEMANTICS mSemantic;
		/// Ԫ�س���
		u8 mSizeInByte;
        /// ���ظ������Ԫ�ص�����
        u8 mIndex;
    };	// end class VertexElement

	VertexElement DRE_EXPORT_CLASS MakeVertexElemnt(DRE_VERTEX_ELEMENT_TYPE, DRE_VERTEX_EMELENT_SEMANTICS,
		u8, u8);

	class DRE_EXPORT_CLASS HardwareVertexBuffer : public HardwareBuffer
    {
	private:
		/// ��������
		VertexDeclaration mElementList;
		/// ��������
		u32 mNumVertices;
		/// ���㳤��
		u32 mVertexSize;
		/// ʵ�����ݵļ���ʣ�ֻ��mInstanceDataΪtrueʱ��Ч
		u32 mInstanceDataStepRate;
		/// �Ƿ�ʵ������
		bool mISinstanceData;
		/// ��������
		DRE_PRIMITIVE_TOPOLOGY mPrimitiveTopology;

	public:
		HardwareVertexBuffer(u32 vertexSize, u32 numVertices, DRE_BUFFER_USAGE usage,
			DRE_PRIMITIVE_TOPOLOGY vertexType, bool haSinstanceData = false, u32 instanceDataStepRate = 0) :
		HardwareBuffer(vertexSize * numVertices, usage),
			mVertexSize(vertexSize), mNumVertices(numVertices),
			mPrimitiveTopology(vertexType),
			mISinstanceData(haSinstanceData), mInstanceDataStepRate(instanceDataStepRate)
		{
			// ����
		}

	private:
		HardwareVertexBuffer(const HardwareVertexBuffer&);
		HardwareVertexBuffer& operator = (const HardwareVertexBuffer&);
		    
	public:
		virtual ~HardwareVertexBuffer() {};

		
        /** ȡ�ö���Ԫ������
		*/
        u32 GetElementCount(void) const { return mElementList.size(); }
        
		/** ��ȡһ��ֻ���Ķ���Ԫ���б�
		*/
        const VertexDeclaration& GetVertexDeclaration(void) const;
	
		/** ��ȡһ��ֻ���Ķ���Ԫ���б�
		*/
        VertexDeclaration& GetVertexDeclaration(void);

        /** Ϊ������������һ��Ԫ��
        */
		void AddElement(const VertexElement& element);

        /** �Ƴ�ӵ��ĳ������Ķ���Ԫ��
		* @param semantics ����Ԫ������
		* @param index ��ѡ��Ĭ��Ϊ0����ʾ����Ԫ����������
		*/
        void RemoveElement(DRE_VERTEX_EMELENT_SEMANTICS semantics, u32 index = 0);

		/** �Ƴ����������е�����Ԫ��
		*/
		void RemoveAllElements(void);

		/** �Ӷ���������Ѱ��ӵ��ĳ������Ķ���Ԫ��
		* @param semantics	����Ԫ������
		* @param index		��ѡ��Ĭ��Ϊ0����ʾ����Ԫ����������
		*
		* @return			����һ��ֻ���Ķ���Ԫ������
		*/
		const VertexElement& FindElement(DRE_VERTEX_EMELENT_SEMANTICS semantics, u32 index = 0) const;

		/** ȡ�ö����С
		*/
		u32 GetVertexSize(void) const { return mVertexSize; }
		/** ȡ�ö�������
		*/
		u32 GetNumVertices(void) const { return mNumVertices; }
		/** �����Ƿ�ʵ������
		*/
		bool GetISinstanceData() const { return mISinstanceData; }
		/** ʵ�����ݵļ����
		*/
		u32 GetInstanceDataStepRate() const 
		{ 
			DreAssert(!mISinstanceData, "�˶��㻺��������ʵ������");
			return mInstanceDataStepRate;
		}
		/** ȡ�ö�������
		*/
		const DRE_PRIMITIVE_TOPOLOGY GetVertexType() const
		{
			return mPrimitiveTopology;
		}
    };

}	// end namespace dream

#endif	// end __DREHARDWAREVERTEXBUFFER_H__

