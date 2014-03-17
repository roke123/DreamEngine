#include "EulerAngles.h"

#include "DreMath.h"
#include "Quaternion.h"
#include "Matrix4.h"

namespace dream
{

		Quaternion EulerAngles::EularAnglesToQuaternion() const 
		{
			Quaternion temp;
			f32 sp = 0.0f, sb = 0.0f, sh = 0.0f;
			f32 cp = 0.0f, cb = 0.0f, ch = 0.0f;

			/*SinCos( pitch_ * 0.5f, &sp, &cp );
			SinCos( bank_ * 0.5f, &sb, &cb );
			SinCos( heading_ * 0.5f, &sh, &ch );*/

			temp.mW = ch * cp * cb + sh * sp * sb;
			temp.mX = -ch * sp * cb - sh * cp * sb;
			temp.mY = ch * sp * sb - sh * cb * cp;
			temp.mZ = sh * sp * cb - ch * cp * sb;

			return temp;
		}

		Matrix4 EulerAngles::EularAnglesToMatrix4() const
		{
			Matrix4 temp;

			temp.mM[0][0] = Cos(heading_)*Cos(bank_) + Sin(heading_)*Sin(pitch_)*Sin(bank_);
			temp.mM[0][1] = Sin(bank_)*Cos(pitch_);
			temp.mM[0][2] = -Sin(heading_)*Cos(bank_) + Cos(heading_)*Sin(pitch_)*Sin(bank_);

			temp.mM[1][0] = -Cos(heading_)*Sin(bank_) + Sin(heading_)*Sin(pitch_)*Cos(bank_); 
			temp.mM[1][1] = Cos(bank_)*Cos(pitch_);
			temp.mM[1][2] = Sin(bank_)*Sin(heading_) + Cos(heading_)*Sin(pitch_)*Cos(bank_);

			temp.mM[2][0] = Sin(heading_)*Cos(pitch_);
			temp.mM[2][1] = -Sin(pitch_);
			temp.mM[2][2] = Cos(heading_)*Cos(pitch_);

			temp.mM[3][0] = temp.mM[3][1] = temp.mM[3][2] = 0.0f; 

			return temp;
		}

}	// end namespace dream;