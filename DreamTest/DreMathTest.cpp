#include "DreMathTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DreMathTest); 
CPPUNIT_TEST_SUITE_REGISTRATION(DreFloatTest);

void DreFloatTest::Initialization()
{
	CPPUNIT_ASSERT_EQUAL(_fval_to_ival(Float::NaN),		0x7fffffff);
	CPPUNIT_ASSERT_EQUAL(_fval_to_ival(Float::Zero),	0x00000000);
	CPPUNIT_ASSERT_EQUAL(_fval_to_ival(Float::PositiveInfinity), 0x7f800000);
	CPPUNIT_ASSERT_EQUAL(_fval_to_ival(Float::NegativeInfinity), (int)0xff800000);
}

void DreFloatTest::IsNaN()
{
	int NaN = 0x7fffffff;
	CPPUNIT_ASSERT(Float::IsNaN(_ival_to_fval(NaN)));
}

void DreFloatTest::IsValid()
{
	int NaN = 0x7fffffff;
	int PositiveInfinity = 0x7f800000;
	int NegativeInfinity = 0xff800000;
	int valid = 0x058af93dd;
	CPPUNIT_ASSERT(!Float::IsValid(_ival_to_fval(NaN)));
	CPPUNIT_ASSERT(!Float::IsValid(_ival_to_fval(PositiveInfinity)));
	CPPUNIT_ASSERT(!Float::IsValid(_ival_to_fval(NegativeInfinity)));
	CPPUNIT_ASSERT(Float::IsValid(_ival_to_fval(valid)));
}

void DreFloatTest::IsInfinity()
{
	int PositiveInfinity = 0x7f800000;
	int NegativeInfinity = 0xff800000;
	CPPUNIT_ASSERT(!Float::IsValid(_ival_to_fval(PositiveInfinity)));
	CPPUNIT_ASSERT(!Float::IsValid(_ival_to_fval(NegativeInfinity)));
}

void DreFloatTest::IsZero()
{
	int zero	= 0x00000000;
	int notZero = 0x00000001;
	CPPUNIT_ASSERT(Float::IsZero(_ival_to_fval(zero)));
	CPPUNIT_ASSERT(!Float::IsZero(_ival_to_fval(notZero)));
}

void DreFloatTest::IsDenormalized()
{
	int denormalize = 0x007fffff;
	int normalize	= 0x008fffff;
	CPPUNIT_ASSERT(Float::IsDenormalized(_ival_to_fval(denormalize)));
	CPPUNIT_ASSERT(!Float::IsDenormalized(_ival_to_fval(normalize)));
}

void DreFloatTest::LessThanZero()
{
	int lessZero	= 0x807fffff;
	int greatZero	= 0x008fffff;
	CPPUNIT_ASSERT(Float::LessThanZero(_ival_to_fval(lessZero)));
	CPPUNIT_ASSERT(!Float::LessThanZero(_ival_to_fval(greatZero)));
}

void DreFloatTest::GreaterThanZero()
{
	int lessZero	= 0x807fffff;
	int greatZero	= 0x008fffff;
	CPPUNIT_ASSERT(!Float::GreaterThanZero(_ival_to_fval(lessZero)));
	CPPUNIT_ASSERT(Float::GreaterThanZero(_ival_to_fval(greatZero)));
}

void DreFloatTest::LessOrEqualZero()
{
	int lessZero	= 0x807fffff;
	int greatZero	= 0x008fffff;
	int zero		= 0x00000000;
	CPPUNIT_ASSERT(Float::LessOrEqualZero(_ival_to_fval(lessZero)));
	CPPUNIT_ASSERT(Float::LessOrEqualZero(_ival_to_fval(zero)));
	CPPUNIT_ASSERT(!Float::LessOrEqualZero(_ival_to_fval(greatZero)));
}

