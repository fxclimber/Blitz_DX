#pragma once
#include "Actor.h"

// Ό³Έν :
class ACameraActor : public AActor
{
public:
	// constrcuter destructer
	ACameraActor();
	~ACameraActor();

	// delete Function
	ACameraActor(const ACameraActor& _Other) = delete;
	ACameraActor(ACameraActor&& _Other) noexcept = delete;
	ACameraActor& operator=(const ACameraActor& _Other) = delete;
	ACameraActor& operator=(ACameraActor&& _Other) noexcept = delete;

	std::shared_ptr<class UEngineCamera> CameraComponent = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime);


protected:

private:
};

