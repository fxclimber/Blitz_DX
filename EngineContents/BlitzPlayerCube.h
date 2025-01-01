#pragma once
#include <EngineCore/Actor.h>

class ABlitzPlayerCube : public APawn
{
public:
	// constrcuter destructer
	ABlitzPlayerCube();
	~ABlitzPlayerCube();

	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return LogoRenderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> LogoRenderer;
	std::shared_ptr<class USpriteRenderer> Child;
};

