#include "PreCompile.h"
#include "BzCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineGUI.h>


#include "ContentsEditorGUI.h"
#include "BzGameMode_Intro.h"
#include "BzTileMapGameMode.h"

#include "BzPlayerCube.h"
#include "TileMapGameMode.h"

// #define은 그냥 무조건 복붙
CreateContentsCoreDefine(UBzCore);


//FVector UBzCore::BgColor = { 1.f,1.f,0.f,1.f };

UBzCore::UBzCore()
{
}

UBzCore::~UBzCore()
{
}

void UBzCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 500, 100 };
	_Data.WindowSize = { 900, 900 };

	UBzCore::ResourceSetting();//이거 안하면 리소스들 널로 나온다 


	// 주인공 APawn 상속 받으세요.
	UEngineCore::CreateLevel<ABzGameMode_Intro, APawn>("Play");
	UEngineCore::CreateLevel<ABzTileMapGameMode, APawn>("BzTileMap");
	//UEngineCore::CreateLevel<ATileMapGameMode, APawn>("TileMapEditor");//임시 
	UEngineCore::OpenLevel("Play");

	// imgui window------------------------------------------------
	UEngineGUI::AllWindowOff();

	UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	Window->SetActive(true);


}

void UBzCore::EngineTick(float _DeltaTime)
{

}

void UBzCore::EngineEnd()
{

}

