#ifndef __DRESCENEMANAGER_H__
#define __DRESCENEMANAGER_H__

#include "DreSceneManagerDeclaration.h"
#include "DreRenderDeclaration.h"

/// SceneManager
#include "DreRenderQueue.h"
#include "DreSceneRootNode.h"

/// other
#include "DreSingleton.h"
#include "DreStringToIDMap.h"

namespace dream
{

	/**
		用于管理Scene Node上的Tag
		@note
			tag号从1开始，每次tag索引可能并不一样，因此应使用tag名进行查询
	*/
	class SceneNodeTags
	{
	public:
		SceneNodeTags() : mLastTagIndex(1) {
			// 留空
		}

		void AddTag(string tagName) 
		{ 
			++mLastTagIndex; 
			mTagDictory.insert(make_pair<string, u8>(std::move(tagName), std::move(mLastTagIndex)));
		};

		u8 GetTag(const string& tagName)
		{
			mTagDictory.find(tagName);
		}

	private:
		u8 mLastTagIndex;

		map<string, u8> mTagDictory;
	};

	class SceneManager : public Singleton<SceneManager>
	{
	public:
		/** 通过名称查找产生的相机 */
		CameraPtr FindCameraByName(const string& cameraName);

		/** 通过名称查找一个用于渲染的相机 */
		CameraPtr FindRenderCameraByName(const string& cameraName);

		/** 注册一个渲染相机 */
		void RegisterRenderCamera(CameraPtr& renderCamera);

		/** 注册一个渲染相机，并绑定到一个renderTarget
		* @param		renderCamera			用于渲染的相机
		* @param		renderTarget			绑定的renderTarget
		*/
		void RegisterRenderCamera(CameraPtr& renderCamera, RenderTargetPtr& renderTarget);

		SceneRootNode* GetRootNode() { return &mRootNode; }

		void RenderSingleObject(RenderablePtr& rend, PassPtr& pass, const LightList& manualLights);

	private:
		RenderSystemPtr	mRenderSystem;

		typedef set<CameraPtr, ConvertibleObjectNameCmp>	CameraSet;
		/// 所有产生的相机集
		CameraSet						mAllCameraSet;
		/// 所有用于渲染的相机集
		CameraSet						mRenderCameraSet;
		/// 用于管理所有 Scene Node 的根节点
		SceneRootNode					mRootNode;

		/// 节点标签映射
		StringToIDMap<TagID>			mTagMap;
		/// 节点层映射
		StringToIDMap<LayerID>			mLayerMap;

	};	// end class SceneManager

}; // end namespace dream

#endif	// end __DRESCENEMANAGER_H__