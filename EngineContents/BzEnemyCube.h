#pragma once
#include <EngineCore/Actor.h>


class ABzEnemyCube : public APawn
{
public:
	ABzEnemyCube();
	~ABzEnemyCube();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class UBzRendererDefault> Renderer;

};

