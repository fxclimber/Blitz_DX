#pragma once
#include <EngineCore/Renderer.h>
#include <EngineBase/EngineDelegate.h>
#include <unordered_map>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineSerializer.h>

#include "BzRendererDefault.h"


struct BzFTileIndex
{
	union
	{
		struct
		{
			int X;
			int Y;
			int Z;
		};
		__int64 Key;
	};
};


struct BzFTileData
{
	bool IsBlock = false;
	BzFTileIndex Index;
	FResultColor ColorData;
};

class UBzBottomTileRenderer : public UBzRendererDefault, public UEngineSerializer
{
public:
	ENGINEAPI UBzBottomTileRenderer();
	ENGINEAPI ~UBzBottomTileRenderer();

	ENGINEAPI void SetTileSetting( std::string_view _Name, FVector _TileSize);
	ENGINEAPI void SetTile(FVector _Pos, int _Index);
	ENGINEAPI void RemoveTile(FVector _Pos);
	// 없으면 만들어요.
	ENGINEAPI void SetTile(int _X, int _Y, int _Z, int _Index);

	ENGINEAPI void RemoveTile(int _X, int _Y, int _Z);

	BzFTileIndex WorldPosToTileIndex(FVector _Pos);

	FVector TileIndexToWorldPos(BzFTileIndex _Pos);

	// 데이터를 직렬화(압축)
	ENGINEAPI void Serialize(UEngineSerializer& _Ser) override;
	// 데이터를 복구(할때)
	ENGINEAPI void DeSerialize(UEngineSerializer& _Ser) override;

protected:
	ENGINEAPI void Render(class UEngineCamera* _Camera, float _DeltaTime) override;
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;
	void SetPivot(PivotType _pivot);

private:
	bool IsAutoScale = true;
	float AutoScaleRatio = 1.0f;

	FVector TileSize;
	FVector TilePivot;

	std::unordered_map<__int64, BzFTileData> Tiles;
	FResultColor TestColor;

};

