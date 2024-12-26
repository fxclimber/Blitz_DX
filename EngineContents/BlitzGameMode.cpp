#include "PreCompile.h"
#include "BlitzGameMode.h"
#include "TitleLogo.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include "BlitzPlayer.h"

class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		ImGui::Button("WindowButton");
		ImGui::SameLine(); // 한간 띄기
		ImGui::Text("Blitz");

	}
};

ABlitzGameMode::ABlitzGameMode()
{
	{
		BlitzPlayer = GetWorld()->SpawnActor<ABlitzPlayer>();
		BlitzPlayer->SetActorLocation({ 100.0f, 100.0f, 0.0f });
	}

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });

	//UEngineGUI::CreateGUIWindow<TestWindow>("Blitz");
}


void ABlitzGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

}

ABlitzGameMode::~ABlitzGameMode()
{
}
