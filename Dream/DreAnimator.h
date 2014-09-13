#ifndef __DREANIMATOR_H__
#define __DREANIMATOR_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{
	/** 关键帧
	*/
	class KeyFrame
	{
	public:
		/** 构造函数 */
		KeyFrame(f32 timePoint) : mTimePoint(timePoint), mISinvalid(false)
		{
			// 留空
		}

		/** 虚析构函数 */
		virtual ~KeyFrame() {};

		/** 通知当前帧已被销毁 */
		void NotifyDispose() { mISinvalid = true; }

		/** 返回关键帧的时间点 */
		f32 GetTimePoint() const { return mTimePoint; }

		/** 返回是否无效帧 */
		bool ISinvalidFrame() const { return mISinvalid; }

	private:
		/// 当前帧是否无效帧
		bool mISinvalid;
		/// 在动画器中的时间点
		f32 mTimePoint;
	};	// end class KeyFrame

	/** 时间索引 */
	class TimeIndex
	{
	public:
		TimeIndex(float timePoint) : mTimePoint(timePoint), mIsTimePoint(true)
		{
			// 留空
		}

		TimeIndex(int index) : mIndex(index), mIsTimePoint(false)
		{
			// 留空
		}

		/** 返回是否时间点 */
		bool GetIsTimePoint() const { return mIsTimePoint; }

		/** 返回时间点 */
		f32 GetTimePoint() const { return mTimePoint; }

		/** 返回索引 */
		u32 GetIndex() const { return mIndex; }

	private:
		// 是否时间点
		bool mIsTimePoint;

		// 时间点/索引
		union 
		{
			f32 mTimePoint;
			u32 mIndex;
		};
	};	// end class TimeIndex

	/** 动画器用于绑定到节点，作为自动动画
	*/
	class Animator
	{
	public:
		/** 构造函数
		* @param	animationName		动画名
		*/
		Animator(string animationName);

		/** 虚析构函数
		*/
		~Animator();

		/** 根据时间索引返回一个最近的keyFrame */
		virtual KeyFrame* GetKeyFrameByTimeIndex(const TimeIndex& i) = 0;
		
		/** 根据时间索引返回一个最近的keyFrame */
		virtual const KeyFrame* GetKeyFrameByTimeIndex(const TimeIndex& i) const = 0;

		/** 返回动画名 */
		string GetAnimationName() const { return mAnimationName; };

	private:
		/// 动画器名称
		string mAnimationName;	
	};	// end class Animator

}	// end namespace dream

#endif	// end of __DREANIMATOR_H__