#include "PreCompile.h"
#include "BzTileMap.h"
#include "BzRendererDefault.h"
#include "PathFindAstar.h"
#include <EngineCore/DefaultSceneComponent.h>

#include <set>


ABzTileMap::ABzTileMap()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	FVector Offset = FVector((GridSize * TileSize) / 2, 0.f, (GridSize * TileSize) / 2);

	// 장애물로 설정할 타일의 인덱스 지정
	std::set<std::pair<int, int>> ObstacleIndices = {
		{12, 15}, {11, 13}, {16, 15}, {10, 10}, {20, 6}, {18, 12}, {11, 3},
		{5, 8}, {23, 17}, {7, 22}, {14, 27}, {28, 5}, {19, 24}, {3, 14}, {21, 9}, {26, 18}
	};

	for (int x = 0; x < GridSize; ++x)
	{
		for (int z = 0; z < GridSize; ++z)
		{
			// 타일 생성 
			ABzTile* BottomTile = GetWorld()->SpawnActor<ABzTile>().get();

			if (nullptr!=BottomTile)
			{
				FVector TilePos = FVector(x * TileSize, 0.f, z * TileSize) - Offset;

				float DistanceFromCenter = FVector(x - GridSize / 2, 0.f, z - GridSize / 2).Length();
				float MaxDistance = FVector(GridSize / 2, 0.f, GridSize / 2).Length();

				float HeightFactor = DistanceFromCenter / MaxDistance;
				float TileHeight = MaxHeight * pow(HeightFactor, 2);

				// 기존 굴곡을 반영한 높이 적용
				TilePos.Y = TileHeight / 2;

				// 장애물인지 확인
				bool isObstacle = (ObstacleIndices.find({ x, z }) != ObstacleIndices.end());

				if (isObstacle)
				{
					BottomTile->SetActorRelativeScale3D(FVector(TileSize, TileSize * 1.5f, TileSize)); // 크기 증가
					TilePos.Y -= TileSize * 0.8f; // 기존 높이에 추가 (덮어쓰기 X)
					BottomTile->GetRenderer()->GetRenderUnit().SetTexture("bz_teXture0", "test10.png");
				}
				else
				{
					BottomTile->SetActorRelativeScale3D(FVector(TileSize, TileSize * 0.2f, TileSize)); // 기본 크기
				}

				BottomTile->SetActorLocation(TilePos);
				BottomTiles.push_back(BottomTile);

				UPathFindNode* NewNode = new UPathFindNode();
				NewNode->pos = TilePos;
				TileNodes[TilePos] = NewNode;

				std::string DebugMessage =
					"Tile [" + std::to_string(x) + ", " + std::to_string(z) + "] -> " +
					"Pos: (" + std::to_string(TilePos.X) + ", " +
					std::to_string(TilePos.Y) + ", " +
					std::to_string(TilePos.Z) + ")";

				UEngineDebug::OutPutString(DebugMessage);
			}
		}
	}

	for (int x = 0; x < GridSize; ++x)
	{
		for (int z = 0; z < GridSize; ++z)
		{
			FVector TilePos = FVector(x * TileSize, 0.f, z * TileSize) - Offset;

			UPathFindNode* NewNode = new UPathFindNode();
			NewNode->pos = TilePos;
			TileNodes[TilePos] = NewNode;
		}
	}


}

ABzTileMap::~ABzTileMap(){}

bool ABzTileMap::IsMove(const FVector& _Point)
{
	for (ABzTile* Tile : BottomTiles)
	{
		if (Tile->GetPos().X == _Point.X && Tile->GetPos().Z == _Point.Z) // 어떻게 에너미와,타일위치가 같을수있냐,플롯인데..
		{
			return Tile->IsWalkable();
		}
	}// 위 조건식 잘못됬음, 일단 참으로 리턴하고 후에 코드수정할것 
	return true; // 타일이 없으면 이동 불가
}

UPathFindNode* ABzTileMap::GetNode(const FVector& _Point)
{
	float TileSize = ABzTileMap::TileSize;
	FVector TileCoord = FVector(round(_Point.X / TileSize) * TileSize,0.f,round(_Point.Z / TileSize) * TileSize);
	auto it = TileNodes.find(TileCoord);

	if (it != TileNodes.end())	{return it->second;	}

	return nullptr;
}


void ABzTileMap::BeginPlay()
{
	AActor::BeginPlay();

}

void ABzTileMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}
