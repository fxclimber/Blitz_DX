#include "PreCompile.h"
#include "BzClassManager.h"

#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWindow.h>
#include "BzTileMap.h"


ABzClassManager::ABzClassManager()
{
}

ABzClassManager::~ABzClassManager()
{
}

void ABzClassManager::BeginPlay()
{
	AActor::BeginPlay();

	PathFinder.SetData(map);

}


void ABzClassManager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}

void ABzClassManager::LevelChangeStart()
{
}

void ABzClassManager::LevelChangeEnd()
{
}