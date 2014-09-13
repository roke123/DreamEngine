#include "DreMath.h"
#include "DreException.h"

namespace dream
{
	Float Float::instance;

	const f32 Float::NaN = _MakeFloat(0x00000000, 0x7F800000, 0x007fffff);
	const f32 Float::Zero = _MakeFloat(0x00000000, 0x00000000, 0x00000000);
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