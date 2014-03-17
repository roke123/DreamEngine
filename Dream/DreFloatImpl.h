#ifndef __DREFLOATIMPL_H__
#define __DREFLOATIMPL_H__

// ת��float��int����
#if defined(C99)
#define _fval_to_ival(fval) *(int*)&(fval)
#define _ival_to_fval(ival) *(float*)&(ival)
#else
#define _fval_to_ival(fval,ival) memcpy(&ival,&fval,sizeof(float)) // these are safer, but perhaps slower
#define _ival_to_fval(ival,fval) memcpy(&fval,&ival,sizeof(int))   // C99 does not make the *(int*)& types well-defined
#endif

// �������λ�ɰ棬c++Ϊ��֤��λΪ�˳�2����������λ�����λ��ʹ�÷���λ
#if defined(_SIGNED_SHIFT)
#define SIGNMASK(i) ((i)>>31) 
#else
#define SIGNMASK(i) (~((((unsigned int)(i))>>31)-1))
#endif

f32 Float::_MakeFloat(int sign, int exp, int mantissa)
{
	int iVal = sign | exp | mantissa;
	return _ival_to_fval(iVal);
}

void Float::_SplitFloat(f32 val, int* sign, int* exp, int* mantissa)
{
	int iVal = _fval_to_ival(val);
	*sign		= iVal & 0x80000000;
	*exp		= iVal & 0x7f800000;
	*mantissa	= iVal & 0x007fffff;
}

bool Float::IsNaN(f32 val)
{
	int sign = 0, exp = 0, mantissa = 0;
	_SplitFloat(val, &sign, &exp, &mantissa);
	return (exp == 0x7F800000) && (mantissa != 0x00000000);
}

bool Float::IsValid(f32 val)
{
	int sign = 0, exp = 0, mantissa = 0;
	_SplitFloat(val, &sign, &exp, &mantissa);
	return exp != 0x7F800000;
}

bool Float::IsInfinity(f32 val)
{
	int sign = 0, exp = 0, mantissa = 0;
	_SplitFloat(val, &sign, &exp, &mantissa);
	return (exp == 0x7F800000) && (mantissa == 0x00000000);
}

bool Float::IsZero(f32 val)
{
	int ival = _fval_to_ival(val) << 1;
	return ival == 0;
}

bool Float::IsDenormalized(f32 val)
{
	int sign = 0, exp = 0, mantissa = 0;
	_SplitFloat(val, &sign, &exp, &mantissa);
	return (exp == 0x00000000) && (mantissa != 0x00000000);
}

bool Float::LessThanZero(f32 val)
{
	int iVal = _fval_to_ival(val);
	// תΪ�޷������Ƚϣ�������λΪ1����β����Ϊ0
	return iVal > 0x80000000u;
}

bool Float::GreaterThanZero(f32 val)
{
	int iVal = _fval_to_ival(val);
	return iVal > 0;
}

bool Float::LessOrEqualZero(f32 val)
{
	int iVal = _fval_to_ival(val);
	return iVal <= 0;
}

bool Float::GreaterOrEqualZero(f32 val)
{
	int iVal = _fval_to_ival(val);
	// תΪ�޷������Ƚϣ�������λΪ0
	return iVal <= 0x80000000u;
}
	
f32 Float::ClampZeroToOne(f32 val)
{
	int iVal = _fval_to_ival(val);
	// ��С��0��mark = 0xffffffff��������mark=0x00000000
	int mark = SIGNMASK(iVal);
	// ��iValС��0�����㣬�����0������ԭֵ
	iVal &= ~mark;
		
	f32 fval = 1.0f - _ival_to_fval(iVal);
	iVal = _fval_to_ival(fval);
	// ��С��0��mark = 0xffffffff��������mark=0x00000000
	mark = SIGNMASK(iVal);
	// ��iValС��0�����㣬�����0������ԭֵ
	iVal &= ~mark;

	return 1.0f - _ival_to_fval(iVal);
}

bool Float::IsEqual(f32 a, f32 b, int maxDiff /* = DiffDefault */)
{
	int iValA = _fval_to_ival(a);
	int iValB = _fval_to_ival(b);
	int mark = SIGNMASK(iValA ^ iValB);
	int diff = ((0x80000000 - iValA) & mark) | (iValA & ~mark) - iValB;
	
	int v1 = maxDiff + diff;
	int v2 = maxDiff - diff;

	return (v1 | v2) >= 0;
}

bool Float::GreaterThan(f32 a, f32 b)
{
	int iValA = _fval_to_ival(a);
	int iValB = _fval_to_ival(b);
	// ����Ƿ�A��B��Ϊ����
	int test = (iValA & iValB) & 0x80000000;
	if(test)
	{
		// Ϊ����ʱ��int�ϴ������С
		return iValB > iValA;
	}
	return iValA > iValB;
}

bool Float::LessThan(f32 a, f32 b)
{
	int iValA = _fval_to_ival(a);
	int iValB = _fval_to_ival(b);
	// ����Ƿ�A��B��Ϊ����
	int test = (iValA & iValB) & 0x80000000;
	if(test)
	{
		// Ϊ����ʱ��int�ϴ������С
		return iValB < iValA;
	}
	return iValA < iValB;
}

bool Float::GreaterEqual(f32 a, f32 b)
{
	if(IsEqual(a, b))
		return true;

	return GreaterThan(a, b);
}

bool Float::LessEqual(f32 a, f32 b)
{
	if(IsEqual(a, b))
		return true;

	return GreaterThan(a, b);
}

f32 Float::ClampAToB(f32 val, f32 A, f32 B)
{
	DreAssert(A < B, "");
	val -= A;
	val /= (B-A);
	val = ClampZeroToOne(val);
	val *= (B-A);
	val += A;
	DreAssert((A <= val) && (val <= B), "");
	return val;
}

f32 Float::ClampNonnegative(f32 val)
{
	int iVal = _fval_to_ival(val);
	int mark = SIGNMASK(iVal);
	iVal = iVal & ~mark;
	return _ival_to_fval(iVal);
}

f32 Float::InvSqrt(f32 val)
{
	DreAssert(val > 0, "");

	f32 valHalf = val * 0.5f;
	int i = _fval_to_ival(val);
	i = 0x5f375a86 - (i >> 1);
	val = _ival_to_fval(i);
	val = val * (1.5f - valHalf * val * val);
	return val;
}

f32 Float::FastSqrt(f32 val)
{
	DreAssert(val >= 0, "");

	int ival = _fval_to_ival(val);
	// ����0�ͷǹ淶��������0
	if (0 == ((ival >> 23)&255))
		return 0;
	return val * InvSqrt(val);
}

void Float::Swap(f32& a, f32& b)
{
	int iValA = _fval_to_ival(a);
	int iValB = _fval_to_ival(b);
	iValA ^= iValB;
	iValB ^= iValA;
	iValA ^= iValB;
	a = _ival_to_fval(iValA);
	b = _ival_to_fval(iValB);
}

#undef OPEN_FLOAT_OP	
#undef C99				
#undef _SIGNED_SHIFT			
#undef _fval_to_ival
#undef _ival_to_fval
#undef SIGNMASK

#endif // __DREFLOATIMPL_H__