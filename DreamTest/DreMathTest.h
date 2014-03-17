#ifndef __DREMATHTEST_H__
#define __DREMATHTEST_H__

#include <cppunit\extensions\HelperMacros.h>

#include <DreMath.h>
using namespace dream;

class DreMathTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(DreMathTest);
	CPPUNIT_TEST_SUITE_END();

public:

};	// end class DreMathTest

class DreFloatTest : public CppUnit::TestFixture
{
	#define _fval_to_ival(fval) *(int*)&(fval)
	#define _ival_to_fval(ival) *(float*)&(ival)
public:
	CPPUNIT_TEST_SUITE(DreFloatTest);
	CPPUNIT_TEST(Initialization);
	CPPUNIT_TEST(IsNaN);
	CPPUNIT_TEST(IsValid);
	CPPUNIT_TEST(IsInfinity);
	CPPUNIT_TEST(IsZero);
	CPPUNIT_TEST(IsDenormalized);
	CPPUNIT_TEST(LessThanZero);
	CPPUNIT_TEST(GreaterThanZero);
	CPPUNIT_TEST(LessOrEqualZero);
	CPPUNIT_TEST(GreaterOrEqualZero);
	CPPUNIT_TEST(IsEqual);
	CPPUNIT_TEST(GreaterThan);
	CPPUNIT_TEST(LessThan);
	CPPUNIT_TEST(GreaterEqual);
	CPPUNIT_TEST(LessEqual);
	CPPUNIT_TEST(ClampZeroToOne);
	CPPUNIT_TEST(ClampAToB);
	CPPUNIT_TEST(ClampNonnegative);
	CPPUNIT_TEST(InvSqrt);
	CPPUNIT_TEST(FastSqrt);
	CPPUNIT_TEST(Swap);
	CPPUNIT_TEST_SUITE_END();

	void Initialization();

	void IsNaN();

	void IsValid();

	void IsInfinity();

	void IsZero();

	void IsDenormalized();

	void LessThanZero();

	void GreaterThanZero();

	void LessOrEqualZero();

	void GreaterOrEqualZero();

	void IsEqual();

	void GreaterThan();

	void LessThan();

	void GreaterEqual();

	void LessEqual();

	void ClampZeroToOne();

	void ClampAToB();

	void ClampNonnegative();

	void InvSqrt();

	void FastSqrt();

	void Swap();
};	// end class DreFloatTest

#endif	// end __DREMATHTEST_H__