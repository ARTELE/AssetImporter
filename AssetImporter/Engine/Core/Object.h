#pragma once
#include "Types.h"

class Object
{
protected:
	InstanceID instanceId;
public:
	InstanceID GetInstanceId() { return instanceId; }
	void SetInstanceId(InstanceID value) { instanceId = value; }
	Object(){}
};