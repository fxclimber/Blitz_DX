#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATileMapGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATileMapGameMode();
	~ATileMapGameMode();

	// delete Function
	ATileMapGameMode(const ATileMapGameMode& _Other) = delete;
	ATileMapGameMode(ATileMapGameMode&& _Other) noexcept = delete;
	ATileMapGameMode& operator=(const ATileMapGameMode& _Other) = delete;
	ATileMapGameMode& operator=(ATileMapGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

protected:
	void LevelChangeStart() override;

private:
	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};
