#pragma once
#include "SceneComponent.h"

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

	// 시점함수는 엔진이 실행시켜주는 겁니다.
	// 직접호출하는 일은 있으면 안됩니다.
	ENGINEAPI virtual void BeginPlay();
	ENGINEAPI virtual void Tick(float _DeltaTime);

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}


	// 이녀석 꽤 많이 
	template<typename ComponentType>
	inline std::shared_ptr<ComponentType> CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>, "액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");
			return nullptr;
			// static_assert
		}

		char* ComMemory = new char[sizeof(ComponentType)];

		UActorComponent* ComPtr = reinterpret_cast<ComponentType*>(ComMemory);
		ComPtr->Actor = this;

		ComponentType* NewPtr = reinterpret_cast<ComponentType*>(ComMemory);
		// 레벨먼저 세팅하고
		// 플레이스먼트 new 
		std::shared_ptr<ComponentType> NewCom(new(ComMemory) ComponentType());

		// 내가 그냥 ActorComponent
		// 내가 그냥 SceneComponent



		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			// 기하구조에 편입되어야 한다.
			if (nullptr != RootComponent)
			{
				MSGASSERT("아직 기하구조를 만들지 않았습니다.");
			}

			RootComponent = NewCom;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{
			ActorComponentList.push_back(NewCom);
		}
		else
		{
			MSGASSERT("말도 안됨");
		}

		return NewCom;
	}

	ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	// 초기화 하면 안됩니다.
	// 스폰액터 방식이 변경되었으니까.
	ULevel* World;

	std::shared_ptr<class USceneComponent> RootComponent = nullptr;

	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

