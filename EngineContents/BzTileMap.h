#pragma once
#include <EngineCore/Actor.h>
#include "BzRendererDefault.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>
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

	FVector GetPos() const { return TilePos; }
	void SetPos(const FVector& _newPos) { TilePos = _newPos; }
	bool IsWalkable() const { return bIsWalkable;  }
	void SetWalkable(bool _bWalkable) { bIsWalkable = _bWalkable; }

	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UBzRendererDefault> BzTileRenderer;

protected:

private:
	FVector TilePos;
	bool bIsWalkable;
	int Index;
};




class ABzTileMap : public AActor , public IPathFindData
{
public:
	ABzTileMap();
	~ABzTileMap();
	bool IsMove(const FVector& _Point) override;
	// fvector 를 타일 인덱스로 변경해주는 함수 
	UPathFindNode* GetNode(const FVector& _Point);

	//const int GridCount = 1;
	const int GridCount = 30;
	const float TileScale = 200.f;
	const float MaxHeight = 1500.f; // 외곽에서 최대 높이

	FVector MapOffset = FVector::ZERO;

	std::vector<ABzTile*> BottomTiles;
	//std::vector<std::vector<ABzTile*>> Tiles;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	std::map<FVector, UPathFindNode*, FVectorCompare> TileNodes;
	bool bHasLoggedTiles = false; // 중복 출력 방지

};

