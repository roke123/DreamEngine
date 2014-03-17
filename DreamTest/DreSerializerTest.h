#ifndef __DRESERIALIZERTEST_H__
#define __DRESERIALIZERTEST_H__

#include <cppunit\extensions\HelperMacros.h>

#include <DreSerializer.h>
#include <DreReadBuffer.h>
#include <DreWriteBuffer.h>
#include <DreDataBufferFactory.h>
using namespace dream;

class DreSerializerTest : public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE(DreSerializerTest);
	CPPUNIT_TEST(SerializablePODTest);
	CPPUNIT_TEST(SerializableSmartArrayTest);
	CPPUNIT_TEST(SerializableArrayTest);
	CPPUNIT_TEST(SerializableCharStrTest);
	CPPUNIT_TEST(SerializableStringStrTest);
	CPPUNIT_TEST(SerializableClassTest);
	CPPUNIT_TEST_SUITE_END();

public:
	class SerializableTest : public Serializable
	{
	public:
		SerializableTest()
		{
			// Áô¿Õ
		}

		bool operator == (const SerializableTest& rh)
		{
			return s == rh.s;
		}

		void init()
		{
			s = "sdfdfsdfd";
		}

		void Serialize(Serializer& serializer) const override
		{
			serializer.SerializeString(s);
		}

		SerializablePtr Deserialze(Serializer& serializer) override
		{
			shared_ptr<SerializableTest> ret(new SerializableTest);
			serializer.DeserializeString(ret->s);
			return ret;
		}

	private:
		string s;
	};

	DreSerializerTest() : buffer(1024)
	{
		reader = DataBufferFactory::CreateMemoryReadBuffer(buffer, buffer->size());
		writer = DataBufferFactory::CreateMemoryWriteBuffer(buffer, buffer->size());
	}

	void SerializablePODTest()
	{
		Serializer serializer("", "", reader, writer);

		int a = 10, b = 100;
		serializer.SerializePOD(a);
		serializer.DeserializePOD(&b);
		CPPUNIT_ASSERT(a == b);
	}

	void SerializableSmartArrayTest()
	{
		Serializer serializer("", "", reader, writer);

		u32Array a(5, 55);
		u32Array b(5, 4);

		serializer.SerializeArray(a, 5);
		serializer.DeserializeArray(b, 5);

		CPPUNIT_ASSERT(a[0] == b[0]);
		CPPUNIT_ASSERT(a[1] == b[1]);
		CPPUNIT_ASSERT(a[2] == b[2]);
		CPPUNIT_ASSERT(a[3] == b[3]);
		CPPUNIT_ASSERT(a[4] == b[4]);
	}

	void SerializableArrayTest()
	{
		Serializer serializer("", "", reader, writer);

		int a[5] = {0, 156, 12, 78, 599859};
		int b[5] = {464, 88, 669, 225, 555};
		serializer.SerializeArray(a, 5);
		serializer.DeserializeArray(b, 5);

		CPPUNIT_ASSERT(a[0] == b[0]);
		CPPUNIT_ASSERT(a[1] == b[1]);
		CPPUNIT_ASSERT(a[2] == b[2]);
		CPPUNIT_ASSERT(a[3] == b[3]);
		CPPUNIT_ASSERT(a[4] == b[4]);
	}

	void SerializableCharStrTest()
	{
		Serializer serializer("", "", reader, writer);

		const char* a = "fsdfjisdjfsdoijf";
		char* b = new char[strlen(a) + 1];
		serializer.SerializeString(a);
		serializer.DeserializeString(b);

		CPPUNIT_ASSERT(strcmp(a, b) == 0);
	}

	void SerializableStringStrTest()
	{
		Serializer serializer("", "", reader, writer);

		string a = "fsdfjisdjfsdoijf";
		string b;;
		serializer.SerializeString(a);
		serializer.DeserializeString(b);

		CPPUNIT_ASSERT(a == b);
	}

	void SerializableClassTest()
	{
		Serializer serializer("", "", reader, writer);

		SerializableTest a;
		a.init();
		serializer.SerializeSerializable(a);
		shared_ptr<SerializableTest> b = serializer.DeserializeSerializable<SerializableTest>();

		CPPUNIT_ASSERT(a == *b);
	}

private:
	u8Array buffer;

	ReadBufferPtr	reader;
	WriteBufferPtr	writer;

};	// end class SerializerTest

#endif	// end __DRESERIALIZERTEST_H__