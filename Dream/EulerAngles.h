#ifndef __EULERANGLES_H__
#define __EULERANGLES_H__

#include "DreMathDeclaration.h"

#include "Matrix4.h"
#include "Quaternion.h"

namespace dream
{

	class EulerAngles
	{
	public:
		EulerAngles() : heading_( 0.0f ), pitch_( 0.0f ), bank_( 0.0f )
		{
			//留空
		}

		EulerAngles( f32 heading, f32 pitch, f32 bank ) :
			heading_( heading ), pitch_( pitch ), bank_( bank )
		{
			//留空
		}

		//置零
		inline void Identity() { heading_ = pitch_ = bank_ = 0.0f; };

		inline void Set( f32 heading, f32 pitch, f32 bank )
		{
			heading_ = heading;
			pitch_ = pitch;
			bank_ = bank;
		}

		//转换欧拉角到四元数
		Quaternion EularAnglesToQuaternion() const;

		//转换欧拉角到矩阵
		Matrix4 EularAnglesToMatrix4() const;

		f32 heading_;
		f32 pitch_;
		f32 bank_;
	}; 

}	// end namespace dream

#endif	// end __EULERANGLES_H__