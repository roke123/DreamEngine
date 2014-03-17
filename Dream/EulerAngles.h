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
			//����
		}

		EulerAngles( f32 heading, f32 pitch, f32 bank ) :
			heading_( heading ), pitch_( pitch ), bank_( bank )
		{
			//����
		}

		//����
		inline void Identity() { heading_ = pitch_ = bank_ = 0.0f; };

		inline void Set( f32 heading, f32 pitch, f32 bank )
		{
			heading_ = heading;
			pitch_ = pitch;
			bank_ = bank;
		}

		//ת��ŷ���ǵ���Ԫ��
		Quaternion EularAnglesToQuaternion() const;

		//ת��ŷ���ǵ�����
		Matrix4 EularAnglesToMatrix4() const;

		f32 heading_;
		f32 pitch_;
		f32 bank_;
	}; 

}	// end namespace dream

#endif	// end __EULERANGLES_H__