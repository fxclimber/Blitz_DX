#pragma once
#include <EngineCore/IContentsCore.h>

class UBzCore : public IContentsCore
{
public:
	UBzCore();
	~UBzCore();

	ENGINEAPI static inline FVector BgColor= { 0.f,0.f,0.1f,1.f };
protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();
	void ResourceSetting();

	class ABzGameMode_Intro* GetGameMode()
	{
		return GameMode;
	}

private:
	//std::shared_ptr<class ABzGameMode_Intro> GameMode = nullptr;
	class ABzGameMode_Intro* GameMode = nullptr;
};

