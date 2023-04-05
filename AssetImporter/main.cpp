#include <iostream>
#include "Serialization/BinaryFileSerialization.h"
#include <Systems/Log/LogSystem.h>
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

	TestPackage() {}
	TestPackage(int a, float b, long c, double d, InPackage i) : aaa(a), bbb(b), ccc(c), ddd(d), in(i) {}

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		SERIALIZE(aaa);
		SERIALIZE(bbb);
		SERIALIZE(ccc);
		SERIALIZE(ddd);
		SERIALIZE(in);
	}
};

int main()
{
	LogMessage("Begin");

	TestPackage A = TestPackage(123, 456, 78, 999, InPackage(321, 654, 987));
	BINARY_FILE_SERIALIZE_WRITE(A, "111.bin");

	TestPackage B;
	BINARY_FILE_SERIALIZE_READ(B, "111.bin");

	LogMessage("End");
	return 0;
}