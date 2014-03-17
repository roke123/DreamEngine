#ifndef __DRESERIALIZER_H__
#define __DRESERIALIZER_H__

#include "DreIOSystemDeclaration.h"

#include "DreWriteBuffer.h"
#include "DreReadBuffer.h"

namespace dream
{
	class Serializable
	{
	public:
		/** 序列化函数
		*/
		virtual void Serialize(Serializer& serializer) const = 0;

		/** 反序列化函数
		*/
		virtual SerializablePtr Deserialze(Serializer& serializer) = 0;
	};	// end class Serializable

	class Serializer
	{
	private:
		class SerializerNameCmp
		{
		public:
			bool operator() (const Serializer* lh, const Serializer* rh)
			{
				return lh->GetSerializerName().compare(rh->GetSerializerName()) != 0;
			}
		};	// end ckass SerializerNameCmp

	public:
		/** 构造函数
		*/
		Serializer(const string& type, const string& version, ReadBufferPtr reader, WriteBufferPtr writer)
			: mType(type), mVersion(version), mReader(reader), mWriter(writer)
		{
			// 留空
		}

	public:
		/** 虚析构函数
		*/
		virtual ~Serializer() {};

		/** 取序列化器名称
		* @return	返回mType + mVersion
		*/
		const string GetSerializerName() const { return mType + mVersion; }

		/** 取序列化器类型
		*/
		const string GetSerializerType() const { return mType; }

		/** 取序列化器版本号
		*/
		const string GetSerializerVersion() const { return mVersion; }

//-------------------------------------------------- 序列化函数 --------------------------------------------------------//
		/** 序列化数据函数(对于pod类型)
		*/
		template<class T> 
		void SerializePOD(const T value) { SerializePOD(value, std::is_pod<T>()); }; 		
		template<class T>
		void SerializePOD(const T value, std::true_type)
		{
			mWriter->Write((u8*)&value, sizeof(T));
		}

		/** 序列化数据函数(对于数组类型)
		*/
		template<class T>
		void SerializeArray(const T* value, u32 numOfElement)
		{
			mWriter->Write((const u8*)value, sizeof(T) * numOfElement);
		}

		/** 序列化数据函数(对于智能数组类型)
		*/
		template<class T>
		void SerializeArray(const shared_array<T>& value, u32 numOfElement)
		{
			mWriter->Write((const u8*)&value[0], sizeof(T) * numOfElement);
		}

		/** 序列化数据函数(对于string类型)
		*/
		void SerializeString(const string& value)
		{
			u32 length = value.size();
			mWriter->Write((u8*)&length, sizeof(u32));
			mWriter->Write((const u8*)value.c_str(), strlen(value.c_str()));
		}

		/** 序列化数据函数(对于字符串类型)
		*/
		void SerializeString(const char* value)
		{
			u32 length = strlen(value);
			mWriter->Write((u8*)&length, sizeof(u32));
			mWriter->Write((const u8*)value, length);
		}

		/** 序列化数据函数(对于继承Serializable接口类型)
		*/
		void SerializeSerializable(const Serializable& value)
		{
			value.Serialize(*this);
		}

//-------------------------------------------------- 反序列化函数 --------------------------------------------------------//
		
		/** 反序列化数据函数(对于pod类型)
		*/
		template<class T>
		void DeserializePOD(T* value) { DeserializePOD(value, std::is_pod<T>());}
		template<class T>
		void DeserializePOD(T* value, std::true_type)
		{
			DreAssert(value != nullptr, "输入数据不能为空");

			mReader->Read((u8*)value, sizeof(T));
		}

		/** 反序列化数据函数(对于数组类型)
		*/
		template<class T>
		void DeserializeArray(T* value, u32 numOfElement)
		{
			DreAssert(value != nullptr, "输入数据不能为空");

			mReader->Read((u8*)value, sizeof(T) * numOfElement);
		}

		/** 反序列化数据函数(对于智能数组类型)
		*/
		template<class T>
		void DeserializeArray(shared_array<T>& value, u32 numOfElement)
		{
			DreAssert(value != nullptr, "输入数据不能为空");

			mReader->Read((u8*)&value[0], sizeof(T) * numOfElement);
		}
		
		/** 反序列化数据函数(对于string类型)
		*/
		void DeserializeString(string& value)
		{
			u32 length = 0;
			this->DeserializePOD(&length);
			u8Array buf(length + 1);
			u32 readLength = mReader->Read(buf, length);
			DreAssert(length == readLength, "反序列化发生异常");
			buf[length] = '\0';
			value += (c8*)&buf[0];
		}

		/** 反序列化数据函数(对于字符串类型)
		*/
		void DeserializeString(char*& value)
		{
			DreAssert(value != nullptr, "输入数据不能为空");

			u32 length = 0;
			this->DeserializePOD(&length);
			value = new c8[length + 1];
			u32 readLength = mReader->Read((u8*)value, length);
			DreAssert(length == readLength, "反序列化发生异常");
			value[length] = '\0';
		}

		/** 反序列化数据函数(对于继承Serializable接口类型)
		*/
		template<class T>
		shared_ptr<T> DeserializeSerializable() { return DeserializeSerializable<T>(std::is_base_of<Serializable, T>(),
			std::has_default_constructor<T>()); }
		template<class T>
		shared_ptr<T> DeserializeSerializable(std::true_type, std::true_type)
		{
			SerializablePtr serializable(new T());
			return dynamic_pointer_cast<T, Serializable>(serializable->Deserialze(*this));
		}
		template<class T>
		shared_ptr<T> DeserializeSerializable(std::true_type, std::false_type)
		{
			string str(typeid(T).name());
			str += "无默认构造函数，而Serializable要求必须有默认构造函数";
			DreAssert(false, str.c_str());
			return nullptr;
		}


	private:
		/// 序列化类型
		string mType;
		/// 序列化版本
		string mVersion;

		WriteBufferPtr	mWriter;

		ReadBufferPtr	mReader;

		typedef set<Serializer*, SerializerNameCmp>			SerializerSet;
		typedef	SerializerSet::iterator						SerializerIte;
		typedef	SerializerSet::const_iterator				SerializerConstIte;
		/// 序列化器集
		static SerializerSet sSerializerSet;
	};

}	// end namespace dream

#endif	// end __DRESERIALIZER_H__