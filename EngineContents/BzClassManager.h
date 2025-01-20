#pragma once
#include <EngineCore/GameMode.h>
#include <Enginebase/EngineRandom.h>
#include "PathFindAstar.h"


class ABzClassManager : public AGameMode
{
public:
	ABzClassManager();
	virtual ~ABzClassManager();

	virtual void BeginPlay()override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd()override;
	virtual void Tick(float _DeltaTime) override;


	UPathFindAStar PathFinder;
	UEngineRandom Random;

protected:

private:
	class ABzTileMap* map = nullptr;

};

