#pragma once
#include <EngineCore/Actor.h>


class ABzBottomTmp : public AActor
{
public:
	ABzBottomTmp();
	~ABzBottomTmp();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class URenderer> RendererBottom;

};

