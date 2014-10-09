////////////////////////////////////
// author: zou lei 
// date: 2014/10/07 20:21
////////////////////////////////////

#ifndef __DRE_VERTEX_INDEX_DATA_H__
#define __DRE_VERTEX_INDEX_DATA_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{

	/** 顶点数据元素 */
	struct VertexElement
	{
		DRE_VERTEX_ELEMENT_TYPE			mType;
		DRE_VERTEX_ELEMENT_SEMANTIC		mSemantic;
		u16								mIndex;
		u32								mOffset;
	};

	/** 顶点数据 */
	class VertexData
	{
	public:
		/** 构造函数
		* @param	start
		*	顶点数据的开始位置
		* @param	offset
		*	顶点数据的偏移值
		* @param	vertexBuf
		*	引用的顶点缓冲区
		*/
		explicit VertexData(u32 start, u32 offset, HardwareVertexBufferPtr vertexBuf);

		/** 添加一个顶点元素描述
		* @param	sematic
		*	顶点元素语义，对应于shader中描述的语义
		* @param	index
		*	顶点元素语义索引，对应于shader中描述的语义后的索引号 
		* @param	offset
		*	顶点元素距离顶点数据开始位置的偏移量
		* @param	type
		*	顶点元素数据格式类型
		*/
		void AddElemnet(
			DRE_VERTEX_ELEMENT_SEMANTIC sematic,
			u16 index,
			u32 offset,
			DRE_VERTEX_ELEMENT_TYPE type);

		/** 修改一个顶点元素描述
		* @param	sematic
		*	顶点元素语义，对应于shader中描述的语义
		* @param	index
		*	顶点元素语义索引，对应于shader中描述的语义后的索引号 
		* @param	offset
		*	顶点元素距离顶点数据开始位置的偏移量
		* @param	type
		*	顶点元素数据格式类型
		*/
		void ModifyElement(
			DRE_VERTEX_ELEMENT_SEMANTIC sematic,
			u16 index,
			u32 offset,
			DRE_VERTEX_ELEMENT_TYPE type);

		/** 根据顶点元素语义与索引号删除顶点元素描述
		* @param	sematic
		*	顶点元素语义
		* @param	index
		*	顶点元素语义索引号
		*/
		void RemoveElement(
			DRE_VERTEX_ELEMENT_SEMANTIC sematic,
			u16 index);

		/** 删除所有顶点元素描述 */
		void RemoveAllElemnet();

		/** 取得顶点元素描述初始迭代器 */
		VertexDeclarationIte begin() { return mVertexDeclaration.begin(); }
		VertexDeclarationConstIte begin() const { return mVertexDeclaration.begin(); }

		/** 取得顶点元素描述终结迭代器 */
		VertexDeclarationIte end() { return mVertexDeclaration.end(); }
		VertexDeclarationConstIte end() const { return mVertexDeclaration.end(); }

		/** 取得数据开始位置 */
		u32 GetDataStart() const { return mDataStart; }
		void SetDataStart(u32 start) { mDataStart = start; }

		/** 取得数据由开始位置的偏移 */
		u32 GetDataOffset() const { return mDataOffset; }
		void SetDataOffset(u32 offset) { mDataOffset = offset; }

		/** 取得引用的顶点缓冲区 */
		HardwareVertexBufferPtr GetVertexBuffer() const { return mVertexBuffer; }
		void SetVertexBuffer(HardwareVertexBufferPtr& vertexBuf) { mVertexBuffer = vertexBuf; }

	private:
		u32								mDataStart;
		u32								mDataOffset;
		HardwareVertexBufferPtr			mVertexBuffer;
		VertexDeclaration				mVertexDeclaration;
	};

	/** 顶点索引数据 
	*/
	class IndexData
	{
	public:
		/** 顶点索引数据构造函数
		* @param	start
		*	索引数据的开始位置
		* @param	offset
		*	索引数据的偏移值
		* @param	indexNuf
		*	引用的顶点索引缓冲区
		*/
		explicit IndexData(
			u32 start,
			u32 offset,
			HardwareIndexBufferPtr indexBuf);

		/** 取得顶点索引开始位置 */
		u32 GetDataStart() const { return mDataStart; }
		void SetDataStart(u32 start) { mDataStart = start; }

		/** 取得顶点索引的偏移值 */
		u32 GetDataOffset() const { return mDataOffset; }
		void SetDataOffset(u32 offset) { mDataOffset = offset; }

		/** 取得顶点索引数据引用的顶点索引缓冲区 */
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