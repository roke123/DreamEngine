#ifndef __DRETYPES_H__
#define __DRETYPES_H__


#include <memory>
#include <functional>

#include "DreContainer.h"

namespace dream
{

using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;
using std::make_shared;

template<class T>
class shared_array : public std::shared_ptr<vector<T>>
{
public:
	shared_array() :
	//-----------------------------------------------------
	std::shared_ptr<vector<T>>(nullptr)
	{
		// 留空
	}

	shared_array(size_t size) :
	//-----------------------------------------------------
	std::shared_ptr<vector<T>>(new vector<T>(size))
	{
		// 留空
	}
	
	shared_array(size_t size, T value) :
	//------------------------------------------------------
	std::shared_ptr<vector<T>>(new vector<T>(size, value))
	{
		// 留空
	}

	T& operator [] (size_t index)
	{
		return (*(*this))[index];
	}

	const T& operator [] (size_t index) const
	{
		return (*(*this))[index];
	}

};

typedef	unsigned char				u8;
typedef shared_array<u8>			u8Array;

typedef	signed char					s8;
typedef shared_array<s8>			s8Array;

typedef char						c8;
typedef shared_array<c8>			c8Array;

typedef unsigned short				u16;
typedef shared_array<u16>			u16Array;

//实际上signed short等同于short
typedef signed short				s16;
typedef shared_array<s16>			s16Array;

typedef unsigned int				u32;
typedef shared_array<u32>			u32Array;

typedef signed int					s32;
typedef shared_array<s32>			s32Array;

typedef float						f32;
typedef shared_array<f32>			f32Array;

typedef double						d32;
typedef shared_array<d32>			d32Array;



}	// end namespace dream

#include <wchar.h>
//s{w,n}printf的函数在windowAPI和ISO C里是不一样的，因为要实现跨平台时必须注意
#if defined(_MSC_VER) && _MSC_VER > 1310 && !defined (_WIN32_WCE)
//#define swprintf swprintf_s
//#define snprintf sprintf_s
#else
#define swprintf _snwprintf
#define snprintf _snprintf
#endif

// 用于检测内存泄露
#if defined(_DEBUG) && defined(DREAM_EXPORTS) && defined(_MSC_VER) && \
	(_MSC_VER > 1299) && !defined(_DRE_DONT_DO_MEMORY_DEBUGGING_HERE)

	#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
	#include <stdlib.h>
	#include <crtdbg.h>
	#define new DEBUG_CLIENTBLOCK
#endif

//Assert
#if defined(_DEBUG)
	// 是否使用WINDOWS_API
	#if defined(_DRE_WINDOWS_API_) && defined(_MSC_VER) && !defined (_WIN32_WCE)
		#if defined(WIN64) || defined(_WIN64) // using portable common solution for x64 configuration
		#include <crtdbg.h>
		#define Assert( _CONDITION_ ) if (_CONDITION_) {_CrtDbgBreak();}
		#else
		#define Assert( _CONDITION_ ) if (_CONDITION_) {_asm int 3}
		#endif
	#else	// else 
		#include "assert.h"
		#define Assert( _CONDITION_ ) assert( !(_CONDITION_) );
	#endif
#else
	#define Assert( _CONDITION_ )
#endif

//复制于irrlicht，用于应对VS6.0里没有wchar_t的定义
#ifdef _MSC_VER
#ifndef _WCHAR_T_DEFINED
// A 16 bit wide character type.
/**
	Defines the wchar_t-type.
	In VS6, its not possible to tell
	the standard compiler to treat wchar_t as a built-in type, and
	sometimes we just don't want to include the huge stdlib.h or wchar.h,
	so we'll use this.
*/
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif // wchar is not defined
#endif // microsoft compiler

typedef wchar_t c16;

//复制于irrlicht，用于导出标记的警告
#if defined(IGNORE_DEPRECATED_WARNING)
#define _IRR_DEPRECATED_
#elif _MSC_VER >= 1310 //vs 2003 or higher
#define _DRE_DEPRECATED_ __declspec(deprecated)
#elif (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)) // all versions above 3.0 should support this feature
#define _DRE_DEPRECATED_  __attribute__ ((deprecated))
#else
#define _DRE_DEPRECATED_
#endif

//复制于irrlicht，用于解决微软编译器错误
//Compiler version defines: VC6.0 : 1200, VC7.0 : 1300, VC7.1 : 1310, VC8.0 : 1400*/
#if defined(_IRR_WINDOWS_API_) && defined(_MSC_VER) && (_MSC_VER > 1299) && (_MSC_VER < 1400)
#define _DRE_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX __asm mov eax,100
#else
#define _DRE_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX
#endif // _IRR_MANAGED_MARSHALLING_BUGFIX

#endif	!__DRETYPES_H__
