#ifndef __DREATTRIBUTION_H__
#define __DREATTRIBUTION_H__

#include "DreUtility.h"
#include "DreException.h"

#include <typeinfo>

namespace dream
{

	class Attribution
	{
	public:
		/** 占位符接口
		*/
		class PlaceHolder
		{
		public:
			/** 虚析构函数，用于指针类型析构 */
			virtual ~PlaceHolder() { /** 留空 */ }

			/** 获取PlaceHolder保存的值的TypeInfo */
			virtual const type_info& GetTypeInfo() const = 0;

			/** 复制一份PlaceHolder保存值 */
			virtual PlaceHolder* Clone() const = 0;
		};

		/** 泛型占位符
		*/
		template<typename ValueType>
		class Holder : public PlaceHolder
		{
		public:
			/** 构造函数 */
			Holder(ValueType value) : mValue(value) { /** 留空 */ }

			/** 获取PlaceHolder保存的值的TypeInfo */
			virtual const type_info& GetTypeInfo() const { return typeid(ValueType); }

			/** 复制一份PlaceHolder保存值 */
			virtual PlaceHolder* Clone() const { return new Holder(mValue); }

			/** 取得保存值 */
			ValueType& Get() { return mValue; }

			/** 取得保存值 */
			const ValueType& Get() const { return mValue; }

		private:
			ValueType mValue;
		};


	public:
		/** 泛型构造函数 */
		template<typename ValueType>
		explicit Attribution(const ValueType& value) : mContent(new Holder<ValueType>(value)) { /** 留空*/ }

		/** 构造函数 */
		Attribution(const Attribution& attribution) : mContent(attribution.IsNull() ? nullptr : mContent->Clone() ) 
		{ 
			/** 留空 */
		}

		/** 析构函数 */
		virtual ~Attribution() { SafeDelete(mContent); }

		/** 判断是否空值 */
		bool IsNull() const { return mContent == nullptr; }

		/** 取值函数
		* @template param		ValueType			取值类型
		*/
		template<typename ValueType>
		ValueType Get() 
		{
			DreAssert(mContent != nullptr, "Attribution保存值为空值");
			// 检查类型是否相符
			DreAssert(typeid(ValueType) == static_cast< Holder<Valuetype>* >(mContent).GetTypeInfo(),
				"模板Attribution::Get()的类型与对象保存类型不符");

			return static_cast< Holder<Valuetype>* >(mContent).Get(); 
		}

		/** 取值函数
		* @template param		ValueType			取值类型
		*/
		template<typename ValueType>
		const ValueType Get() const 
		{ 
			DreAssert(mContent != nullptr, "Attribution保存值为空值");
			// 检查类型是否相符
			DreAssert(typeid(ValueType) == static_cast< Holder<Valuetype>* >(mContent).GetTypeInfo(),
				"模板Attribution::Get()的类型与对象保存类型不符");

			return static_cast< Holder<Valuetype>* >(mContent).Get(); 
		}

		/** 重载赋值操作符 */
		Attribution operator = (const Attribution& attribution)
		{
			if(&attribution == this)
				return *this;

			SafeDelete(mContent);
			mContent = attribution.mContent->Clone();
		}

		/** 重载赋值操作符 */
		template<typename ValueType>
		Attribution operator = (const ValueType& value)
		{
			// 检查类型是否相符
			DreAssert(typeid(ValueType) == static_cast< Holder<Valuetype>* >(mContent).GetTypeInfo(),
				"参数类型与对象保存类型不符");

			ValueType& originalValue = static_cast< Holder<Valuetype>* >(mContent).Get();
			originalValue = value;

			return *this;
		}

		/** 交换函数 */
		void Swap(Attribution& attribution)
		{
			std::swap(mContent, attribution.mContent);
		}

		/** 设置对象值为空值*/
		void SetNull() { SafeDelete(mContent);}

	private:
		PlaceHolder* mContent;
	};
}

#endif	// end of __DREATTRIBUTION_H__