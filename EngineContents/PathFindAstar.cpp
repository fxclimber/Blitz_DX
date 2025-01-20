#include "PreCompile.h"
#include "PathFindAStar.h"
#include <algorithm>

UPathFindAStar::UPathFindAStar()
{
	NodePool.resize(1000);
	PoolCount = 0;
	WayDir = {
		{1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}, // 상하좌우
		{1, 0, 1}, {1, 0, -1}, {-1, 0, 1}, {-1, 0, -1} // 대각선 이동
	};
}

UPathFindAStar::~UPathFindAStar()
{
}

bool Comp(UPathFindNode* first, UPathFindNode* second)
{
	if (first->F < second->F) // F값이 작은 노드를 우선적으로 선택 -> 최단경로 
	{
		return true;
	}
	else
	{
		return false;
	}
}


// 시작~끝의 최적경로 찾기 // 내부적으로 OpenList, CloseList를 사용해 탐색 진행 <- G, H, F 값을 계산
std::list<FVector> UPathFindAStar::PathFind(const FVector& _Start, const FVector& _End)
{
	// 1. 초기화 
	NodeClear();
	EndPoint = _End;
	GetNewNode(_Start, nullptr);// 시작노드를 OpenList에 추가

	UPathFindNode* ResultNode = nullptr;

	// 2. 탐색 루프 
	while (true)
	{
		if (OpenList.empty())//OpenList가 비었으면 종료 (경로 없음)
		{
			break;
		}

		OpenList.sort(Comp);// Comp(비교 함수)를 사용해 F 값이 작은 순서대로 정렬

		// 가장 좋은 노드를 CurNode로 선택
		UPathFindNode* CurNode = OpenList.front();// OpenList 의 맨앞노드를 가져옴 
		OpenList.pop_front();// OpenList에서 제거하고,
		CloseList.push_back(CurNode); // CloseList에 추가 

		// 3. 인접타일 탐색 
		FVector CheckPoint = { 0.f , 0.f , 0.f };

		for (size_t i = 0; i < WayDir.size(); i++)// (8방향 이동 벡터)을 사용하여 현재 노드 주변의 이동 가능한 좌표(CheckPoint)를 계산.
		{
			CheckPoint = CurNode->pos + WayDir[i];

			if (false == PathFindData->IsMove(CheckPoint))
			{
				continue;//false이면 해당 위치는 벽 또는 장애물이므로 탐색하지 않음.
			}

			if (true == FindCloseNode(CheckPoint))
			{
				continue;//CloseList에 있는 노드는 이미 최적 경로를 평가했으므로 다시 검사할 필요 없음.
			}

			if (true == FindOpenNode(CheckPoint))
			{
				continue;//OpenList에 있는 노드는 이미 탐색 후보에 포함되었으므로 중복 추가하지 않음.
			}

			if (CheckPoint == EndPoint)
			{
				break;//현재 탐색 중인 노드가 EndPoint에 도착하면 탐색 종료.
			}

			GetNewNode(CheckPoint, CurNode);//새로운 탐색 노드를 추가하고 부모 노드를 CurNode로 설정 <- 역추적때 사용 
		}

		// 목적지에 도달했다는 것이므로 종료한다.
		if (CheckPoint == EndPoint)
		{
			ResultNode = CurNode;
			break;
		}


	}

	// 4. 경로 재구성 
	std::list<FVector> Result;

	 //ResultNode= 도착지점 근처
	if (nullptr != ResultNode)
	{
		while (nullptr != ResultNode)
		{
			Result.push_front(ResultNode->pos);//경로가 순서대로 저장

			ResultNode = ResultNode->ParentNode;
		}
	}

	// 탐색이 성공하면 _Start → _End까지의 최적 경로 리스트(std::list<FVector>)를 반환
	return Result;
}


// OpenList 에 같은 좌표있는지 검색 
bool UPathFindAStar::FindOpenNode(FVector _Point)
{
	std::list<UPathFindNode*>::iterator StartIter = OpenList.begin();
	std::list<UPathFindNode*>::iterator Enditer = OpenList.end();

	for (; StartIter != Enditer; ++StartIter)
	{
		if ((*StartIter)->pos == _Point)
		{
			return true;
		}
	}
	return false;
}

// CloseList 에 같은 좌표있는지 검색 -> 재방문 방지하기위해 
bool UPathFindAStar::FindCloseNode(FVector _Point)
{
	std::list<UPathFindNode*>::iterator StartIter = CloseList.begin();
	std::list<UPathFindNode*>::iterator Enditer = CloseList.end();

	for (; StartIter != Enditer; ++StartIter)
	{
		if ((*StartIter)->pos == _Point)
		{
			return true;
		}
	}
	return false;
}

UPathFindNode* UPathFindAStar::GetNewNode(FVector _Point, UPathFindNode* _ParentNode)
{

	//if (PoolCount >= NodePool.size())
	//{
	//	return nullptr;
	//}
	UPathFindNode* NewNode = &NodePool[PoolCount]; // 미리 할당된 노드 풀에서 가져옴
	NewNode->ParentNode = nullptr;
	NewNode->pos = _Point;
	NewNode->ParentNode = _ParentNode;

	FVector ThisPos = NewNode->GetPointToVector();

	if (nullptr != _ParentNode)
	{
		FVector ParentPos = _ParentNode->GetPointToVector();
		NewNode->G = _ParentNode->G + (ThisPos - ParentPos).Length(); // G 계산
	}

	FVector EndPos = { EndPoint.X, 0.f , EndPoint.Z }; // 목표점 좌표
	NewNode->H = (EndPos - ThisPos).Length(); // H 계산
	NewNode->F = NewNode->H + NewNode->G; // F = G + H

	OpenList.push_back(NewNode); // OpenList에 추가
	++PoolCount;
	return NewNode;
}
