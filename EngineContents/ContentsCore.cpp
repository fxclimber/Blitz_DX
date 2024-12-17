#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/Level.h>
#include "TitleGameMode.h"

// #define은 그냥 무조건 복붙
CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}


void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	// mainwindow는 아무나 건들면 안된다.
	// 넌 컨텐츠잖아 엔진이 관리하는 윈도우라는게 존재하는지도 몰라야한다.

	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	// 리로스 로드 할수 없다.

	// UEngineCore::CreateLevel<ATitleGameMode, APawn>("Titlelevel");
	UEngineCore::CreateLevel<ATitleGameMode, APawn>("Titlelevel");
	UEngineCore::OpenLevel("Titlelevel");

}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}