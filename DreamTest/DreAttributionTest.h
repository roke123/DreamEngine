#ifndef __DREATTRIBUTIONTEST_H__
#define __DREATTRIBUTIONTEST_H__

#include <cppunit\extensions\HelperMacros.h>

#include <DreAttribution.h>
using namespace dream;

class DreAttributionTest : public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE(DreAttributionTest);
	CPPUNIT_TEST(NullTest);
	CPPUNIT_TEST_SUITE_END();

	void NullTest()
	{
		Attribution a(10);
		CPPUNIT_ASSERT(!a.IsNull());
		a.SetNull();
		CPPUNIT_ASSERT(a.IsNull());
	}
};

#endif	// end __DREATTRIBUTIONTEST_H__