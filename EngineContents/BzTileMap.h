#pragma once
#include <EngineCore/Actor.h>
#include "BzRendererDefault.h"
#include <EngineCore/DefaultSceneComponent.h>

#include "PathFindAstar.h"

#include <map>
#include <functional>

struct FVectorCompare
{
	bool operator()(const FVector& A, const FVector& B) const
	{
		if (A.X != B.X) return A.X < B.X;
		if (A.Y != B.Y) return A.Y < B.Y;
		return A.Z < B.Z;
	}
};

class ABzTile : public AActor
{
public:
	ABzTile()
		: TilePos(0.0f, 0.0f, 0.0f), bIsWalkable(true)
	{
		std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
		RootComponent = Default;

		BzTileRenderer = CreateDefaultSubObject<UBzRendererDefault>();
		BzTileRenderer->SetupAttachment(RootComponent);
		BzTileRenderer->SetMesh("cube");
		BzTileRenderer->SetPivot(PivotType::Bottom);
		BzTileRenderer->GetRenderUnit().SetMaterial("BzDefault");
		BzTileRenderer->GetRenderUnit().SetTexture("bz_teXture0", "test09.png");
	}

	std::shared_ptr<class UBzRendererDefault> GetRenderer()
	{
		return BzTileRenderer;
	}

	FVector GetPos() const { return TilePos; }
	void SetPos(const FVector& _newPos) { TilePos = _newPos; }
	bool IsWalkable() const { return bIsWalkable;  }
	void SetWalkable(bool _bWalkable) { bIsWalkable = _bWalkable; }

protected:

private:
	std::shared_ptr<class UBzRendererDefault> BzTileRenderer;
	FVector TilePos;
	bool bIsWalkable;

};




class ABzTileMap : public AActor , public IPathFindData
{
public:
	ABzTileMap();
	~ABzTileMap();
	bool IsMove(const FVector& _Point) override;
	UPathFindNode* GetNode(const FVector& _Point);

	const int GridSize = 30;
	const float TileSize = 200.f;
	const float MaxHeight = 1500.f; // 외곽에서 최대 높이

	std::vector<ABzTile*> BottomTiles;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	std::map<FVector, UPathFindNode*, FVectorCompare> TileNodes;
	bool bHasLoggedTiles = false; // 중복 출력 방지

};

