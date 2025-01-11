#include "PreCompile.h"
#include "BzCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineGUI.h>

#include "ContentsEditorGUI.h"
#include "BzGameMode_Intro.h"
#include "BzTileMapGameMode.h"

#include "TileMapGameMode.h"

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
	_Data.WindowPos = { 500, 100 };
	_Data.WindowSize = { 900, 900 };
	// 증말 중요한!!! 리소스 세팅함수!!! 이안에 게임모드별, 텍스쳐,쉐이더 정보를 다 넣을것!!
	UBzCore::ResourceSetting();//이거 안하면 리소스들 널로 나온다 
	//---------------------------------------------------------

	// 주인공 APawn 상속 받으세요.
	UEngineCore::CreateLevel<ABzGameMode_Intro, APawn>("Play");// 플레이 
	UEngineCore::CreateLevel<ABzTileMapGameMode, APawn>("Map_Edit");// 맵 에디터 
	UEngineCore::CreateLevel<ATileMapGameMode, APawn>("TileMapEditor");// 나중에 스프라이트 선택해서 쓸때 
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

