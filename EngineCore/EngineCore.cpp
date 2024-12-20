#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include "IContentsCore.h"
#include "Level.h"

UEngineGraphicDevice UEngineCore::Device;
UEngineWindow UEngineCore::MainWindow;
HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::Core;
UEngineInitData UEngineCore::Data;

std::shared_ptr<class ULevel> UEngineCore::NextLevel;
std::shared_ptr<class ULevel> UEngineCore::CurLevel = nullptr;

std::map<std::string, std::shared_ptr<class ULevel>> UEngineCore::LevelMap;

FVector UEngineCore::GetScreenScale()
{
	return Data.WindowSize;
}

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::WindowInit(HINSTANCE _Instance)
{
	UEngineWindow::EngineWindowInit(_Instance);
	MainWindow.Open("MainWindow");
}

void UEngineCore::LoadContents(std::string_view _DllName)
{
	UEngineDirectory Dir;

	Dir.MoveParentToDirectory("Build");
	Dir.Move("bin/x64");

	// 빌드 상황에 따라서 경로 변경
#ifdef _DEBUG
	Dir.Move("Debug");
#else
	Dir.Move("Release");
#endif

	UEngineFile File = Dir.GetFile(_DllName);

	std::string FullPath = File.GetPathToString();
	// 규칙이 생길수밖에 없다.
	ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == ContentsDLL)
	{
		MSGASSERT("컨텐츠 기능을 로드할수가 없습니다.");
		return;
	}

	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");

	if (nullptr == Ptr)
	{
		MSGASSERT("컨텐츠 코어 내부에 CreateContentsCoreDefine을 정의하지 않았습니다.");
		return;
	}

	Ptr(Core);

	if (nullptr == Core)
	{
		MSGASSERT("컨텐츠 코어 생성에 실패했습니다.");
		return;
	}
}

void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{
	UEngineDebug::LeakCheck();

	WindowInit(_Instance);

	LoadContents(_DllName);

	// 윈도우와는 무관합니다.
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			// 어딘가에서 이걸 호출하면 콘솔창이 뜨고 그 뒤로는 std::cout 하면 그 콘솔창에 메세지가 뜰겁니다.
			// UEngineDebug::StartConsole();
			Device.CreateDeviceAndContext();
			Core->EngineStart(Data);
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			Device.CreateBackBuffer(MainWindow);
			// 디바이스가 만들어지지 않으면 리소스 로드도 할수가 없다.
			// 여기부터 리소스 로드가 가능하다.


		},
		[]()
		{
			EngineFrame();
			// 엔진이 돌아갈때 하고 싶은것
		},
		[]()
		{
			// static으로 하자고 했습니다.
			// 이때 레벨이 다 delete가 되어야 한다.
			// 레퍼런스 카운트로 관리되면 그 레퍼런스 카운트는 내가 세고 있어요.
			EngineEnd();
		});


	// 게임 엔진이 시작되었다.
	// 윈도우창은 엔진이 알아서 띄워줘야 하고.

	// Window 띄워줘야 한다.


}

// 헤더 순환 참조를 막기 위한 함수분리
std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string_view _Name)
{
	// 만들기만 하고 보관을 안하면 앤 그냥 지워집니다. <= 

	// 만들면 맵에 넣어서 레퍼런스 카운트를 증가시킵니다.
	// UObject의 기능이었습니다.
	std::shared_ptr<ULevel> Ptr = std::make_shared<ULevel>();
	Ptr->SetName(_Name);

	LevelMap.insert({ _Name.data(), Ptr });

	std::cout << "NewLevelCreate" << std::endl;

	return Ptr;
}

void UEngineCore::OpenLevel(std::string_view _Name)
{
	if (false == LevelMap.contains(_Name.data()))
	{
		MSGASSERT("만들지 않은 레벨로 변경하려고 했습니다." + std::string(_Name));
		return;
	}


	NextLevel = LevelMap[_Name.data()];
}

void UEngineCore::EngineFrame()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		CurLevel->LevelChangeStart();
		NextLevel = nullptr;
	}

	CurLevel->Tick(0.0f);
	CurLevel->Render(0.0f);

	// tick
}

void UEngineCore::EngineEnd()
{
	// 리소스 정리도 여기서 할겁니다.
	Device.Release();

	CurLevel = nullptr;
	NextLevel = nullptr;
	LevelMap.clear();

	UEngineDebug::EndConsole();

}