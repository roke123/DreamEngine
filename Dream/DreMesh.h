////////////////////////////////////
// date: 2014/9/5 14:35
// author: zou lei
////////////////////////////////////

#ifndef __DREMESH_H__
#define __DREMESH_H__

#include "DreSceneManager.h"

#include "DreComponent.h"
#include "DreRenderable.h"

namespace dream
{
	struct MeshLodUsage;
	class LodStrategy;
	class SubMesh;
	typedef shared_ptr<SubMesh> SubMeshPtr;

	/**
	* 记录 vertex 与 bone 的对应关系，以及权重 
	*/
	struct VectexBoneAssignment
	{
		u32 vextexIndex;
		u16 boneIndex;
		f32 weight;
	};

	/**
	* Mesh 是一个组件可以绑定在 SceneNode 下，同时 Mesh 继承 Renderable 接口
	*/
	class Mesh : public Renderable
	{
	public:
		typedef vector<f32>									LodValueList;
		typedef vector<MeshLodUsage>						MeshLodUsageList;
		typedef vector<SubMeshPtr>							SubMeshList;

	protected:
		/// 每个Mesh中至少有一个SubMesh
		SubMeshList mSubMeshList;

		/// 是否投射阴影
		bool		mShadowCasterEnable;

		/// 是否接收阴影
		bool		mShadowReceiveEnable;

	public:
		void SetShadowCasterEnable(bool enable) { mShadowCasterEnable = enable; }
		bool GetShadowCasterEnable() const { return mShadowCasterEnable; }

		void SetShadowReceiveEnable(bool enable) { mShadowReceiveEnable = enable; }
		bool GetShadowReceiveEnable() const { return mShadowReceiveEnable; }

	};	// end of class Mesh

}

#endif	// end of __DREMESH_H__