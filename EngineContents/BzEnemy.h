#pragma once

enum EEnemyType
{
	BzEnemyCube,
	BzEnemyCubeBig,
};


class ABzEnemy : public AActor
{
public:
	ABzEnemy();
	~ABzEnemy(){}
	EEnemyType EEnemyTypeValue;

protected:
	void BeginPlay() override{}
	void Tick(float _DeltaTime) override{}

private:
	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;

};