void DreFloatTest::GreaterOrEqualZero()
{
	int lessZero	= 0x807fffff;
	int greatZero	= 0x008fffff;
	int zero		= 0x00000000;
	CPPUNIT_ASSERT(!Float::GreaterOrEqualZero(_ival_to_fval(lessZero)));
	CPPUNIT_ASSERT(Float::GreaterOrEqualZero(_ival_to_fval(zero)));
	CPPUNIT_ASSERT(Float::GreaterOrEqualZero(_ival_to_fval(greatZero)));
}

void DreFloatTest::IsEqual()
{
	f32 a = 1.111111f;
	f32 b = 1.111112f;
	f32 c = 1.111112f;
	CPPUNIT_ASSERT(Float::IsEqual(a, b));
	CPPUNIT_ASSERT(Float::IsEqual(c, b));
}

void DreFloatTest::GreaterThan()
{
	f32 a = 1.111111f;
	f32 b = 1.111112f;
	CPPUNIT_ASSERT(!Float::GreaterThan(a, b));
	CPPUNIT_ASSERT(Float::GreaterThan(b, a));
}

void DreFloatTest::LessThan()
{
	f32 a = 1.111111f;
	f32 b = 1.111112f;
	CPPUNIT_ASSERT(Float::LessThan(a, b));
	CPPUNIT_ASSERT(!Float::LessThan(b, a));
}

void DreFloatTest::GreaterEqual()
{
	f32 a = 1.111111f;
	f32 b = 1.111112f;
	int c = 0x56f18da5;
	int d = 0x56f18da5;
	CPPUNIT_ASSERT(Float::GreaterEqual(a, b));
	CPPUNIT_ASSERT(Float::GreaterEqual(_ival_to_fval(c), _ival_to_fval(d)));
}

void DreFloatTest::LessEqual()
{
	f32 a = 1.111111f;
	f32 b = 1.111112f;
	int c = 0x56f18da5;
	int d = 0x56f18da5;
	CPPUNIT_ASSERT(Float::LessEqual(a, b));
	CPPUNIT_ASSERT(Float::LessEqual(_ival_to_fval(c), _ival_to_fval(d)));
}

void DreFloatTest::ClampZeroToOne()
{
	f32 a = 5926.46653f;
	f32 b = 0.55654f;
	f32 c = -269.5494f;
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampZeroToOne(a), 1.0f));
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampZeroToOne(b), b));
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampZeroToOne(c), 0.0f));
}

void DreFloatTest::ClampAToB()
{
	f32 a = 5926.46653f;
	f32 b = 6.55654f;
	f32 c = -269.5494f;
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampAToB(a, 2.2f, 9.7f), 9.7f));
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampAToB(b, 2.2f, 9.7f), b));
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampAToB(c, 2.2f, 9.7f), 2.2f));
}

void DreFloatTest::ClampNonnegative()
{
	f32 a = 5926.46653f;
	f32 b = Float::Zero;
	f32 c = -269.5494f;
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampNonnegative(a), a));
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampNonnegative(b), Float::Zero));
	CPPUNIT_ASSERT(Float::IsEqual(Float::ClampNonnegative(c), 0.0f));
}

void DreFloatTest::InvSqrt()
{
	f32 a = 2.5697f;
	CPPUNIT_ASSERT(Float::IsEqual(Float::InvSqrt(a), 1.0f / sqrtf(a), Float::DiffTwo));
}

void DreFloatTest::FastSqrt()
{
	f32 a = 999999999999.6597f;
	CPPUNIT_ASSERT(Float::IsEqual(Float::FastSqrt(a), sqrtf(a), Float::DiffTwo));
}

void DreFloatTest::Swap()
{
	f32 a = 26.788f;
	f32 b = -0.2667f;
	Float::Swap(a, b);
	CPPUNIT_ASSERT(Float::IsEqual(b, 26.788f));
	CPPUNIT_ASSERT(Float::IsEqual(a, -0.2667f));
}