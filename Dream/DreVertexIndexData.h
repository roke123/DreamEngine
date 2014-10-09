////////////////////////////////////
// author: zou lei 
// date: 2014/10/07 20:21
////////////////////////////////////

#ifndef __DRE_VERTEX_INDEX_DATA_H__
#define __DRE_VERTEX_INDEX_DATA_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{

	/** ��������Ԫ�� */
	struct VertexElement
	{
		DRE_VERTEX_ELEMENT_TYPE			mType;
		DRE_VERTEX_ELEMENT_SEMANTIC		mSemantic;
		u16								mIndex;
		u32								mOffset;
	};

	/** �������� */
	class VertexData
	{
	public:
		/** ���캯��
		* @param	start
		*	�������ݵĿ�ʼλ��
		* @param	offset
		*	�������ݵ�ƫ��ֵ
		* @param	vertexBuf
		*	���õĶ��㻺����
		*/
		explicit VertexData(u32 start, u32 offset, HardwareVertexBufferPtr vertexBuf);

		/** ���һ������Ԫ������
		* @param	sematic
		*	����Ԫ�����壬��Ӧ��shader������������
		* @param	index
		*	����Ԫ��������������Ӧ��shader�������������������� 
		* @param	offset
		*	����Ԫ�ؾ��붥�����ݿ�ʼλ�õ�ƫ����
		* @param	type
		*	����Ԫ�����ݸ�ʽ����
		*/
		void AddElemnet(
			DRE_VERTEX_ELEMENT_SEMANTIC sematic,
			u16 index,
			u32 offset,
			DRE_VERTEX_ELEMENT_TYPE type);

		/** �޸�һ������Ԫ������
		* @param	sematic
		*	����Ԫ�����壬��Ӧ��shader������������
		* @param	index
		*	����Ԫ��������������Ӧ��shader�������������������� 
		* @param	offset
		*	����Ԫ�ؾ��붥�����ݿ�ʼλ�õ�ƫ����
		* @param	type
		*	����Ԫ�����ݸ�ʽ����
		*/
		void ModifyElement(
			DRE_VERTEX_ELEMENT_SEMANTIC sematic,
			u16 index,
			u32 offset,
			DRE_VERTEX_ELEMENT_TYPE type);

		/** ���ݶ���Ԫ��������������ɾ������Ԫ������
		* @param	sematic
		*	����Ԫ������
		* @param	index
		*	����Ԫ������������
		*/
		void RemoveElement(
			DRE_VERTEX_ELEMENT_SEMANTIC sematic,
			u16 index);

		/** ɾ�����ж���Ԫ������ */
		void RemoveAllElemnet();

		/** ȡ�ö���Ԫ��������ʼ������ */
		VertexDeclarationIte begin() { return mVertexDeclaration.begin(); }
		VertexDeclarationConstIte begin() const { return mVertexDeclaration.begin(); }

		/** ȡ�ö���Ԫ�������ս������ */
		VertexDeclarationIte end() { return mVertexDeclaration.end(); }
		VertexDeclarationConstIte end() const { return mVertexDeclaration.end(); }

		/** ȡ�����ݿ�ʼλ�� */
		u32 GetDataStart() const { return mDataStart; }
		void SetDataStart(u32 start) { mDataStart = start; }

		/** ȡ�������ɿ�ʼλ�õ�ƫ�� */
		u32 GetDataOffset() const { return mDataOffset; }
		void SetDataOffset(u32 offset) { mDataOffset = offset; }

		/** ȡ�����õĶ��㻺���� */
		HardwareVertexBufferPtr GetVertexBuffer() const { return mVertexBuffer; }
		void SetVertexBuffer(HardwareVertexBufferPtr& vertexBuf) { mVertexBuffer = vertexBuf; }

	private:
		u32								mDataStart;
		u32								mDataOffset;
		HardwareVertexBufferPtr			mVertexBuffer;
		VertexDeclaration				mVertexDeclaration;
	};

	/** ������������ 
	*/
	class IndexData
	{
	public:
		/** �����������ݹ��캯��
		* @param	start
		*	�������ݵĿ�ʼλ��
		* @param	offset
		*	�������ݵ�ƫ��ֵ
		* @param	indexNuf
		*	���õĶ�������������
		*/
		explicit IndexData(
			u32 start,
			u32 offset,
			HardwareIndexBufferPtr indexBuf);

		/** ȡ�ö���������ʼλ�� */
		u32 GetDataStart() const { return mDataStart; }
		void SetDataStart(u32 start) { mDataStart = start; }

		/** ȡ�ö���������ƫ��ֵ */
		u32 GetDataOffset() const { return mDataOffset; }
		void SetDataOffset(u32 offset) { mDataOffset = offset; }

		/** ȡ�ö��������������õĶ������������� */
		HardwareIndexBufferPtr GetIndexBuffer() const { return mIndexBuffer; }
		void SetIndexBuffer(HardwareIndexBufferPtr indexBuf) { mIndexBuffer = indexBuf; }

		DRE_INDEX_ELEMENT_TYPE GetIndexDataType() const;

	private:
		u32								mDataStart;
		u32								mDataOffset;
		HardwareIndexBufferPtr			mIndexBuffer;
	};

}	// end of namespace dream

#endif	// __DRE_VERTEX_INDEX_DATA_H__