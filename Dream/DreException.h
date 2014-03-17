#ifndef __DREEXCEPTION_H__
#define __DREEXCEPTION_H__

#include <exception>

#include "DreComplieConfig.h"
#include "DreContainer.h"
#include "DreTypes.h"

namespace dream
{

//------------------------------------------------ Assert 定义 ------------------------------------------------//
	DRE_EXPORT_CLASS void DreAssert_Impl(bool condition, const string& message, const char* filename, int line);

	DRE_EXPORT_CLASS void DreAssert_Impl(bool condition, const c8* message, const char* filename, int line);

#	if !defined(DreAssert)
#		if defined(_DEBUG) || defined(DEBUG)
#			define DreAssert(condition, message) DreAssert_Impl(condition, message, __FILE__,  __LINE__);
#		else
#			define DreAssert(condition, message)
#		endif
#	endif

//------------------------------------------------ Exception 定义 ------------------------------------------------//
	enum DRE_EXCEPTION_CODE
	{
        DRE_EXCEPTION_IO,
        DRE_EXCEPTION_INVALID_STATE,
        DRE_EXCEPTION_INVALID_PARAMS,
        DRE_EXCEPTION_RENDERINGAPI_ERROR,
        DRE_EXCEPTION_DUPLICATE_ITEM,
        DRE_EXCEPTION_ITEM_NOT_FOUND,
        DRE_EXCEPTION_FILE_NOT_FOUND,
        DRE_EXCEPTION_INTERNAL_ERROR,
        DRE_EXCEPTION_RT_ASSERTION_FAILED, 
		DRE_EXCEPTION_NOT_IMPLEMENTED,
		DRE_EXCEPTION_OUT_OF_MEMORY,
    };

	/** 用于把异常代码通过模板转换为C++类型
	* @note 常用于需要根据具体enum调用函数，把运行期
	*		的值识别转换为编译器的类型识别
	*/
	template <int num>
	struct ExceptionCodeType
	{
		enum { number = num };
	};

