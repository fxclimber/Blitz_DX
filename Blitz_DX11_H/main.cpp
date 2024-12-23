// 비주얼 코드 쳐줌.
#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineCore.h>

// 프로젝트 다 만들었고
// 내일 부터 본격으로 하겠다.
#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EnginePlatform.lib")
#pragma comment(lib, "EngineCore.lib")

// 이녀석은 정적로딩으로 사용하지 않겠다.
// #pragma comment(lib, "EngineContents.lib")

// 예전에는 Level먼저 만들고
// 컨테츠에 가서 레벨을 Create하는 식으로 갔다.

int APIENTRY wWinMain(_In_ HINSTANCE _hInstance,
	_In_opt_ HINSTANCE _hPrevInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	// 동적 연결을 위한 "EngineContents" dll이름을 넣어줘야 한다.
	UEngineCore::EngineStart(_hInstance, "EngineContents.dll");
	return 0;
}