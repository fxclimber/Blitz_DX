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
	// ���� �������� ����.
	void TakeDamage();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Ani_Idle(float _DeltaTime);
	float GetRandom(float _x);
	void Physics(float _DeltaTime);


	// ���ʹ̳����� �浹�Ǵ��ؾ��ϴµ�
	bool CheckAttackDistance(float _DeltaTime , float _speed);
	// �Ѹ����� �����, ���ϴ��� ����� �ʿ� 
	void AvoidWall(float _DeltaTime);
	// Ÿ�� ���� ���� �Լ� 
	void ApplyTilemap();


	// ��ã�� �Լ� 
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

