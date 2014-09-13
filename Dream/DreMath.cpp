#include "DreMath.h"
#include "DreException.h"

namespace dream
{
	Float Float::instance;

	const f32 Float::NaN = _MakeFloat(0x00000000, 0x7F800000, 0x007fffff);
	const f32 Float::Zero = _MakeFloat(0x00000000, 0x00000000, 0x00000000);
	const f32 Float::PositiveInfinity = _MakeFloat(0x00000000, 0x7F800000, 0x00000000);
	const f32 Float::NegativeInfinity = _MakeFloat(0x80000000, 0x7F800000, 0x00000000);

	// 精确到尾数后六位，误差≈0.000002
	const int Float::DiffSix		= 16;
	// 精确到尾数后五位，误差≈0.000015
	const int Float::DiffFive		= 128;
	// 精确到尾数后四位，误差≈0.000122
	const int Float::DiffFour		= 1024;
	// 精确到尾数后三位，误差≈0.001953
	const int Float::DiffThree		= 16384;
	// 精确到尾数后两位，误差≈0.015625
	const int Float::DiffTwo		= 131072;
	// 默认精确位数
	const int Float::DiffDefault = DiffSix;

	Float::Float()
	{
#		if defined(OPEN_FLOAT_OP)
			DreAssert(sizeof(f32)==sizeof(int), "f32类型与int类型大小不一致");
			DreAssert(sizeof(f32)==4, "f32类型大小不等于4个字节");
#			if defined(_SIGNED_SHIFT)
				//检查移位操作是否带符号
				int i = -1;	
				i >>= 5;
				DreAssert(i<0, "当前移位操作符非带符号移位");
#			endif
#		endif
	}



}	// end namespace dream