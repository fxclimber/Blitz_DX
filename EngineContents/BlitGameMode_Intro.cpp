#include "PreCompile.h"
#include "BlitGameMode_Intro.h"
#include "BlitzPlayerCube.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>

class TestWindow : public UEngineGUIWindow
{
public:

};

ABlitGameMode_Intro::ABlitGameMode_Intro()
{
	{
		PlayerCube = GetWorld()->SpawnActor<ABlitzPlayerCube>();
		// Logo->SetActorLocation({ 300.0f, 0.0f, 0.0f });
	}


	{

	}
	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
}

ABlitGameMode_Intro::~ABlitGameMode_Intro()
{

}

void ABlitGameMode_Intro::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);



}