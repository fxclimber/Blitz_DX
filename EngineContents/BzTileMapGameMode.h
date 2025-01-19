#pragma once
#include <EngineCore/GameMode.h>

class ABzTileMapGameMode : public AGameMode
{
public:
	ABzTileMapGameMode();
	~ABzTileMapGameMode(){}

	ABzTileMapGameMode(const ABzTileMapGameMode& _Other) = delete;
	ABzTileMapGameMode(ABzTileMapGameMode&& _Other) noexcept = delete;
	ABzTileMapGameMode& operator=(const ABzTileMapGameMode& _Other) = delete;
	ABzTileMapGameMode& operator=(ABzTileMapGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

protected:
	void LevelChangeStart() override;

private:
	std::shared_ptr<class UTileMap> TileMapWindow;//게임모드가 가진,타일맵 에디터윈도우

	std::shared_ptr<class UBzBottomTileRenderer> BzBottomTileRenderer;
};
