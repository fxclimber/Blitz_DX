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
	void OnGUI() override
	{
		ImGui::Button("WindowButton");
		ImGui::SameLine(); // 한간 띄기
		ImGui::Text("test");

	}


};

ABlitGameMode_Intro::ABlitGameMode_Intro()
{
	UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
	{
		PlayerCube = GetWorld()->SpawnActor<ABlitzPlayerCube>();
		PlayerCube->SetActorRelativeScale3D({10,10,10});
	}

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -100.0f, 1.0f });
}

ABlitGameMode_Intro::~ABlitGameMode_Intro()
{

}

void ABlitGameMode_Intro::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	FTransform pos = PlayerCube->GetActorTransform();
	//Camera->AddRelativeLocation(pos.Location);// 왜 반대로 움직이냐?? 
	Camera->SetActorLocation((pos.Location) + FVector( 0.0f, 0.0f, -100.0f));



}