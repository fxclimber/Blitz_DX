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
	std::shared_ptr<class UTileMap> TileMapWindow;//���Ӹ�忡�� ������ �����ְ�

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;

	std::shared_ptr<class UBzRendererDefault> BzRendererDefault;
};
