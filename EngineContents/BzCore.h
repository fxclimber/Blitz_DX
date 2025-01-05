#pragma once
#include <EngineCore/IContentsCore.h>

class UBzCore : public IContentsCore
{
public:
	UBzCore();
	~UBzCore();

protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();
	void ResourceSetting();

private:

};

