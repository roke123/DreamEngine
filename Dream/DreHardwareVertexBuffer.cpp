#include "DreD3D11HardwareVertexBuffer.h"

#include "DreD3D11RenderMapping.h"

namespace dream
{
        
	VertexElement MakeVertexElemnt(DRE_VERTEX_ELEMENT_TYPE type, DRE_VERTEX_EMELENT_SEMANTICS semantics,
		u8 index, u8 size)
	{
		VertexElement temp = {type, semantics, size, index};
		// 右值引用取消消耗
		return temp;
	}

	/** 获取一个只读的顶点元素列表
	*/
    const VertexDeclaration& HardwareVertexBuffer::GetVertexDeclaration(void) const
	{
		return mElementList;
	}

	/** 获取一个只读的顶点元素列表
	*/
	VertexDeclaration& HardwareVertexBuffer::GetVertexDeclaration(void)
	{
		return mElementList;
	}

    /** 为顶点描述增加一个元素
    */
	void HardwareVertexBuffer::AddElement(const VertexElement& element)
	{
		mElementList.push_back(element);
	}

    /** 移除拥有某个语义的顶点元素
	* @param semantics 顶点元素语义
	* @param index 可选，默认为0，表示顶点元素语义索引
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

	/** 移除顶点描述中的所有元素
	*/
	void HardwareVertexBuffer::RemoveAllElements(void)
	{
		mElementList.clear();
	}

	/** 从顶点描述中寻找拥有某个语义的顶点元素
	* @param semantics	顶点元素语义
	* @param index		可选，默认为0，表示顶点元素语义索引
	*
	* @return			返回一个只读的顶点元素引用
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