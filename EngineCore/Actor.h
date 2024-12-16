#pragma once
#include <EngineBase/Object.h>


// 기하구조를 이야기해 봅시다.
// 설명 :
// 언리얼에서 Actor는 절대 트랜스폼을 가지지 않는다.
class AActor : public UObject
{
	friend class ULevel;

public:
	// constrcuter destructer
	ENGINEAPI AActor();
	ENGINEAPI ~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	ENGINEAPI virtual void BeginPlay();
	ENGINEAPI virtual void Tick(float _DeltaTime);

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}


	// 이녀석 꽤 많이 
	void CreateDefaultSubObject()
	{

	}

	ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	// 초기화 하면 안됩니다.
	ULevel* World;

	// std::list<std::shared_ptr<class UActorComponent>>
	std::shared_ptr<class USceneComponent> RootComponent;
	// std::list<std::shared_ptr<class USceneComponent>> SceneComponentLists;

	// 이제 처음으로 만드는 SceneComponent 무조건 Root가 됩니다.
	// 온리 ActorComponent만 분리할거냐.
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

