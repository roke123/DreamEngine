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
		/** ռλ���ӿ�
		*/
		class PlaceHolder
		{
		public:
			/** ����������������ָ���������� */
			virtual ~PlaceHolder() { /** ���� */ }

			/** ��ȡPlaceHolder�����ֵ��TypeInfo */
			virtual const type_info& GetTypeInfo() const = 0;

			/** ����һ��PlaceHolder����ֵ */
			virtual PlaceHolder* Clone() const = 0;
		};

		/** ����ռλ��
		*/
		template<typename ValueType>
		class Holder : public PlaceHolder
		{
		public:
			/** ���캯�� */
			Holder(ValueType value) : mValue(value) { /** ���� */ }

			/** ��ȡPlaceHolder�����ֵ��TypeInfo */
			virtual const type_info& GetTypeInfo() const { return typeid(ValueType); }

			/** ����һ��PlaceHolder����ֵ */
			virtual PlaceHolder* Clone() const { return new Holder(mValue); }

			/** ȡ�ñ���ֵ */
			ValueType& Get() { return mValue; }

			/** ȡ�ñ���ֵ */
			const ValueType& Get() const { return mValue; }

		private:
			ValueType mValue;
		};


	public:
		/** ���͹��캯�� */
		template<typename ValueType>
		explicit Attribution(const ValueType& value) : mContent(new Holder<ValueType>(value)) { /** ����*/ }

		/** ���캯�� */
		Attribution(const Attribution& attribution) : mContent(attribution.IsNull() ? nullptr : mContent->Clone() ) 
		{ 
			/** ���� */
		}

		/** �������� */
		virtual ~Attribution() { SafeDelete(mContent); }

		/** �ж��Ƿ��ֵ */
		bool IsNull() const { return mContent == nullptr; }

		/** ȡֵ����
		* @template param		ValueType			ȡֵ����
		*/
		template<typename ValueType>
		ValueType Get() 
		{
			DreAssert(mContent != nullptr, "Attribution����ֵΪ��ֵ");
			// ��������Ƿ����
			DreAssert(typeid(ValueType) == static_cast< Holder<Valuetype>* >(mContent).GetTypeInfo(),
				"ģ��Attribution::Get()����������󱣴����Ͳ���");

			return static_cast< Holder<Valuetype>* >(mContent).Get(); 
		}

		/** ȡֵ����
		* @template param		ValueType			ȡֵ����
		*/
		template<typename ValueType>
		const ValueType Get() const 
		{ 
			DreAssert(mContent != nullptr, "Attribution����ֵΪ��ֵ");
			// ��������Ƿ����
			DreAssert(typeid(ValueType) == static_cast< Holder<Valuetype>* >(mContent).GetTypeInfo(),
				"ģ��Attribution::Get()����������󱣴����Ͳ���");

			return static_cast< Holder<Valuetype>* >(mContent).Get(); 
		}

		/** ���ظ�ֵ������ */
		Attribution operator = (const Attribution& attribution)
		{
			if(&attribution == this)
				return *this;

			SafeDelete(mContent);
			mContent = attribution.mContent->Clone();
		}

		/** ���ظ�ֵ������ */
		template<typename ValueType>
		Attribution operator = (const ValueType& value)
		{
			// ��������Ƿ����
			DreAssert(typeid(ValueType) == static_cast< Holder<Valuetype>* >(mContent).GetTypeInfo(),
				"������������󱣴����Ͳ���");

			ValueType& originalValue = static_cast< Holder<Valuetype>* >(mContent).Get();
			originalValue = value;

			return *this;
		}

		/** �������� */
		void Swap(Attribution& attribution)
		{
			std::swap(mContent, attribution.mContent);
		}

		/** ���ö���ֵΪ��ֵ*/
		void SetNull() { SafeDelete(mContent);}

	private:
		PlaceHolder* mContent;
	};
}

#endif	// end of __DREATTRIBUTION_H__