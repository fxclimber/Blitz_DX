#include "PreCompile.h"
#include "BlitzCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include "BlitGameMode_Intro.h"
#include "BlitzPlayerCube.h"

// #define은 그냥 무조건 복붙
CreateContentsCoreDefine(UBlitzCore);

UBlitzCore::UBlitzCore()
{
}

UBlitzCore::~UBlitzCore()
{
}

void UBlitzCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 900, 900 };

	
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	UEngineSprite::CreateSpriteToMeta("Player.png", ".sdata");

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


	// 주인공 APawn 상속 받으세요.
	UEngineCore::CreateLevel<ABlitGameMode_Intro, APawn>("Intro");
	UEngineCore::OpenLevel("Intro");

}

void UBlitzCore::EngineTick(float _DeltaTime)
{

}

void UBlitzCore::EngineEnd()
{

}

