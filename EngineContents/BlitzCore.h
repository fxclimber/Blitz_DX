#pragma once
#include <EngineCore/IContentsCore.h>

class UBlitzCore : public IContentsCore
{
public:
	UBlitzCore();
	~UBlitzCore();

protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();

private:
	void MyGSetting();

};

