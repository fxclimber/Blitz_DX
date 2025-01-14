#pragma once
#include <EngineCore/Pawn.h>

class ACubeTest_Player : public APawn
{
public:
	ACubeTest_Player();
	~ACubeTest_Player(){}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class UCubeTest_Renderer> Renderer;

	std::shared_ptr<class UCollision> Collision;
};

