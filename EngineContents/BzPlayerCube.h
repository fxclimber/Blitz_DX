#pragma once
#include <EngineCore/Actor.h>

class ABzPlayerCube : public APawn
{
public:
	ABzPlayerCube();
	~ABzPlayerCube();



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> LogoRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;


};

