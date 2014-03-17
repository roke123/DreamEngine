#include "DreMath.h"
#include "DreException.h"

namespace dream
{
	const f32 Math::MAX_F32	= FLT_MAX;
	const f32 Math::MIN_F32	= -FLT_MAX;

	// PI_F
	const f32 Math::PI_F					= 3.14159265359f;
	// PI_F * 2
	const f32 Math::DOUBLE_PI_F				= 2 * Math::PI_F;
	// PI_F�ĵ���.
	const f32 Math::RECIPROCAL_PI_F			= 1.0f / Math::PI_F;
	// PI_F / 2
	const f32 Math::HALF_PI_F				= Math::PI_F / 2.0f;
	// �ӻ���ת�Ƕ�
	const f32 Math::DEGTORAD_F				= Math::PI_F / 180.0f;
	// �ӽǶ�ת����
	const f32 Math::RADTODEG_F				= 180.0f / Math::PI_F;

	Float Float::instance;

	const f32 Float::NaN = _MakeFloat(0x00000000, 0x7F800000, 0x007fffff);
	const f32 Float::Zero = MakeFloat(0x00000000, 0x00000000, 0x00000000);
	const f32 Float::PositiveInfinity = _MakeFloat(0x00000000, 0x7F800000, 0x00000000);
	const f32 Float::NegativeInfinity = _MakeFloat(0x80000000, 0x7F800000, 0x00000000);

	// ��ȷ��β������λ������0.000002
	const int Float::DiffSix		= 16;
	// ��ȷ��β������λ������0.000015
	const int Float::DiffFive		= 128;
	// ��ȷ��β������λ������0.000122
	const int Float::DiffFour		= 1024;
	// ��ȷ��β������λ������0.001953
	const int Float::DiffThree		= 16384;
	// ��ȷ��β������λ������0.015625
	const int Float::DiffTwo		= 131072;
	// Ĭ�Ͼ�ȷλ��
	const int Float::DiffDefault = DiffSix;

	Float::Float()
	{
#		if defined(OPEN_FLOAT_OP)
			DreAssert(sizeof(f32)==sizeof(int), "f32������int���ʹ�С��һ��");
			DreAssert(sizeof(f32)==4, "f32���ʹ�С������4���ֽ�");
#			if defined(_SIGNED_SHIFT)
				//�����λ�����Ƿ������
				int i = -1;	
				i >>= 5;
				DreAssert(i<0, "��ǰ��λ�������Ǵ�������λ");
#			endif
#		endif
	}



}	// end namespace dream