	/**	转换异常代码到异常类型
	*/
	class ExceptionType
	{
	public:
		/** 返回异常码DRE_EXCEPTION_CANNOT_WRITE_TO_FILE的异常类型
		*/
		static string Get(ExceptionCodeType<DRE_EXCEPTION_IO> type)
		{
			return "IOException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_INVALID_STATE> type)
		{
			return "InvalidStateException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_INVALID_PARAMS> type)
		{
			return "InvalidParamsException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_RENDERINGAPI_ERROR> type)
		{
			return "RenderingAPIErrorException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_DUPLICATE_ITEM> type)
		{
			return "DuplicateItemException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_ITEM_NOT_FOUND> type)
		{
			return "ItemNotFoundException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_FILE_NOT_FOUND> type)
		{
			return "FileNotFoundException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_INTERNAL_ERROR> type)
		{
			return "InternalErrorException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_RT_ASSERTION_FAILED> type)
		{
			return "RTAssertionFailedException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_NOT_IMPLEMENTED> type)
		{
			return "NotImplementedException";
		}
		static string Get(ExceptionCodeType<DRE_EXCEPTION_OUT_OF_MEMORY> type)
		{
			return "OutOfMemory";
		}
	};

	/// 取异常类型宏
#	define GetExceptionType(code) ExceptionType::Get(ExceptionCodeType<code>());

	class Exception : public std::exception
	{
	private:
		/// 异常代码
		DRE_EXCEPTION_CODE mExceptionCode;
		/// 发生异常的函数
		string mSource;
		/// 关于异常的描述
		string mDescription;
		/// 发生异常的文件名
		string mFile;
		/// 发生异常的文件行
		u32 mLine;
		/// 返回的详细异常信息
		mutable string mFullDescription;

	public:
		/** 构造函数
		*/
		Exception( u32 exceptionCode, const string& description, const string& source,
			const char* file, long line ) :
					mExceptionCode(static_cast<DRE_EXCEPTION_CODE>(exceptionCode)), mDescription(description), mSource(source),
					mFile(file), mLine(line)
		{
		}

		/// 虚析构函数
		~Exception() {}

        /** 返回详细异常信息
        */
		const string& GetFullDescription(void) const { return mFullDescription; }

        /** 返回异常代码
        */
		DRE_EXCEPTION_CODE GetExceptionCode(void) const { return mExceptionCode; }

        /** 返回异常发生源
        */
		const string& GetSource() const { return mSource; }

        /** 返回异常发生文件
        */
        const string& GetFile() const { return mFile; }

        /** 返回异常发生行数
        */
        long GetLine() const { return mLine; }

		/** 返回异常描述
        */
		const string& GetDescription(void) const { return mDescription; }

		/*** 重载std::exception::what
		*/
		const c8* what() const { return GetFullDescription().c_str(); }

	};	// end class Exception

	class UnimplementedException : public Exception 
	{
	public:
		UnimplementedException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class FileNotFoundException : public Exception
	{
	public:
		FileNotFoundException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class IOException : public Exception
	{
	public:
		IOException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class InvalidStateException : public Exception
	{
	public:
		InvalidStateException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class InvalidParametersException : public Exception
	{
	public:
		InvalidParametersException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class ItemIdentityException : public Exception
	{
	public:
		ItemIdentityException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class InternalErrorException : public Exception
	{
	public:
		InternalErrorException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class RenderingAPIException : public Exception
	{
	public:
		RenderingAPIException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class RuntimeAssertionException : public Exception
	{
	public:
		RuntimeAssertionException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};
	class OutOfMemoryException : public Exception
	{
	public:
		OutOfMemoryException(u32 exceptionCode, const string& inDescription, const string& inSource,
			const char* inFile, long inLine)
			: Exception(exceptionCode, inDescription, inSource, inFile, inLine) {}
	};

	/** 异常工厂
	*/
	class DRE_EXPORT_CLASS ExceptionFactory
	{
	public:
		static UnimplementedException create(
			ExceptionCodeType<DRE_EXCEPTION_NOT_IMPLEMENTED> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return UnimplementedException(code.number, desc, src, file, line);
		}
		static FileNotFoundException create(
			ExceptionCodeType<DRE_EXCEPTION_FILE_NOT_FOUND> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return FileNotFoundException(code.number, desc, src, file, line);
		}
		static IOException create(
			ExceptionCodeType<DRE_EXCEPTION_IO> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return IOException(code.number, desc, src, file, line);
		}
		static InvalidStateException create(
			ExceptionCodeType<DRE_EXCEPTION_INVALID_STATE> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return InvalidStateException(code.number, desc, src, file, line);
		}
		static InvalidParametersException create(
			ExceptionCodeType<DRE_EXCEPTION_INVALID_PARAMS> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return InvalidParametersException(code.number, desc, src, file, line);
		}
		static ItemIdentityException create(
			ExceptionCodeType<DRE_EXCEPTION_ITEM_NOT_FOUND> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return ItemIdentityException(code.number, desc, src, file, line);
		}
		static ItemIdentityException create(
			ExceptionCodeType<DRE_EXCEPTION_DUPLICATE_ITEM> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return ItemIdentityException(code.number, desc, src, file, line);
		}
		static InternalErrorException create(
			ExceptionCodeType<DRE_EXCEPTION_INTERNAL_ERROR> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return InternalErrorException(code.number, desc, src, file, line);
		}
		static RenderingAPIException create(
			ExceptionCodeType<DRE_EXCEPTION_RENDERINGAPI_ERROR> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return RenderingAPIException(code.number, desc, src, file, line);
		}
		static RuntimeAssertionException create(
			ExceptionCodeType<DRE_EXCEPTION_RT_ASSERTION_FAILED> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return RuntimeAssertionException(code.number, desc, src, file, line);
		}
		static OutOfMemoryException create(
			ExceptionCodeType<DRE_EXCEPTION_OUT_OF_MEMORY> code, 
			const string& desc, 
			const string& src, const char* file, long line)
		{
			return OutOfMemoryException(code.number, desc, src, file, line);
		}

	};

#	ifndef DRE_EXCEPT
#		define DRE_EXCEPT(code, desc, src) throw ExceptionFactory::create( \
			ExceptionCodeType<code>(), desc, src, __FILE__, __LINE__ );
#	endif

}	// end namespace dream

#endif	// end __DREEXCEPTION_H__