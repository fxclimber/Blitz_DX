#include "PreCompile.h"
#include "BzCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineGUI.h>

#include <EngineCore/HUD.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>
#include "TitleHUD.h"

#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>

#include "ContentsEditorGUI.h"
#include "BzGameMode_Intro.h"
#include "BzTileMapGameMode.h"
#include "BzPlayerCube.h"
#include "TileMapGameMode.h"

#include "BzHUD.h"


// 어떤 코어 쓸거니?
CreateContentsCoreDefine(UBzCore);

UBzCore::UBzCore()
{
}

UBzCore::~UBzCore()
{
}

void UBzCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 0 };
	_Data.WindowSize = { 900, 900 };
	// 증말 중요한!!! 리소스 세팅함수!!! 이안에 게임모드별, 텍스쳐,쉐이더 정보를 다 넣을것!!
	UBzCore::ResourceSetting();//이거 안하면 리소스들 널로 나온다 
	//---------------------------------------------------------

	// 주인공 APawn 상속 받으세요.
	UEngineCore::CreateLevel<ABzGameMode_Intro, ABzPlayerCube , ABzHUD>("Play");// 플레이 
	UEngineCore::CreateLevel<ABzTileMapGameMode, APawn , AHUD>("Map_Edit");// 맵 에디터 
	UEngineCore::CreateLevel<ATileMapGameMode, APawn , AHUD >("TileMapEditor");// 나중에 스프라이트 선택해서 쓸때 
	UEngineCore::OpenLevel("Play");

	// imgui window------------------------------------------------
	UEngineGUI::AllWindowOff();
	UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("Editor");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("Editor");
	Window->SetActive(true);
}

void UBzCore::EngineTick(float _DeltaTime)
{

}

void UBzCore::EngineEnd()
{

}

