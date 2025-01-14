#include "PreCompile.h"
#include "TitleHUD.h"
#include <EngineCore/Widget.h>

ATitleHUD::ATitleHUD()
{
}

ATitleHUD::~ATitleHUD()
{
}

void ATitleHUD::BeginPlay()
{
	AHUD::BeginPlay();

	std::shared_ptr<UWidget> Button = CreateWidget<UWidget>(-1);

	Button->SetScale3D({100, 100, 1});
	Button->SetWorldLocation({ -200, 300 });
	Button->SetTexture("BackGround.png");
	Button->SetDownEvent([]()
		{
			UEngineDebug::OutPutString("Click~~~~~~~~~");
		});

}

void ATitleHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);
}




