#pragma once
#include "EngineResources.h"

#include "ThirdParty/FW1FontWrapper/Inc/FW1FontWrapper.h"

// Ό³Έν :
class UEngineFont : public UEngineResources
{
public:
	// constrcuter destructer
	UEngineFont();
	~UEngineFont();

	// delete Function
	UEngineFont(const UEngineFont& _Other) = delete;
	UEngineFont(UEngineFont&& _Other) noexcept = delete;
	UEngineFont& operator=(const UEngineFont& _Other) = delete;
	UEngineFont& operator=(UEngineFont&& _Other) noexcept = delete;

protected:

private:

};

