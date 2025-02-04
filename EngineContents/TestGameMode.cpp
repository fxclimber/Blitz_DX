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
	// 레벨마다 해주셔야 합니다.
	// 이걸 UI공유할건지 
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");
	// 충돌체크 해야한다.
	GetWorld()->LinkCollisionProfile("Player", "Monster");

	

	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
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
	// 부모 호출
	AActor::Tick(_DeltaTime);


	if (true == LoadingEnd)
	{
		// 이미지를 변환 
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

				// 쓰레드 모르잖아. 뚜드려 맞는다.

				{
					// 말도 안되는 겁니다.
					// 쓰레드가 살아있으려면 이 객체도 살아있어야 한다는 것을 기억핫세요.
					// UEngineThread Thread;

					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("ContentsResources"))
					{
						MSGASSERT("리소스 폴더를 찾지 못했습니다.");
						return;
					}
					Dir.Append("Image");
					// 로딩바 만들고 싶으면  100개면 10 10 10 10 10 10
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
						MSGASSERT("리소스 폴더를 찾지 못했습니다.");
						return;
					}
					Dir.Append("Image/Tevi");

					UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
				}

				{
					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("ContentsResources"))
					{
						MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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
					// 언제나 화면에 나오는 누구도 이녀석의 앞을 가릴수 없어.
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