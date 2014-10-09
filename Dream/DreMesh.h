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
		/** 子网格的构造函数
		* @param	vertexData
		*	顶点数据
		* @param	indexData
		*	细节等级最高的顶点索引数据
		* @param	material
		*	渲染网格使用的材质数据
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

		/** 取得子网格的渲染材质数据 */
		MaterialPtr GetMaterial() const { return mMaterial; }
		void SetMaterial(MaterialPtr& material) { mMaterial = material; }

		/** 取得子网格的渲染顶点数据 */
		VertexDataPtr GetVertexData() const { return mVertexData; }
		void SetVertexData(VertexDataPtr& vertexData) { mVertexData = vertexData; }

		/** 取得父网格 */ 
		Mesh* GetParent() const { return mParentMesh; }
	private:
		Mesh*						mParentMesh;
		/// 用于渲染的材质数据
		MaterialPtr					mMaterial;
		/// 用于渲染的顶点数据
		VertexDataPtr				mVertexData;
		/// 用于不同细节等级的顶点索引列表
		LodFaceList					mLodFaceList;
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