#pragma once
#include <EngineCore/Actor.h>


class ABzBottom : public AActor
{
public:
	ABzBottom();
	~ABzBottom();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class UBzRendererDefault> RendererBottom;

};

