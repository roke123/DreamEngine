#ifndef __DRESCENEMANAGER_H__
#define __DRESCENEMANAGER_H__

#include "DreSceneManagerDeclaration.h"
#include "DreRenderDeclaration.h"

#include "DreNode.h"
#include "DreRenderQueue.h"

namespace dream
{

	class SceneManager
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

	private:
		typedef set<CameraPtr, ConvertibleObjectNameCmp>	CameraSet;
		/// 所有产生的相机集
		CameraSet					mAllCameraSet;
		/// 所有用于渲染的相机集
		CameraSet					mRenderCameraSet;
		
		/// 渲染队列
		SMSC::RenderQueue			mRenderQueue;

	};	// end class SceneManager

}; // end namespace dream

#endif	// end __DRESCENEMANAGER_H__