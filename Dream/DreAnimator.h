#ifndef __DREANIMATOR_H__
#define __DREANIMATOR_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{
	/** �ؼ�֡
	*/
	class KeyFrame
	{
	public:
		/** ���캯�� */
		KeyFrame(f32 timePoint) : mTimePoint(timePoint), mISinvalid(false)
		{
			// ����
		}

		/** ���������� */
		virtual ~KeyFrame() {};

		/** ֪ͨ��ǰ֡�ѱ����� */
		void NotifyDispose() { mISinvalid = true; }

		/** ���عؼ�֡��ʱ��� */
		f32 GetTimePoint() const { return mTimePoint; }

		/** �����Ƿ���Ч֡ */
		bool ISinvalidFrame() const { return mISinvalid; }

	private:
		/// ��ǰ֡�Ƿ���Ч֡
		bool mISinvalid;
		/// �ڶ������е�ʱ���
		f32 mTimePoint;
	};	// end class KeyFrame

	/** ʱ������ */
	class TimeIndex
	{
	public:
		TimeIndex(float timePoint) : mTimePoint(timePoint), mIsTimePoint(true)
		{
			// ����
		}

		TimeIndex(int index) : mIndex(index), mIsTimePoint(false)
		{
			// ����
		}

		/** �����Ƿ�ʱ��� */
		bool GetIsTimePoint() const { return mIsTimePoint; }

		/** ����ʱ��� */
		f32 GetTimePoint() const { return mTimePoint; }

		/** �������� */
		u32 GetIndex() const { return mIndex; }

	private:
		// �Ƿ�ʱ���
		bool mIsTimePoint;

		// ʱ���/����
		union 
		{
			f32 mTimePoint;
			u32 mIndex;
		};
	};	// end class TimeIndex

	/** ���������ڰ󶨵��ڵ㣬��Ϊ�Զ�����
	*/
	class Animator
	{
	public:
		/** ���캯��
		* @param	animationName		������
		*/
		Animator(string animationName);

		/** ����������
		*/
		~Animator();

		/** ����ʱ����������һ�������keyFrame */
		virtual KeyFrame* GetKeyFrameByTimeIndex(const TimeIndex& i) = 0;
		
		/** ����ʱ����������һ�������keyFrame */
		virtual const KeyFrame* GetKeyFrameByTimeIndex(const TimeIndex& i) const = 0;

		/** ���ض����� */
		string GetAnimationName() const { return mAnimationName; };

	private:
		/// ����������
		string mAnimationName;	
	};	// end class Animator

}	// end namespace dream

#endif	// end of __DREANIMATOR_H__