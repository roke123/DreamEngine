////////////////////////////////////
// date: 2014/9/5 14:35
// author: zou lei
////////////////////////////////////

#ifndef __DREMESH_H__
#define __DREMESH_H__

#include "DreSceneManagerDeclaration.h"

#include "DreComponent.h"
#include "DreRenderable.h"
#include "DreVertexIndexData.h"


namespace dream
{
	struct MeshLodUsage;
	class LodStrategy;
	class SubMesh;
	typedef shared_ptr<SubMesh> SubMeshPtr;
	class Mesh;

	class SubMesh
	{
	private:
		typedef vector<IndexDataPtr>							LodFaceList;
		typedef LodFaceList::iterator							LodFaceListIte;
		typedef LodFaceList::const_iterator						LodFaceListConstIte;

	public:
		/** ������Ĺ��캯��
		* @param	vertexData
		*	��������
		* @param	indexData
		*	ϸ�ڵȼ���ߵĶ�����������
		* @param	material
		*	��Ⱦ����ʹ�õĲ�������
		*/
		SubMesh(
			Mesh* parent,
			VertexDataPtr& vertexData, 
			IndexDataPtr indexData = nullptr, 
			MaterialPtr material = nullptr);

		void InsertLodFaceData(u16 lodLevel, IndexDataPtr& indexData)
		{
			if(lodLevel > mLodFaceList.size)
				mLodFaceList.resize(lodLevel);
			mLodFaceList[lodLevel] = indexData;
		}

		void RemoveLodFaceData(u32 lodLevel)
		{
			mLodFaceList[lodLevel] = nullptr;
		}

		IndexDataPtr GetIndexData(u32 lodLevel) const
		{
			IndexDataPtr result = nullptr;

			if(lodLevel > mLodFaceList.size)
			{
				result = mLodFaceList[mLodFaceList.size - 1];
			}
			else
			{
				for(u32 i = lodLevel; i >= 0; -- i)
				{
					if(mLodFaceList[i] != nullptr)
						result = mLodFaceList[i];
				}
			}

			return result;
		}

		/** ȡ�����������Ⱦ�������� */
		MaterialPtr GetMaterial() const { return mMaterial; }
		void SetMaterial(MaterialPtr& material) { mMaterial = material; }

		/** ȡ�����������Ⱦ�������� */
		VertexDataPtr GetVertexData() const { return mVertexData; }
		void SetVertexData(VertexDataPtr& vertexData) { mVertexData = vertexData; }

		/** ȡ�ø����� */ 
		Mesh* GetParent() const { return mParentMesh; }
	private:
		Mesh*						mParentMesh;
		/// ������Ⱦ�Ĳ�������
		MaterialPtr					mMaterial;
		/// ������Ⱦ�Ķ�������
		VertexDataPtr				mVertexData;
		/// ���ڲ�ͬϸ�ڵȼ��Ķ��������б�
		LodFaceList					mLodFaceList;
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