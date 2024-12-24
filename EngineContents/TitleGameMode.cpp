#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>

ATitleGameMode::ATitleGameMode()
{
	{
		Logo = GetWorld()->SpawnActor<ATitleLogo>();
		Logo->SetActorLocation({ 300.0f, 0.0f, 0.0f });
		Logo->GetRenderer()->SetSpriteData(4);
	}

	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
}

ATitleGameMode::~ATitleGameMode()
{

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	static float Time = 1.0f;
	static int Index = 0;

	Logo->GetRenderer()->SetSpriteData(Index);

	Time -= _DeltaTime;

	if (0.0f >= Time)
	{
		++Index;
		Time = 1.0f;
	}


}