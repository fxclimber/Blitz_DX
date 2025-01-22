#pragma once
#include <EngineCore/GameMode.h>
#include <Enginebase/EngineRandom.h>
#include <EngineCore/ACtor.h>
#include "PathFindAstar.h"
#include "BzEnemyCube.h"

class ABzClassManager : public AActor
{
public:
	ABzClassManager();
	virtual ~ABzClassManager();

	virtual void BeginPlay()override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd()override;
	virtual void Tick(float _DeltaTime) override;


	//UPathFindAStar PathFinder;
	UEngineRandom Random;

	std::vector<class ABzEnemyCube*> Enemies;

	void RegisterEnemy(class ABzEnemyCube* _enemy) {
		Enemies.push_back(_enemy);
	}

	void RemoveEnemy(class ABzEnemyCube* _enemy) {
		//Enemies.erase(std::remove(Enemies.begin(), Enemies.end(), _enemy), Enemies.end());
	}

	class ABzEnemyCube* GetClosestEnemy(const FVector& projectilePos) {
		class ABzEnemyCube* closest = nullptr;
		float minDist = FLT_MAX;

		for (class ABzEnemyCube* enemy : Enemies) 
		{
			FVector diff = enemy->GetActorLocation() - projectilePos;
			float dist = diff.Length();

			if (dist < minDist) 
			{
				minDist = dist;
				closest = enemy;
			}
		}
		return closest;
	}

protected:

private:

};

