#pragma once
#include <EngineBase/Object.h>


class UActorComponent : public UObject
{
public:
	UActorComponent();
	~UActorComponent();


	std::shared_ptr<class AActor> GetActor()
	{
		return nullptr;
	}

protected:

private:
	class AActor* Actor;
};

