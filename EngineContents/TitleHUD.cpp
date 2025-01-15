#include "PreCompile.h"
#include "TitleHUD.h"
#include <EngineCore/ImageWidget.h>
#include <EngineCore/FontWidget.h>

ATitleHUD::ATitleHUD()
{
}

ATitleHUD::~ATitleHUD()
{
}

void ATitleHUD::BeginPlay()
{
	AHUD::BeginPlay();

	{
		std::shared_ptr<UImageWidget> Widget = CreateWidget<UImageWidget>(-1);

		Widget->SetScale3D({ 100, 100, 1 });
		Widget->SetWorldLocation({ -200, 300 });
		Widget->SetTexture("BackGround.png");
		Widget->SetDownEvent([]()
			{
				UEngineDebug::OutPutString("Click~~~~~~~~~");
			});
	}

	{
		std::shared_ptr<UFontWidget> Widget = CreateWidget<UFontWidget>(1);

		Widget->SetWorldLocation({ 200, 300 });
		Widget->SetFont("±√º≠");
		Widget->SetText("æ»≥Á«œººø‰");
	}

}

void ATitleHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);
}




