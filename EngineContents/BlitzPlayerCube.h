#pragma once
#include <EngineCore/Actor.h>

class ABlitzPlayerCube : public APawn
{
public:
	ABlitzPlayerCube();
	~ABlitzPlayerCube();

	std::shared_ptr<class USpriteRenderer> GetTestSprite()
	{
		return TestSprite;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> TestSprite;
	std::shared_ptr<class USpriteRenderer> TestSpriteChild;

	std::shared_ptr<class URenderer> Renderer;
};

