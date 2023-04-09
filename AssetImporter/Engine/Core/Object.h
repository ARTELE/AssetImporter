#pragma once
#include "Types.h"

class Object
{
protected:
	InstanceID instanceId = 0;
public:
	InstanceID GetInstanceId() { return instanceId; }
	void SetInstanceId(InstanceID value) { instanceId = value; }
	virtual Object* Clone() { return nullptr; } //这里要纯虚函数
	Object(){}
};