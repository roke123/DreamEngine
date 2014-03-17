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
		/** ���л�����
		*/
		virtual void Serialize(Serializer& serializer) const = 0;

		/** �����л�����
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
		/** ���캯��
		*/
		Serializer(const string& type, const string& version, ReadBufferPtr reader, WriteBufferPtr writer)
			: mType(type), mVersion(version), mReader(reader), mWriter(writer)
		{
			// ����
		}

	public:
		/** ����������
		*/
		virtual ~Serializer() {};

		/** ȡ���л�������
		* @return	����mType + mVersion
		*/
		const string GetSerializerName() const { return mType + mVersion; }

		/** ȡ���л�������
		*/
		const string GetSerializerType() const { return mType; }

		/** ȡ���л����汾��
		*/
		const string GetSerializerVersion() const { return mVersion; }

//-------------------------------------------------- ���л����� --------------------------------------------------------//
		/** ���л����ݺ���(����pod����)
		*/
		template<class T> 
		void SerializePOD(const T value) { SerializePOD(value, std::is_pod<T>()); }; 		
		template<class T>
		void SerializePOD(const T value, std::true_type)
		{
			mWriter->Write((u8*)&value, sizeof(T));
		}

		/** ���л����ݺ���(������������)
		*/
		template<class T>
		void SerializeArray(const T* value, u32 numOfElement)
		{
			mWriter->Write((const u8*)value, sizeof(T) * numOfElement);
		}

		/** ���л����ݺ���(����������������)
		*/
		template<class T>
		void SerializeArray(const shared_array<T>& value, u32 numOfElement)
		{
			mWriter->Write((const u8*)&value[0], sizeof(T) * numOfElement);
		}

		/** ���л����ݺ���(����string����)
		*/
		void SerializeString(const string& value)
		{
			u32 length = value.size();
			mWriter->Write((u8*)&length, sizeof(u32));
			mWriter->Write((const u8*)value.c_str(), strlen(value.c_str()));
		}

		/** ���л����ݺ���(�����ַ�������)
		*/
		void SerializeString(const char* value)
		{
			u32 length = strlen(value);
			mWriter->Write((u8*)&length, sizeof(u32));
			mWriter->Write((const u8*)value, length);
		}

		/** ���л����ݺ���(���ڼ̳�Serializable�ӿ�����)
		*/
		void SerializeSerializable(const Serializable& value)
		{
			value.Serialize(*this);
		}

//-------------------------------------------------- �����л����� --------------------------------------------------------//
		
		/** �����л����ݺ���(����pod����)
		*/
		template<class T>
		void DeserializePOD(T* value) { DeserializePOD(value, std::is_pod<T>());}
		template<class T>
		void DeserializePOD(T* value, std::true_type)
		{
			DreAssert(value != nullptr, "�������ݲ���Ϊ��");

			mReader->Read((u8*)value, sizeof(T));
		}

		/** �����л����ݺ���(������������)
		*/
		template<class T>
		void DeserializeArray(T* value, u32 numOfElement)
		{
			DreAssert(value != nullptr, "�������ݲ���Ϊ��");

			mReader->Read((u8*)value, sizeof(T) * numOfElement);
		}

		/** �����л����ݺ���(����������������)
		*/
		template<class T>
		void DeserializeArray(shared_array<T>& value, u32 numOfElement)
		{
			DreAssert(value != nullptr, "�������ݲ���Ϊ��");

			mReader->Read((u8*)&value[0], sizeof(T) * numOfElement);
		}
		
		/** �����л����ݺ���(����string����)
		*/
		void DeserializeString(string& value)
		{
			u32 length = 0;
			this->DeserializePOD(&length);
			u8Array buf(length + 1);
			u32 readLength = mReader->Read(buf, length);
			DreAssert(length == readLength, "�����л������쳣");
			buf[length] = '\0';
			value += (c8*)&buf[0];
		}

		/** �����л����ݺ���(�����ַ�������)
		*/
		void DeserializeString(char*& value)
		{
			DreAssert(value != nullptr, "�������ݲ���Ϊ��");

			u32 length = 0;
			this->DeserializePOD(&length);
			value = new c8[length + 1];
			u32 readLength = mReader->Read((u8*)value, length);
			DreAssert(length == readLength, "�����л������쳣");
			value[length] = '\0';
		}

		/** �����л����ݺ���(���ڼ̳�Serializable�ӿ�����)
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
			str += "��Ĭ�Ϲ��캯������SerializableҪ�������Ĭ�Ϲ��캯��";
			DreAssert(false, str.c_str());
			return nullptr;
		}


	private:
		/// ���л�����
		string mType;
		/// ���л��汾
		string mVersion;

		WriteBufferPtr	mWriter;

		ReadBufferPtr	mReader;

		typedef set<Serializer*, SerializerNameCmp>			SerializerSet;
		typedef	SerializerSet::iterator						SerializerIte;
		typedef	SerializerSet::const_iterator				SerializerConstIte;
		/// ���л�����
		static SerializerSet sSerializerSet;
	};

}	// end namespace dream

#endif	// end __DRESERIALIZER_H__