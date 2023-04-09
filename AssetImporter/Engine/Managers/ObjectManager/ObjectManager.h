#pragma once
#include<Engine/Core/Types.h>
#include <unordered_map>
#include <Engine/Core/Object.h>
#include <Engine/Systems/Allocator/SystemAllocator.h>
class ObjectManager
{
	InstanceID id = -10000;
	std::unordered_map<InstanceID,Object*> idToInstance;
public:
	SystemAllocator allocator = SystemAllocator(false);

	InstanceID GenerateInstanceId() { return --id; }
	void AddObject(Object* object);
	Object* IDToPointer(InstanceID id);
	void UnloadObject(Object* object);
	void Initialize();
};