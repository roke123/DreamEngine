#ifndef __DREVISIABLEBOUNDSBOX_H__
#define __DREVISIABLEBOUNDSBOX_H__

#include "DreSceneManagerDeclaration.h"
//------------------ Math --------------------//
#include "Vector3.h"
#include "AABB3.h"
//---------------- IOSystem ------------------//
#include "DreDataBufferFactory.h"
//-------------- SceneManager ----------------//
#include "DreRenderable.h"
//-------------- RenderSystem ----------------//
#include "DreRenderSystem.h"

namespace dream
{

	class VisiableBoundsBox : public Renderable
	{
	public:
		/** 默认构造函数
		*/
		VisiableBoundsBox()
		{
			// 正面
			mIBuffer[0]	 = 0; mIBuffer[1]  = 1; mIBuffer[2]	 = 2;
			mIBuffer[3]	 = 0; mIBuffer[4]  = 2; mIBuffer[5]	 = 3;
			// 左侧面	  									 
			mIBuffer[6]	 = 4; mIBuffer[7]  = 0; mIBuffer[8]	 = 8;
			mIBuffer[9]	 = 8; mIBuffer[10] = 3; mIBuffer[11] = 8;
			// 右侧面	  
			mIBuffer[12] = 1; mIBuffer[13] = 5; mIBuffer[14] = 2;
			mIBuffer[15] = 1; mIBuffer[16] = 6; mIBuffer[17] = 2;
			// 顶面	   
			mIBuffer[18] = 4; mIBuffer[19] = 5; mIBuffer[20] = 0;
			mIBuffer[21] = 4; mIBuffer[22] = 1; mIBuffer[23] = 0;
			// 底面	   
			mIBuffer[24] = 3; mIBuffer[25] = 2; mIBuffer[26] = 2;
			mIBuffer[27] = 3; mIBuffer[28] = 1; mIBuffer[29] = 2;
			// 背面	   
			mIBuffer[30] = 5; mIBuffer[31] = 4; mIBuffer[32] = 8;
			mIBuffer[33] = 5; mIBuffer[34] = 7; mIBuffer[35] = 8;
		}

		void SetBoundsBox(const AABB3& box)
		{
			mVBuffer[0] = box.mMin;
			mVBuffer[1] = Vector3(box.mMax.mX, box.mMin.mY, box.mMin.mZ);
			mVBuffer[2] = Vector3(box.mMax.mX, box.mMax.mY, box.mMin.mZ);
			mVBuffer[3] = Vector3(box.mMin.mX, box.mMax.mY, box.mMin.mZ);

			mVBuffer[4] = Vector3(box.mMin.mX, box.mMin.mY, box.mMax.mZ);
			mVBuffer[5] = Vector3(box.mMax.mX, box.mMin.mY, box.mMax.mZ);
			mVBuffer[6] = box.mMax;
			mVBuffer[7] = Vector3(box.mMin.mX, box.mMax.mY, box.mMax.mZ);
		}

		void Render(RenderSystem& renderSystem) override
		{
			ReadBufferPtr readIBuffer = 
				DataBufferFactory::CreateBaseMemoryReadBuffer(&mIBuffer, sizeof(u16) * 36);
			HardwareIndexBufferPtr iBuffer = renderSystem.CreateHardwareIndexBuffer(
				readIBuffer, DRE_INDEX_ELEMENT_TYPE_U16, 36, DRE_BUFFER_USAGE_DEFAULT);

			ReadBufferPtr readVBuffer = 
				DataBufferFactory::CreateBaseMemoryReadBuffer(&mIBuffer, sizeof(u16) * 36);
			HardwareVertexBufferPtr vBuffer = renderSystem.CreateHardwareVertexBuffer(
				readVBuffer, sizeof(Vector3), 8, DRE_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, DRE_BUFFER_USAGE_DEFAULT);

			renderSystem.SetFillMode(DRE_FILL_WIREFRAME_MODE);

			renderSystem.SetHardwareIndexBuffer(iBuffer);
			renderSystem.SetHardwareVertexBuffer(vBuffer);

			renderSystem.Render();
		}

	private:
		/// 八个顶点
		Vector3 mVBuffer[8];
		/// 十二个三角形
		u16 mIBuffer[36];
		/// 渲染HLSL
		static HLSLProgram mHLSLProgram;		
	};	// end class VisiableBoundsBox

}	// end namespace dream

#endif	// end __DREVISIABLEBOUNDSBOX_H__