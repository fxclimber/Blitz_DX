#include "PreCompile.h"
#include "BlitzCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include "BlitGameMode_Intro.h"
#include "BlitzPlayerCube.h"

// #define�� �׳� ������ ����
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
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image/Tevi");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}


	// ���ΰ� APawn ��� ��������.
	UEngineCore::CreateLevel<ABlitGameMode_Intro, APawn>("Intro");
	UEngineCore::OpenLevel("Intro");

}

void UBlitzCore::EngineTick(float _DeltaTime)
{

}

void UBlitzCore::EngineEnd()
{

}

