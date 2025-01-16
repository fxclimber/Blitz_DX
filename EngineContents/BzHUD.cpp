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

		Widget->SetScale3D({ 100, 50, 1 });
		Widget->SetWorldLocation({ -350, 400 });
		Widget->SetTexture("exit.png");
		Widget->SetDownEvent([]()
			{
				UEngineDebug::OutPutString("Click~~~~~~~~~");
			});
	}

	{
		std::shared_ptr<UFontWidget> Widget = CreateWidget<UFontWidget>(1);

		Widget->SetWorldLocation({ 200, 300 });
		Widget->SetFont("궁서");
		Widget->SetText("안녕하세요");
	}
}

void ABzHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);
}
