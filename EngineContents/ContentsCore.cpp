#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include "TitleGameMode.h"
#include "TileMapGameMode.h"
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>
#include "ContentsEditorGUI.h"

#include "BzCore.h"


#include "BzGameMode_Intro.h"
#include "BzTileMapGameMode.h"

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

	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	MyGSetting();



	// ���ΰ� APawn ��� ��������.
	//UEngineCore::CreateLevel<ATitleGameMode, APawn>("Titlelevel");
	//UEngineCore::CreateLevel<ATileMapGameMode, APawn>("TileMapEditor");

	UEngineCore::CreateLevel<ABzGameMode_Intro, APawn>("Play");
	UEngineCore::CreateLevel<ABzTileMapGameMode, APawn>("BzTileMap");

	UEngineCore::OpenLevel("BzTileMap");

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