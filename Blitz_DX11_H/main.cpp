#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineCore.h>

#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EnginePlatform.lib")
#pragma comment(lib, "EngineCore.lib")

int APIENTRY wWinMain(_In_ HINSTANCE _hInstance,
	_In_opt_ HINSTANCE _hPrevInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	// 동적로딩을 위해 "컨텐츠.dll"이름을 넣을것 
	UEngineCore::EngineStart(_hInstance, "EngineContents.dll");
	return 0;
}