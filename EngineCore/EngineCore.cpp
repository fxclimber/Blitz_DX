#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::EngineStart(HINSTANCE _Instance)
{
	UEngineDebug::LeakCheck();

	UEngineWindow::EngineWindowInit(_Instance);

	UEngineWindow MainWindow;

	MainWindow.Open("MainWindow");

	// 윈도우와는 무관합니다.
	UEngineWindow::WindowMessageLoop(nullptr,[](){		});


	// 게임 엔진이 시작되었다.
	// 윈도우창은 엔진이 알아서 띄워줘야 하고.

	// Window 띄워줘야 한다.

	
}