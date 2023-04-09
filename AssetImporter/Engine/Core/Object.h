#pragma once
#include "Types.h"

class Object
{
protected:
	InstanceID instanceId = 0;
public:
	InstanceID GetInstanceId() { return instanceId; }
	void SetInstanceId(InstanceID value) { instanceId = value; }
	virtual Object* Clone() { return nullptr; } //����Ҫ���麯��
	Object(){}
};