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
		���ڹ���Scene Node�ϵ�Tag
		@note
			tag�Ŵ�1��ʼ��ÿ��tag�������ܲ���һ�������Ӧʹ��tag�����в�ѯ
	*/
	class SceneNodeTags
	{
	public:
		SceneNodeTags() : mLastTagIndex(1) {
			// ����
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
		/** ͨ�����Ʋ��Ҳ�������� */
		CameraPtr FindCameraByName(const string& cameraName);

		/** ͨ�����Ʋ���һ��������Ⱦ����� */
		CameraPtr FindRenderCameraByName(const string& cameraName);

		/** ע��һ����Ⱦ��� */
		void RegisterRenderCamera(CameraPtr& renderCamera);

		/** ע��һ����Ⱦ��������󶨵�һ��renderTarget
		* @param		renderCamera			������Ⱦ�����
		* @param		renderTarget			�󶨵�renderTarget
		*/
		void RegisterRenderCamera(CameraPtr& renderCamera, RenderTargetPtr& renderTarget);

		SceneRootNode* GetRootNode() { return &mRootNode; }

		void RenderSingleObject(RenderablePtr& rend, PassPtr& pass, const LightList& manualLights);

	private:
		RenderSystemPtr	mRenderSystem;

		typedef set<CameraPtr, ConvertibleObjectNameCmp>	CameraSet;
		/// ���в����������
		CameraSet						mAllCameraSet;
		/// ����������Ⱦ�������
		CameraSet						mRenderCameraSet;
		/// ���ڹ������� Scene Node �ĸ��ڵ�
		SceneRootNode					mRootNode;

		/// �ڵ��ǩӳ��
		StringToIDMap<TagID>			mTagMap;
		/// �ڵ��ӳ��
		StringToIDMap<LayerID>			mLayerMap;

	};	// end class SceneManager

}; // end namespace dream

#endif	// end __DRESCENEMANAGER_H__