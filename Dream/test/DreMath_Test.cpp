#ifndef __DREMATH_TEST_H__
#define __DREMATH_TEST_H__

#include <boost\test\unit_test.hpp>
using namespace boost::unit_test;

#include <core\DreMath.h>
using namespace dream;

s32 sa = core::MIN_S32, sb = 0, sc = core::MAX_S32;
f32 fa = core::MIN_F32, fb = 0.0f, fc = core::MAX_F32;
	
struct Vectex
{
	float x, y, z;
	unsigned int color;
	float nx, ny, nz;
	static int vexterDataFormat[];
};

int Vectex::vexterDataFormat[] = 
{
	1, 2, 3
};

BOOST_AUTO_TEST_SUITE( s_DreMath )

//test：DreMath - function Min
BOOST_AUTO_TEST_CASE( c_Min )
{
	BOOST_REQUIRE( Vectex::vexterDataFormat[0] == 1 );

	BOOST_REQUIRE( core::Min( sa, sb ) == sa );
	BOOST_REQUIRE_CLOSE( core::Min( fa, fb ), fa, core::CLOSE_TO_ZERO_F32 );
	BOOST_REQUIRE( core::Min( sa, sb, sc ) == sa );
	BOOST_REQUIRE_CLOSE( core::Min( fa, fb, fc ), fa, core::CLOSE_TO_ZERO_F32 );
}

//test：DreMath - function Max
BOOST_AUTO_TEST_CASE( c_Max )
{
	BOOST_REQUIRE( core::Max( sa, sb ) == sb );
	BOOST_REQUIRE_CLOSE( core::Max( fa, fb ), fb, core::CLOSE_TO_ZERO_F32 );
	BOOST_REQUIRE( core::Max( sa, sb, sc ) == sc );
	BOOST_REQUIRE_CLOSE( core::Max( fa, fb, fc ), fc, core::CLOSE_TO_ZERO_F32 );
}

//test：DreMath - function Swap
BOOST_AUTO_TEST_CASE( c_Swap )
{
	s32 a = sa, b = sb;
	f32 a1 = fa, b1 = fb;
	
	core::Swap( a, b );
	BOOST_REQUIRE( a == sb );
	BOOST_REQUIRE( b == sa );

	core::Swap( a1, b1 );
	BOOST_REQUIRE_CLOSE( a1, fb, core::CLOSE_TO_ZERO_F32 );
	BOOST_REQUIRE_CLOSE( b1, fa, core::CLOSE_TO_ZERO_F32 );
}

BOOST_AUTO_TEST_CASE( c_Abs )
{
	BOOST_REQUIRE( core::Abs( sa ) == -sa );
	BOOST_REQUIRE_CLOSE( core::Abs( fa ), -fa, core::CLOSE_TO_ZERO_F32 );
}

BOOST_AUTO_TEST_CASE( c_Lerp )
{
	s32 a = 1, b = -1;
	BOOST_REQUIRE( core::Lerp( a, b, 0.5f ) == 0 );

	f32 a1 = 1.0f, b1 = -0.5f;
	BOOST_REQUIRE_CLOSE( core::Lerp( a1, b1, 0.5f ), 0.25f, core::CLOSE_TO_ZERO_F32 );
}

BOOST_AUTO_TEST_CASE( c_Clamp )
{
	BOOST_REQUIRE( core::Clamp( sb, sa, sc ) == sb );
	BOOST_REQUIRE_CLOSE( core::Clamp( fa, fb, fc ), fb, core::CLOSE_TO_ZERO_F32 );
}

BOOST_AUTO_TEST_CASE( c_Equal )
{
	BOOST_REQUIRE( core::Equal( fa, core::MIN_F32 ) );
	BOOST_REQUIRE( !core::Equal( fa, core::MAX_F32 ) );
}

BOOST_AUTO_TEST_CASE( c_Rand_U32 )
{
	u32 test[10];
	for(u32 i = 0; i < 10; ++ i )
	{
		core::Srand(i);
		test[i] = core::Rand_U32();
	}

	//十个数值内随机数不重复
	for( u32 i = 0; i < 10; ++ i )
		for( u32 j = 0; j < 10; ++ j )
		{
			if( i == j )
				continue;

			BOOST_REQUIRE( test[i] != test[j] );
		}
}

BOOST_AUTO_TEST_CASE( c_Rand_F32 )
{
	f32 test[10];
	for(u32 i = 0; i < 10; ++ i )
	{
		core::Srand(i);
		test[i] = core::Rand_F32();
	}

	//十个数值内随机数不重复
	for( u32 i = 0; i < 10; ++ i )
		for( u32 j = 0; j < 10; ++ j )
		{
			if( i == j )
				continue;

			BOOST_REQUIRE( !core::Equal( test[i], test[j] ) );
		}
}

BOOST_AUTO_TEST_CASE( c_SymmetricRandom_F32 )
{
	f32 test[10];
	for(u32 i = 0; i < 10; ++ i )
	{
		core::Srand(i);
		test[i] = core::SymmetricRandom_F32();
	}

	//十个数值内随机数不重复
	for( u32 i = 0; i < 10; ++ i )
		for( u32 j = 0; j < 10; ++ j )
		{
			if( i == j )
				continue;

			BOOST_REQUIRE( !core::Equal( test[i], test[j] ) );
		}
}

BOOST_AUTO_TEST_CASE( c_Sqrt )
{
	f32 a = 4.0;
	BOOST_REQUIRE_CLOSE( core::Sqrt( a ), 2.0f, core::CLOSE_TO_ZERO_F32 );
}

BOOST_AUTO_TEST_CASE( c_IsPowerOf2 )
{
	u32 a = 2, b = 1;
	BOOST_REQUIRE( core::IsPowerOf2(a) );
	BOOST_REQUIRE( core::IsPowerOf2(b) );
}

BOOST_AUTO_TEST_CASE( c_FastLog )
{
	u32 a = 4;
	BOOST_REQUIRE( core::FastLog(a) == 2 );
}

BOOST_AUTO_TEST_CASE( c_FastInvSqrt )
{
	f32 a = 4.0f;
	BOOST_REQUIRE( 0.5f - core::FAST_MATH_CLOSE_TO_ZERO_F32 <= core::FastInvSqrt(a) &&
		0.5 + core::FAST_MATH_CLOSE_TO_ZERO_F32 >= core::FastInvSqrt(a) );
}

BOOST_AUTO_TEST_CASE( c_FastSqrt )
{
	f32 a = 4.0f;
	BOOST_REQUIRE( 2.0f - core::FAST_MATH_CLOSE_TO_ZERO_F32 <= core::FastSqrt(a) &&
		2.0f + core::FAST_MATH_CLOSE_TO_ZERO_F32 >= core::FastSqrt(a) );
}

BOOST_AUTO_TEST_SUITE_END()

#endif	//	 end __DREMATH_TEST_H__