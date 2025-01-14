#include "PreCompile.h"
#include "BzHUD.h"
#include <EngineCore/Widget.h>

ABzHUD::ABzHUD()
{
}

ABzHUD::~ABzHUD()
{
}

void ABzHUD::BeginPlay()
{
	AHUD::BeginPlay();

	std::shared_ptr<UWidget> Button = CreateWidget<UWidget>(-1);

	Button->SetScale3D({ 100, 42, 1 });
	Button->SetWorldLocation({ -390, 420 });
	Button->SetTexture("play.png");
	Button->SetDownEvent([]() 
		{
			UEngineDebug::OutPutString("Click~~~~~~~~~");
		});

}

void ABzHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);
}
