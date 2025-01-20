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

	// ��ֹ��� ������ Ÿ���� �ε��� ����
	std::set<std::pair<int, int>> ObstacleIndices = {
		{12, 15}, {11, 13}, {16, 15}, {10, 10}, {20, 6}, {18, 12}, {11, 3},
		{5, 8}, {23, 17}, {7, 22}, {14, 27}, {28, 5}, {19, 24}, {3, 14}, {21, 9}, {26, 18}
	};

	for (int x = 0; x < GridSize; ++x)
	{
		for (int z = 0; z < GridSize; ++z)
		{
			// Ÿ�� ���� 
			ABzTile* BottomTile = GetWorld()->SpawnActor<ABzTile>().get();

			if (nullptr!=BottomTile)
			{
				FVector TilePos = FVector(x * TileSize, 0.f, z * TileSize) - Offset;

				float DistanceFromCenter = FVector(x - GridSize / 2, 0.f, z - GridSize / 2).Length();
				float MaxDistance = FVector(GridSize / 2, 0.f, GridSize / 2).Length();

				float HeightFactor = DistanceFromCenter / MaxDistance;
				float TileHeight = MaxHeight * pow(HeightFactor, 2);

				// ���� ������ �ݿ��� ���� ����
				TilePos.Y = TileHeight / 2;

				// ��ֹ����� Ȯ��
				bool isObstacle = (ObstacleIndices.find({ x, z }) != ObstacleIndices.end());

				if (isObstacle)
				{
					BottomTile->SetActorRelativeScale3D(FVector(TileSize, TileSize * 1.5f, TileSize)); // ũ�� ����
					TilePos.Y -= TileSize * 0.8f; // ���� ���̿� �߰� (����� X)
					BottomTile->GetRenderer()->GetRenderUnit().SetTexture("bz_teXture0", "test10.png");
				}
				else
				{
					BottomTile->SetActorRelativeScale3D(FVector(TileSize, TileSize * 0.2f, TileSize)); // �⺻ ũ��
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
		if (Tile->GetPos().X == _Point.X && Tile->GetPos().Z == _Point.Z) // ��� ���ʹ̿�,Ÿ����ġ�� �������ֳ�,�÷��ε�..
		{
			return Tile->IsWalkable();
		}
	}// �� ���ǽ� �߸�����, �ϴ� ������ �����ϰ� �Ŀ� �ڵ�����Ұ� 
	return true; // Ÿ���� ������ �̵� �Ұ�
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
