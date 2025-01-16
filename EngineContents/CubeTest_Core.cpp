#include "PreCompile.h"
#include "CubeTest_Core.h"
#include "CubeTest_GameMode.h"
#include "CubeTest_Player.h"

#include "ContentsEditorGUI.h"

#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineGUI.h>

#include <EngineCore/HUD.h>
#include <EngineCore/EngineGUIWindow.h>

#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>

//CreateContentsCoreDefine(UCubeTest_Core);

UCubeTest_Core::UCubeTest_Core()
{
}

UCubeTest_Core::~UCubeTest_Core()
{
}

void UCubeTest_Core::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 0 };
	_Data.WindowSize = { 900, 900 };
	UCubeTest_Core::ResourceSetting();

	UEngineCore::CreateLevel<ACubeTest_GameMode,ACubeTest_Player,AHUD>("CubeTest");
	UEngineCore::OpenLevel("CubeTest");

	// imgui window-----임구이 안쓸거면, 삭제, 쓸거면, 파일복제 -------------------------------------------
	UEngineGUI::AllWindowOff();
	UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("Editor");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("Editor");
	Window->SetActive(true);

}

void UCubeTest_Core::EngineTick(float _DeltaTime)
{
}

void UCubeTest_Core::EngineEnd()
{
}

