#ifndef __DRENODE_H__
#define __DRENODE_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{
	/** �����ڵ�
	*/
	class Node
	{
	public:
		/** ��������
		*/
		virtual ~Node() {}; 
		
		/** ȡ���������� */
		virtual Vector3 _GetFinalPosition() = 0;;
		/** ȡ�����շ��� */
		virtual Quaternion _GetFinalOrientation() = 0;
		/** ȡ������Scale */
		virtual Vector3 _GetFinalScale() = 0;

		/** ��ȡת������ */
		virtual Matrix4 GetWorldMatrix() = 0;

		/** ֪ͨ���ڵ���Ҫ���� */
		virtual void _NotifyNeedUpdate() = 0;

		/** ��Ⱦ����ǰ���½ڵ㣬���㵱ǰ�ڵ����� */
		virtual void _PreRenderUpdate() = 0;

		/** ��Ⱦ���̺���½ڵ㣬���㵱ǰ�ڵ����� */
		virtual void _PostRenderUpdate() = 0;

		/** �߼����½ڵ� */
		virtual void _FixedUpdate() = 0;

		/** ȡ����ײ�� */
		virtual AABB3 GetBoundBox() const = 0;

		/** ���ҿɼ�Ԫ��
		* @param
		*/
		virtual void _FindVisibleObject(const CameraPtr& camera) = 0;

	};	// end class Node

}	// end namespace Node

#endif	// end __DRENODE_H__