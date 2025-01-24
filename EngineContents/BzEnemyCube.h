#pragma once
#include <EngineCore/Actor.h>
#include "BzEnemy.h"
#include <EngineBase/EngineRandom.h>

class ABzEnemyCube : public ABzEnemy
{
public:
	ABzEnemyCube();
	~ABzEnemyCube();
	void SetPlayer(std::shared_ptr<class ABzPlayerCube> _name);
	void SetPath(const std::list<FVector>& NewPath)	{		AStarPath = NewPath;	}
	// 몬스터 데미지줄 예정.
	void TakeDamage();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Ani_Idle(float _DeltaTime);
	float GetRandom(float _x);
	void Physics(float _DeltaTime);


	// 에너미끼리도 충돌판단해야하는데
	bool CheckAttackDistance(float _DeltaTime , float _speed);
	// 한마리만 만들고, 피하는지 디버깅 필요 
	void AvoidWall(float _DeltaTime);
	// 타일 높이 적용 함수 
	void ApplyTilemap();


	// 길찾기 함수 
	void MoveAlongPath(float DeltaTime);


private:
	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;
	class ABzPlayerCube* Player = nullptr;

	float DistFromPlayer = 0.f;

	float rotationAngle = 0.f;
	float jumpHeight = 0.f;
	FVector gravity = { 0.f,-2.f,0.f };
	FVector vel = { 0.f,1.f,0.f };
	float radius = 0;
	FVector pos = {};

	float AttackDistance;
	FVector Attackdir;
	FVector AttackPlayerPos;

	UEngineRandom random;
	float randomResult = 0;
	class UTimeEventComponent* TimeEventComponent;

	std::vector<UCollision*> collisionList;
	std::list<FVector> AStarPath;

	FVector Scale = { 70.f,120.f,70.f };
	class ABzClassManager* Manager;

};

