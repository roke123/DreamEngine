#include "DreD3D11HardwareVertexBuffer.h"

#include "DreD3D11RenderMapping.h"

namespace dream
{
        
	VertexElement MakeVertexElemnt(DRE_VERTEX_ELEMENT_TYPE type, DRE_VERTEX_EMELENT_SEMANTICS semantics,
		u8 index, u8 size)
	{
		VertexElement temp = {type, semantics, size, index};
		// ��ֵ����ȡ������
		return temp;
	}

	/** ��ȡһ��ֻ���Ķ���Ԫ���б�
	*/
    const VertexDeclaration& HardwareVertexBuffer::GetVertexDeclaration(void) const
	{
		return mElementList;
	}

	/** ��ȡһ��ֻ���Ķ���Ԫ���б�
	*/
	VertexDeclaration& HardwareVertexBuffer::GetVertexDeclaration(void)
	{
		return mElementList;
	}

    /** Ϊ������������һ��Ԫ��
    */
	void HardwareVertexBuffer::AddElement(const VertexElement& element)
	{
		mElementList.push_back(element);
	}

    /** �Ƴ�ӵ��ĳ������Ķ���Ԫ��
	* @param semantics ����Ԫ������
	* @param index ��ѡ��Ĭ��Ϊ0����ʾ����Ԫ����������
	*/
	void HardwareVertexBuffer::RemoveElement(DRE_VERTEX_EMELENT_SEMANTICS semantics, u32 index /* = 0 */)
	{
		VertexElementIterator ite = mElementList.begin();

		for(; ite != mElementList.end(); ++ ite)
		{
			if(ite->mSemantic == semantics && ite->mIndex == index)
			{
				mElementList.erase(ite);
				break;
			}
		}
	}

	/** �Ƴ����������е�����Ԫ��
	*/
	void HardwareVertexBuffer::RemoveAllElements(void)
	{
		mElementList.clear();
	}

	/** �Ӷ���������Ѱ��ӵ��ĳ������Ķ���Ԫ��
	* @param semantics	����Ԫ������
	* @param index		��ѡ��Ĭ��Ϊ0����ʾ����Ԫ����������
	*
	* @return			����һ��ֻ���Ķ���Ԫ������
	*/
	const VertexElement& HardwareVertexBuffer::FindElement(
		DRE_VERTEX_EMELENT_SEMANTICS semantics, u32 index /* = 0 */) const
	{
		VertexElementConstIterator ite = mElementList.begin();

		for(; ite != mElementList.end(); ++ ite)
		{
			if(ite->mSemantic == semantics && ite->mIndex == index)
				break;
		}

		return *ite;
	}

}	// end namespace dream