#pragma once
#include <EngineCore/HUD.h>


class ABzHUD :public AHUD
{
public:
	ABzHUD();
	~ABzHUD();

	void BeginPlay();
	void Tick(float _DeltaTime);

protected:

private:

};

