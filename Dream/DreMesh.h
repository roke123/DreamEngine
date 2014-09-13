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
	* ��¼ vertex �� bone �Ķ�Ӧ��ϵ���Լ�Ȩ�� 
	*/
	struct VectexBoneAssignment
	{
		u32 vextexIndex;
		u16 boneIndex;
		f32 weight;
	};

	/**
	* Mesh ��һ��������԰��� SceneNode �£�ͬʱ Mesh �̳� Renderable �ӿ�
	*/
	class Mesh : public Renderable
	{
	public:
		typedef vector<f32>									LodValueList;
		typedef vector<MeshLodUsage>						MeshLodUsageList;
		typedef vector<SubMeshPtr>							SubMeshList;

	protected:
		/// ÿ��Mesh��������һ��SubMesh
		SubMeshList mSubMeshList;

		/// �Ƿ�Ͷ����Ӱ
		bool		mShadowCasterEnable;

		/// �Ƿ������Ӱ
		bool		mShadowReceiveEnable;

	public:
		void SetShadowCasterEnable(bool enable) { mShadowCasterEnable = enable; }
		bool GetShadowCasterEnable() const { return mShadowCasterEnable; }

		void SetShadowReceiveEnable(bool enable) { mShadowReceiveEnable = enable; }
		bool GetShadowReceiveEnable() const { return mShadowReceiveEnable; }

	};	// end of class Mesh

}

#endif	// end of __DREMESH_H__