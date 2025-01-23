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

	// 게임모드에서 원점을 중심으로 하도록 캐릭터,카메라 옵셋시킬 값
	MapOffset = FVector((GridCount * TileScale) / 2, MaxHeight, (GridCount * TileScale) / 2);
	FVector Offset = FVector::ZERO;

	// 장애물로 설정할 타일의 인덱스 지정
	std::set<std::pair<int, int>> ObstacleIndices = {
		{12, 15}, {11, 13}, {16, 15}, {10, 10}, {20, 6}, {18, 12}, {11, 3},
		{5, 8}, {23, 17}, {7, 22}, {14, 27}, {28, 5}, {19, 24}, {3, 14}, {21, 9}, {26, 18}
	};

	for (int x = 0; x < GridCount; ++x)
	{
		for (int z = 0; z < GridCount; ++z)
		{
			// 타일 생성 
			ABzTile* BottomTile = GetWorld()->SpawnActor<ABzTile>().get();

			if (nullptr != BottomTile)
			{
				FVector TilePos = FVector(x * TileScale, 0.f, z * TileScale) - Offset;

				float DistanceFromCenter = FVector(x - GridCount / 2, 0.f, z - GridCount / 2).Length();
				float MaxDistance = FVector(GridCount / 2, 0.f, GridCount / 2).Length();

				float HeightFactor = DistanceFromCenter / MaxDistance;
				float TileHeight = MaxHeight * pow(HeightFactor, 2);

				// 기존 굴곡을 반영한 높이 적용
				TilePos.Y = TileHeight / 2;

				// 장애물인지 확인
				bool isObstacle = (ObstacleIndices.find({ x, z }) != ObstacleIndices.end());

				if (isObstacle)
				{
					BottomTile->SetActorRelativeScale3D(FVector(TileScale, TileScale * 1.5f, TileScale)); // 크기 증가
					TilePos.Y -= TileScale * 0.8f; // 기존 높이에 추가 (덮어쓰기 X)
					BottomTile->BzTileRenderer->GetRenderUnit().SetTexture("bz_teXture0", "test10.png");
					BottomTile->SetWalkable(false);
					// 터진다
					//BottomTile->Collision = CreateDefaultSubObject<UCollision>();
					//BottomTile->Collision->SetupAttachment(BottomTile->BzTileRenderer);
					//BottomTile->Collision->SetCollisionProfileName("Wall");
					//BottomTile->Collision->SetCollisionType(ECollisionType::OBB);

				}
				else
				{
					BottomTile->SetActorRelativeScale3D(FVector(TileScale, TileScale * 0.2f, TileScale)); // 기본 크기
					BottomTile->SetWalkable(true);
				}

				BottomTile->SetActorLocation(TilePos);
				BottomTiles.push_back(BottomTile);

				UPathFindNode* NewNode = new UPathFindNode();
				NewNode->pos = TilePos;
				TileNodes[TilePos] = NewNode;

				//std::string DebugMessage =
				//	"Tile [" + std::to_string(x) + ", " + std::to_string(z) + "] -> " +
				//	"Pos: (" + std::to_string(TilePos.X) + ", " +
				//	std::to_string(TilePos.Y) + ", " +
				//	std::to_string(TilePos.Z) + ")";
				//UEngineDebug::OutPutString(DebugMessage);

			}
		}
	}

	for (int x = 0; x < GridCount; ++x)
	{
		for (int z = 0; z < GridCount; ++z)
		{
			FVector TilePos = FVector(x * TileScale, 0.f, z * TileScale) - Offset;

			UPathFindNode* NewNode = new UPathFindNode();
			NewNode->pos = TilePos;
			TileNodes[TilePos] = NewNode;
		}
	}


}

ABzTileMap::~ABzTileMap() {
	for (auto NodePair : TileNodes)
	{
		delete NodePair.second;
	}
}

bool ABzTileMap::IsMove(const FVector& _Point)
{
	FVector CheckPos = _Point;
	int X = std::floor(_Point.X / TileScale); 
	int Z = std::floor(_Point.Z / TileScale); 	
	// BottomTiles 자료구조 잘못만들었다.그래서 이 조건식은 잘못된 상태다.고쳐라 
	bool move = BottomTiles[X][Z].IsWalkable();
	if (false == move)
	{
		return false;
	}
	return true;
}

UPathFindNode* ABzTileMap::GetNode(const FVector& _Point)
{
	float TileScale = ABzTileMap::TileScale;
	FVector TileCoord = FVector(round(_Point.X / TileScale) * TileScale, 0.f, round(_Point.Z / TileScale) * TileScale);
	auto it = TileNodes.find(TileCoord);

	if (it != TileNodes.end()) { return it->second; }

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
