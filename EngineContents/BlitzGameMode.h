#pragma once
#include <EngineCore/Actor.h>

class ABlitzGameMode : public AActor
{
public:
	ABlitzGameMode();
	~ABlitzGameMode();

	void Tick(float _DeltaTime);

protected:

private:
	std::shared_ptr<class ABlitzPlayer> BlitzPlayer;
};

