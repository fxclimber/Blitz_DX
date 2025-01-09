#pragma once
#include "AMon.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWinImage.h>

// 설명 :
class AMonster2 : public AMon
{
public:
	// constrcuter destructer
	AMonster2();
	~AMonster2();

	// delete Function
	AMonster2(const AMonster2& _Other) = delete;
	AMonster2(AMonster2&& _Other) noexcept = delete;
	AMonster2& operator=(const AMonster2& _Other) = delete;
	AMonster2& operator=(AMonster2&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return Renderer;
	}

	// 데이터를 직렬화(압축)
	void Serialize(UEngineSerializer& _Ser) override;
	// 데이터를 복구(할때)
	void DeSerialize(UEngineSerializer& _Ser) override;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	std::shared_ptr<class USpriteRenderer> Renderer;

	std::shared_ptr<class UCollision> Collision;
};

