#pragma once
#include <EngineCore/Actor.h>

enum EMonsterType
{
	Monster,
	Monster2,
};

// Ό³Έν :
class AMon : public AActor
{
public:
	// constrcuter destructer
	AMon();
	~AMon();

	// delete Function
	AMon(const AMon& _Other) = delete;
	AMon(AMon&& _Other) noexcept = delete;
	AMon& operator=(const AMon& _Other) = delete;
	AMon& operator=(AMon&& _Other) noexcept = delete;

	EMonsterType MonsterTypeValue;

protected:

private:
};

