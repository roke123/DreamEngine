#include "DreVertexIndexData.h"

#include "DreHardwareIndexBuffer.h"

namespace dream
{

	DRE_INDEX_ELEMENT_TYPE IndexData::GetIndexDataType() const 
	{
		return mIndexBuffer->GetIndexType();
	}

}	// end of namespace dream