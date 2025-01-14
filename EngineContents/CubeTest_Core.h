#pragma once
#include <EngineCore/IContentsCore.h>

class UCubeTest_Core : public IContentsCore
{
public:
	UCubeTest_Core();
	~UCubeTest_Core();

protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();
	void ResourceSetting();

	std::shared_ptr<class ABzGameMode_Intro> GetGameMode()
	{
		return GameMode;
	}

private:
	std::shared_ptr<class ABzGameMode_Intro> GameMode = nullptr;

};

