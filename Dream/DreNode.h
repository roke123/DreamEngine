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
		virtual Vector3 _GetFinalPosition() const = 0;;
		/** ȡ�����շ��� */
		virtual Quaternion _GetFinalOrientation() const = 0;
		/** ȡ������Scale */
		virtual Vector3 _GetFinalScale() const = 0;

		/** ��ȡת������ */
		virtual Matrix4 GetWorldMatrix() const = 0;

		/** ֪ͨ���ڵ����һ��ʵ�� */
		virtual void _NotifyChanged() = 0;

		/** ���½ڵ㣬���㵱ǰ�ڵ����� */
		virtual void _Update() = 0;

		/** ȡ����ײ�� */
		virtual AABB3 GetBoundBox() const = 0;

		/** ���ҿɼ�Ԫ�� */
		virtual void _FindVisibleObject(const CameraPtr& camera) = 0;

	};	// end class Node

}	// end namespace Node

#endif	// end __DRENODE_H__