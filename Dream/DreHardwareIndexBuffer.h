#ifndef __DREHARDWAREINDEXBUFFER_H__
#define __DREHARDWAREINDEXBUFFER_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreHardwareBuffer.h"

namespace dream
{

	class DRE_EXPORT_CLASS HardwareIndexBuffer : public HardwareBuffer
	{
	private:
		/// 索引类型
		DRE_INDEX_ELEMENT_TYPE mIndexType;
		/// 索引数量
		u32 mNumIndices;

	public:
		HardwareIndexBuffer(DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage) :
			HardwareBuffer((u32)type * numIndices, usage),
			mIndexType(type), mNumIndices(numIndices)
		{
			// 留空
		}

	private:
		HardwareIndexBuffer(const HardwareIndexBuffer&);
		HardwareIndexBuffer& operator = (const HardwareIndexBuffer&);
		    
	public:

		DRE_INDEX_ELEMENT_TYPE GetIndexType() const { return mIndexType; }

		u32 GetIndexNum() const { return mNumIndices; }

	};	// end class HardwareIndexBuffer

}	// end namespace dream

#endif	// end namespace __DREHARDWAREINDEXBUFFER_H__