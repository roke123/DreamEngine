#ifndef __DRE_COMPILE_CONFIG_H__
#define __DRE_COMPILE_CONFIG_H__

//�汾�ź�
#define DREAM_VERSION_MAJOR 1
#define DREAM_VERSION_MINOR 0
#define DREAM_VERSION_REVISION 0

// SVN�����
#define DREAM_VERSION_SVN -beta
#define DREAM_SDK_VERSION "1.0.0-beta"

#define DRE_ENDIAN_BIG 0
#define DRE_ENDIAN_LITTLE 1
// �ձ���ɫʹ��little endian�����������ɵ�λ��ʼ��RGB = B8G8R8��
// @note DirectX11ʹ��big endian����
#ifdef DRE_USE_ENDIAN_BIG
	#define	DRE_ENDIAN DRE_ENDIAN_BIG
#else
	#define DRE_ENDIAN DRE_ENDIAN_LITTLE
#endif	

#ifndef _USRDLL
	#define DRE_EXPORT_CLASS					__declspec(dllimport)
	#define DRE_EXPORT_CLASS_TEMPLATE			
#else
	#define DRE_EXPORT_CLASS					__declspec(dllexport)
	#define DRE_EXPORT_CLASS_TEMPLATE			__declspec(dllexport)
#endif

#define OPEN_FLOAT_OP	1		// define this to enable safety asserts, useful for debugging
#define C99				0		// define this if you want to use C99 stuff (although you need to fix other C++ code below, like iostreams)
#define _SIGNED_SHIFT	1		// define this if bitshift of signed ints preserves sign - implementation defined

/// �������Ժ�
#define DREAM_DEBUG		0
#if defined(DEBUG) || defined(_DEBUG)
	#define DREAM_DEBUG		1
#endif

// ���þ���
#if defined(_MSC_VER)
	#pragma warning(disable:4507)
	#if _MSC_VER > 1700
		#pragma warning(disable:4005)
	#endif
#endif


#include <cstdio>	//�����ͷ�ļ�

#endif // __IRR_COMPILE_CONFIG_H__

