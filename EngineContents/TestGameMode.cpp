#include "PreCompile.h"
#include "TestGameMode.h"
#include "TitleLogo.h"
#include "Monster.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include "TestActor.h"
#include <EngineCore/EngineCore.h>
#include "TitleGameMode.h"
#include "TileMapGameMode.h"
#include "TitleHUD.h"

ATestGameMode::ATestGameMode()
{
	// �������� ���ּž� �մϴ�.
	// �̰� UI�����Ұ��� 
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");
	// �浹üũ �ؾ��Ѵ�.
	GetWorld()->LinkCollisionProfile("Player", "Monster");

	

	// ī�޶� �����Ÿ� �ڷ� ���� 
	// ī�޶� ��ġ������ ������ ����� �Ұ��̴�.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({0.0f, 0.0f, -1000.0f, 1.0f});
	Camera->GetCameraComponent()->SetZSort(0, true);

	{
		std::shared_ptr<ATestActor> NewMonster = GetWorld()->SpawnActor<ATestActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 200.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ 0.0f, 0.0f, 0.0f });
	}


}

ATestGameMode::~ATestGameMode()
{

}

void ATestGameMode::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);


	if (true == LoadingEnd)
	{
		// �̹����� ��ȯ 
		//UEngineCore::CreateLevel<ATitleGameMode, APawn, ATitleHUD>("Titlelevel");
		UEngineCore::CreateLevel<ATileMapGameMode, APawn, AHUD>("TileMapEditor");
		UEngineCore::OpenLevel("Titlelevel");
	}

}

void ATestGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	if (false == LoadingEnd)
	{


		Thread.Start("Loading", [this]()
			{

				// ������ ���ݾ�. �ѵ�� �´´�.

				{
					// ���� �ȵǴ� �̴ϴ�.
					// �����尡 ����������� �� ��ü�� ����־�� �Ѵٴ� ���� ����ּ���.
					// UEngineThread Thread;

					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("ContentsResources"))
					{
						MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
						return;
					}
					Dir.Append("Image");
					// �ε��� ����� ������  100���� 10 10 10 10 10 10
					std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
					for (size_t i = 0; i < ImageFiles.size(); i++)
					{
						std::string FilePath = ImageFiles[i].GetPathToString();
						UEngineTexture::Load(FilePath);
					}
				}

				UEngineSprite::CreateSpriteToMeta("Player.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("TileMap.png", ".sdata");


				{
					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("ContentsResources"))
					{
						MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
						return;
					}
					Dir.Append("Image/Tevi");

					UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
				}

				{
					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("ContentsResources"))
					{
						MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
						return;
					}
					Dir.Append("Image/TileSet");

					UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
				}


				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyMaterial");
					Mat->SetVertexShader("TestShader.fx");
					Mat->SetPixelShader("TestShader.fx");
				}


				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyCollisionDebugMaterial");
					Mat->SetVertexShader("EngineDebugCollisionShader.fx");
					Mat->SetPixelShader("EngineDebugCollisionShader.fx");
					// ������ ȭ�鿡 ������ ������ �̳༮�� ���� ������ ����.
					Mat->SetDepthStencilState("CollisionDebugDepth");
					Mat->SetRasterizerState("CollisionDebugRas");
				}

				//for (size_t i = 0; i < 100000; i++)
				//{
				//	UEngineDebug::OutPutString("Loading.....");
				//}

				this->LoadingEnd = true;
			});
	}
	

}