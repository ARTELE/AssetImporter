#include <iostream>
#include "Serialization/BinaryFileSerialization.h"
#include <Modules/Log/Log.h>
using namespace std;

struct InPackage
{
	InPackage() {}
	InPackage(int e, float f, double g) : eee(e), fff(f), ggg(g) {}
	int eee;
	float fff;
	double ggg;

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		SERIALIZE(eee);
		SERIALIZE(fff);
		SERIALIZE(ggg);
	}
};

struct TestPackage
{
	int aaa = 0;
	float bbb = 0;
	long ccc = 0;
	double ddd = 0;
	InPackage in;
	char* hhh = nullptr;
	SystemAllocator allocator;

	TestPackage() {}
	TestPackage(int a, float b, long c, double d, InPackage i) : aaa(a), bbb(b), ccc(c), ddd(d), in(i) {}

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		serializer.SetUserAllocator(&allocator);
		SERIALIZE(aaa);
		SERIALIZE(bbb);
		SERIALIZE(ccc);
		SERIALIZE(ddd);
		SERIALIZE(in);
		SERIALIZE_PTR(hhh, 16);
	}
};

int main()
{
	LogMessage("Begin");

	SystemAllocator allocator;
	TestPackage A = TestPackage(123, 456, 78, 999, InPackage(321, 654, 987));
	A.hhh = allocator.AllocateArray<char>(16);
	strcpy(A.hhh, "qwertyuiop");
	BINARY_FILE_SERIALIZE_WRITE(A, "111.bin");

	TestPackage B;
	BINARY_FILE_SERIALIZE_READ(B, "111.bin");

	LogMessage("End");
	return 0;
}