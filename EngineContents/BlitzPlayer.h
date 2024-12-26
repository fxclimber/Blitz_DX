#pragma once
#include <EngineCore/Actor.h>

class ABlitzPlayer : public AActor
{
public:
	ABlitzPlayer();
	~ABlitzPlayer();

	std::shared_ptr<class URenderBlitz> GetRenderer()
	{
		return RenderBlitzForTest;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class URenderBlitz> RenderBlitzForTest;

};


