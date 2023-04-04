#include <iostream>
#include "Serialization/BinaryFileSerialization.h"
using namespace std;

struct TestA
{
	int aaa = 0x12345678;
	float bbb = 1;
	long ccc = 2;
	double ddd = 3;

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		SERIALIZE(aaa);
		SERIALIZE(bbb);
		SERIALIZE(ccc);
		SERIALIZE(ddd);
	}
};

int main()
{
	TestA A;
	BinaryFileWrite write("111.bin");
	A.Serialize<BinaryFileWrite>(write);
	write.EndSerialize();

	return 0;
}