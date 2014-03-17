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

	private:
		typedef set<CameraPtr, ConvertibleObjectNameCmp>	CameraSet;
		/// ���в����������
		CameraSet					mAllCameraSet;
		/// ����������Ⱦ�������
		CameraSet					mRenderCameraSet;
		
		/// ��Ⱦ����
		SMSC::RenderQueue			mRenderQueue;

	};	// end class SceneManager

}; // end namespace dream

#endif	// end __DRESCENEMANAGER_H__