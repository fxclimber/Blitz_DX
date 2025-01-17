#pragma once
#include <EngineCore/GameInstance.h>
#include "GMStruct.h"
#include <EngineCore/Widget.h>

// Ό³Έν :
class MyGameInstance : public UGameInstance
{
public:
	// constrcuter destructer
	MyGameInstance();
	~MyGameInstance();

	// delete Function
	MyGameInstance(const MyGameInstance& _Other) = delete;
	MyGameInstance(MyGameInstance&& _Other) noexcept = delete;
	MyGameInstance& operator=(const MyGameInstance& _Other) = delete;
	MyGameInstance& operator=(MyGameInstance&& _Other) noexcept = delete;

	PlayerStatus Status;

	UWidget* InvenWidget;

protected:

private:
};

