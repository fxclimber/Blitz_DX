#include "PreCompile.h"
#include "ContentsCore.h"

// #define은 그냥 무조건 복붙
CreateContentsCoreDefine(UContentsCore);
//STDAPI_(__declspec(dllexport) INT_PTR) CreateContentsCore(std::shared_ptr<IContentsCore>& _Test)
//{ 
//	_Test = std::make_shared<UContentsCore>();
//	if (nullptr == _Test) 
//	{ 
//		MSGASSERT("컨텐츠 모듈 생성에 실패했습니다."); 
//	} 
//	return 0; 
//}

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
	_Data.WindowSize = { 300, 300 };

	// 윈도우 크기 지정
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}