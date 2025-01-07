#pragma once
#include <EngineCore/Actor.h>

class ABzProjectile : public AActor
{
public:
	ABzProjectile();
	~ABzProjectile();


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	std::shared_ptr<class UBzRendererDefault> Renderer;

};

