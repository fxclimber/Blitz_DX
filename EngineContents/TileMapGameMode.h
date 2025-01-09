#pragma once
#include <EngineCore/GameMode.h>

// 설명 :
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
};

//
//// 삼각형 하나
//struct FNaviData
//{
//	int Index;
//
//	FVector Arr[3];
//
//	int ArrIndex[3];
//
//	// std::vector<FNaviData*> LinkArr;
//	// std::vector<int> Arr;
//
//	void Intersect(AActor* Player, float& Dis)
//	{
//		// DirectX::TriangleTests::Intersects()
//	}
//};
//
//class ANaviMeshManager : AActor
//{
//	std::vector<FNaviData> Data;
//
//	void LoadModel(std::string_view _Path)
//	{
//		std::vector<FVector> AllVector;
//	}
//
//	// 연결을 만들어주면 됩니다.
//	void LinkProgress();
//};
//
//class Player
//{
//	FNaviData* CurNaviMesh;
//};