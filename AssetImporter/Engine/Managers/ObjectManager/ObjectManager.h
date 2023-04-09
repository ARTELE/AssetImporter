#pragma once
#include<Engine/Core/Types.h>
#include <unordered_map>
#include <Engine/Core/Object.h>
#include <Engine/Systems/Allocator/SystemAllocator.h>
class ObjectManager
{
	std::unordered_map<InstanceID,Object*> idToInstance;
public:
	
	Object* IDToPointer(InstanceID id);
	void Initialize();
};