#include "PreCompile.h"
#include "CubeTest_GameMode.h"
#include "CubeTest_Player.h"


#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>

#include <EngineCore/imgui.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineInput.h>




class UCubeTestPlayWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine();
		ImGui::Text("UCubeTestPlayWindow");
	}
};





ACubeTest_GameMode::ACubeTest_GameMode()
{
	ACameraActor* Camera = GetWorld()->GetMainCamera().get();
	std::shared_ptr<class UEngineCamera> cam = Camera->GetCameraComponent();
	cam->SetProjectionType(EProjectionType::Perspective);

	FVector camPos = { 100.0f, 220.0f, -200.0f, 1.0f };
	Camera->SetActorLocation(camPos);
	Camera->SetActorRotation({ 25.f,330.f,0.f });

}

ACubeTest_GameMode::~ACubeTest_GameMode()
{
}

void ACubeTest_GameMode::BeginPlay()
{
	AActor::BeginPlay();

	GetWorld()->SpawnActor<ACubeTest_Player>();
}

void ACubeTest_GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


}

void ACubeTest_GameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	{
		std::shared_ptr<UCubeTestPlayWindow> Window = UEngineGUI::FindGUIWindow<UCubeTestPlayWindow>("UCubeTestPlayWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UCubeTestPlayWindow>("UCubeTestPlayWindow");
		}

		Window->SetActive(true);
	}
}