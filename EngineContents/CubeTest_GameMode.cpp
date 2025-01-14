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
		if (true == ImGui::Button("NAN"))
		{
			//std::shared_ptr<AMonster> NewMonster = GetWorld()->SpawnActor<AMonster>();
			//NewMonster->SetActorLocation({ 300.0f, 200.0f, 0.0f });
		}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine(); // ÇÑ°£ ¶ç±â
		ImGui::Text("CAM");
	}
};





ACubeTest_GameMode::ACubeTest_GameMode()
{
	ACameraActor* Camera = GetWorld()->GetMainCamera().get();
	std::shared_ptr<class UEngineCamera> cam = Camera->GetCameraComponent();
	cam->SetProjectionType(EProjectionType::Perspective);
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
