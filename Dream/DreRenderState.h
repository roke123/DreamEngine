#ifndef __DRERENDERSTATE_H__
#define __DRERENDERSTATE_H__

#include "DreTypes.h"

namespace dream
{

	class RenderState
	{
	private:
		/// 默认是DRE_COMPARISON_LESSEQUAL，DRE_COMPARISON_NEVER时关闭深度测试
		DRE_COMPARISON_FUNC mZBuffer;

		/// 反锯齿(多重取样)属性，0为不使用多重取样
		u8 mAntiAliasing;

		/// 颜色通道蒙版
		u8 mColorMask:4;

		// 
		// u8 ColorMaterial:3;

		//! Draw as wireframe or filled triangles? Default: false
		/** The user can access a material flag using
		\code material.Wireframe=true \endcode
		or \code material.setFlag(EMF_WIREFRAME, true); \endcode */
		bool Wireframe:1;

		//! Draw as point cloud or filled triangles? Default: false
		bool PointCloud:1;

		//! Flat or Gouraud shading? Default: true
		bool GouraudShading:1;

		//! Will this material be lighted? Default: true
		bool Lighting:1;

		//! Is the zbuffer writeable or is it read-only. Default: true.
		/** This flag is forced to false if the MaterialType is a
		transparent type and the scene parameter
		ALLOW_ZWRITE_ON_TRANSPARENT is not set. */
		bool ZWriteEnable:1;

		//! Is backface culling enabled? Default: true
		bool BackfaceCulling:1;

		//! Is frontface culling enabled? Default: false
		bool FrontfaceCulling:1;

		//! Is fog enabled? Default: false
		bool FogEnable:1;

		//! Should normals be normalized?
		/** Always use this if the mesh lit and scaled. Default: false */
		bool NormalizeNormals:1;
	};	// end class RenderState

}	// end namespace dream

#endif	// end __DRERENDERSTATE_H__