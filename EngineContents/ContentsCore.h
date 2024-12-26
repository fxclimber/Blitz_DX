#pragma once
#include <EngineCore/IContentsCore.h>

class UContentsCore : public IContentsCore
{
public:
	UContentsCore();
	~UContentsCore();

protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();

private:

};

