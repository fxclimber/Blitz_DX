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

// � �ھ� ���Ŵ�?
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
	// ���� �߿���!!! ���ҽ� �����Լ�!!! �̾ȿ� ���Ӹ�庰, �ؽ���,���̴� ������ �� ������!!
	UBzCore::ResourceSetting();//�̰� ���ϸ� ���ҽ��� �η� ���´� 
	//---------------------------------------------------------

	// ���ΰ� APawn ��� ��������.
	UEngineCore::CreateLevel<ABzGameMode_Intro, APawn>("Play");// �÷��� 
	UEngineCore::CreateLevel<ABzTileMapGameMode, APawn>("Map_Edit");// �� ������ 
	UEngineCore::CreateLevel<ATileMapGameMode, APawn>("TileMapEditor");// ���߿� ��������Ʈ �����ؼ� ���� 
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

