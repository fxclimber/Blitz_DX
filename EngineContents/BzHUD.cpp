#include "PreCompile.h"
#include "BzHUD.h"
#include <EngineCore/ImageWidget.h>
#include <EngineCore/FontWidget.h>


ABzHUD::ABzHUD()
{
}

ABzHUD::~ABzHUD()
{
}

void ABzHUD::BeginPlay()
{
	AHUD::BeginPlay();
	{
		std::shared_ptr<UImageWidget> Widget = CreateWidget<UImageWidget>(-1);
		Widget->SetScale3D({ 100, 100, 1 });
		Widget->SetWorldLocation({ -200, 300 });
		Widget->SetTexture("play.png");
		Widget->SetDownEvent([]()
			{
				UEngineDebug::OutPutString("Click~~~~~~~~~");
			});
	}
	{
		std::shared_ptr<UFontWidget> Widget = CreateWidget<UFontWidget>(1);
		Widget->SetWorldLocation({ 200, 300 });
		Widget->SetFont("±Ã¼­");
		Widget->SetText("¾È³çÇÏ¼¼¿ä");
	}
}

void ABzHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);
}
