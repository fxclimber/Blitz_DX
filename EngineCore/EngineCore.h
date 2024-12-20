#pragma once
#include <EngineBase/EngineDefine.h>
#include <EnginePlatform/EngineWindow.h>
#include "EngineGraphicDevice.h"
#include "IContentsCore.h"
#include "Level.h"
#include <memory>


// 설명 :
class UEngineCore
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineCore();
	ENGINEAPI virtual ~UEngineCore() = 0;

	ENGINEAPI static void EngineStart(HINSTANCE _Instance, std::string_view _DllName);

	template<typename GameModeType, typename MainPawnType>
	static class std::shared_ptr<class ULevel> CreateLevel(std::string_view _Name)
	{
		// 1 유지하고 있겠죠.
		// shared_ptr을 사용하므로 new UEngineLevel()
		std::shared_ptr<ULevel> NewLevel = NewLevelCreate(_Name);
		// std::make_shared
		// new UEngineLevel();

		NewLevel->SpawnActor<GameModeType>();
		NewLevel->SpawnActor<MainPawnType>();

		// 2가 됩니다
		return NewLevel;
	}

	ENGINEAPI static void OpenLevel(std::string_view _Name);

	ENGINEAPI static UEngineGraphicDevice Device;

	ENGINEAPI static FVector GetScreenScale();

protected:

private:
	// 데이터영역에 있죠? => 언제 삭제될까요?
	// 릭체크는 
	ENGINEAPI static UEngineWindow MainWindow;
	static HMODULE ContentsDLL;
	static std::shared_ptr<IContentsCore> Core;
	static UEngineInitData Data;

	static void WindowInit(HINSTANCE _Instance);
	static void LoadContents(std::string_view _DllName);

	static void EngineFrame();
	static void EngineEnd();

	ENGINEAPI static std::shared_ptr<ULevel> NewLevelCreate(std::string_view _Name);

	static std::map<std::string, std::shared_ptr<class ULevel>> LevelMap;
	static std::shared_ptr<class ULevel> CurLevel;
	static std::shared_ptr<class ULevel> NextLevel;
};

