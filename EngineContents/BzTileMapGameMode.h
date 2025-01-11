#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ABzTileMapGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ABzTileMapGameMode();
	~ABzTileMapGameMode();

	// delete Function
	ABzTileMapGameMode(const ABzTileMapGameMode& _Other) = delete;
	ABzTileMapGameMode(ABzTileMapGameMode&& _Other) noexcept = delete;
	ABzTileMapGameMode& operator=(const ABzTileMapGameMode& _Other) = delete;
	ABzTileMapGameMode& operator=(ABzTileMapGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

protected:
	void LevelChangeStart() override;

private:
	std::shared_ptr<class UTileMap> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};
