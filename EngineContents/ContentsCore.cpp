#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include "TitleGameMode.h"
#include "TileMapGameMode.h"
#include <EngineCore/HUD.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>
#include "TitleHUD.h"
#include "TestGameMode.h"
#include "ContentsEditorGUI.h"
#include "MyGameInstance.h"

// #define�� �׳� ������ ����
//CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}


void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	// mainwindow�� �ƹ��� �ǵ�� �ȵȴ�.
	// �� �������ݾ� ������ �����ϴ� �������°� �����ϴ����� ������Ѵ�.

	GEngine->CreateGameInstance<MyGameInstance>();

	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	MyGSetting();

	// new int();



	UEngineCore::CreateLevel<ATestGameMode, APawn, AHUD>("LoadingLevel");

	UEngineCore::OpenLevel("LoadingLevel");
	// UEngineCore::OpenLevel("Titlelevel");

	UEngineGUI::AllWindowOff();

	UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	Window->SetActive(true);
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}