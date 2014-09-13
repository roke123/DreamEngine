#ifndef __DREHARDWAREVERTEXBUFFER_H__
#define __DREHARDWAREVERTEXBUFFER_H__

#include "DreRenderDeclaration.h"

#include "DreHardwareBuffer.h"

namespace dream {
	
	struct VertexElement
    {
        /// 元素类型
        DRE_VERTEX_ELEMENT_TYPE mType;
        /// 元素语义
        DRE_VERTEX_EMELENT_SEMANTICS mSemantic;
		/// 元素长度
		u8 mSizeInByte;
        /// 对重复语义的元素的索引
        u8 mIndex;
    };	// end class VertexElement

	VertexElement DRE_EXPORT_CLASS MakeVertexElemnt(DRE_VERTEX_ELEMENT_TYPE, DRE_VERTEX_EMELENT_SEMANTICS,
		u8, u8);

	class DRE_EXPORT_CLASS HardwareVertexBuffer : public HardwareBuffer
    {
	private:
		/// 顶点描述
		VertexDeclaration mElementList;
		/// 顶点数量
		u32 mNumVertices;
		/// 顶点长度
		u32 mVertexSize;
		/// 实例数据的间隔率，只在mInstanceData为true时有效
		u32 mInstanceDataStepRate;
		/// 是否实例数据
		bool mISinstanceData;
		/// 顶点类型
		DRE_PRIMITIVE_TOPOLOGY mPrimitiveTopology;

	public:
		HardwareVertexBuffer(u32 vertexSize, u32 numVertices, DRE_BUFFER_USAGE usage,
			DRE_PRIMITIVE_TOPOLOGY vertexType, bool haSinstanceData = false, u32 instanceDataStepRate = 0) :
		HardwareBuffer(vertexSize * numVertices, usage),
			mVertexSize(vertexSize), mNumVertices(numVertices),
			mPrimitiveTopology(vertexType),
			mISinstanceData(haSinstanceData), mInstanceDataStepRate(instanceDataStepRate)
		{
			// 留空
		}

	private:
		HardwareVertexBuffer(const HardwareVertexBuffer&);
		HardwareVertexBuffer& operator = (const HardwareVertexBuffer&);
		    
	public:
		virtual ~HardwareVertexBuffer() {};

		
        /** 取得顶点元素数量
		*/
        u32 GetElementCount(void) const { return mElementList.size(); }
        
		/** 获取一个只读的顶点元素列表
		*/
        const VertexDeclaration& GetVertexDeclaration(void) const;
	
		/** 获取一个只读的顶点元素列表
		*/
        VertexDeclaration& GetVertexDeclaration(void);

        /** 为顶点描述增加一个元素
        */
		void AddElement(const VertexElement& element);

        /** 移除拥有某个语义的顶点元素
		* @param semantics 顶点元素语义
		* @param index 可选，默认为0，表示顶点元素语义索引
		*/
        void RemoveElement(DRE_VERTEX_EMELENT_SEMANTICS semantics, u32 index = 0);

		/** 移除顶点描述中的所有元素
		*/
		void RemoveAllElements(void);

		/** 从顶点描述中寻找拥有某个语义的顶点元素
		* @param semantics	顶点元素语义
		* @param index		可选，默认为0，表示顶点元素语义索引
		*
		* @return			返回一个只读的顶点元素引用
		*/
		const VertexElement& FindElement(DRE_VERTEX_EMELENT_SEMANTICS semantics, u32 index = 0) const;

		/** 取得顶点大小
		*/
		u32 GetVertexSize(void) const { return mVertexSize; }
		/** 取得顶点数量
		*/
		u32 GetNumVertices(void) const { return mNumVertices; }
		/** 返回是否实例数据
		*/
		bool GetISinstanceData() const { return mISinstanceData; }
		/** 实例数据的间隔率
		*/
		u32 GetInstanceDataStepRate() const 
		{ 
			DreAssert(!mISinstanceData, "此顶点缓冲区不是实例数据");
			return mInstanceDataStepRate;
		}
		/** 取得顶点类型
		*/
		const DRE_PRIMITIVE_TOPOLOGY GetVertexType() const
		{
			return mPrimitiveTopology;
		}
    };

}	// end namespace dream

#endif	// end __DREHARDWAREVERTEXBUFFER_H__

