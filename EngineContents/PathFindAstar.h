#pragma once
#include <EngineBase/EngineMath.h>

// 타일맵에 특화된 클래스, 대각선 이동가능

// A* 길찾기 알고리즘에서 개별 노드를 나타내는 클래스
class UPathFindNode
{
public:
	UPathFindNode* ParentNode;//부모노드
	FVector pos = FVector(0.0f, 0.0f, 0.0f);//각 타일의 위치
	float F = 0.0f; // G + H
	float G = 0.0f; // 현재 내 위치에서 시작지점과의 거리
	float H = 0.0f; // 현재 내 위치에서 도착지점과의 거리

	FVector GetPointToVector()
	{
		return { pos.X, pos.Y, pos.Z };
	}
};

class IPathFindData // 맵 이동가능여부 판별 인터페이스
{
public:
	virtual bool IsMove(const FVector& _Point) = 0;// 좌표가 이동가능지역인지 확인 //타일맵클래스는 상속,구현할것 
};

// 길찾기 알고리즘 클래스 
class UPathFindAStar
{
public:
	UPathFindAStar();
	~UPathFindAStar();

	// delete Function
	UPathFindAStar(const UPathFindAStar& _Other) = delete;
	UPathFindAStar(UPathFindAStar&& _Other) noexcept = delete;
	UPathFindAStar& operator=(const UPathFindAStar& _Other) = delete;
	UPathFindAStar& operator=(UPathFindAStar&& _Other) noexcept = delete;

	// 경로찾기 -> 좌표리스트 리턴 
	std::list<FVector> PathFind(const FVector& _Start, const FVector& _End);

	void SetData(IPathFindData* _PathFindData)
	{
		PathFindData = _PathFindData;// 이동가능여부 체크 , bool IsMove()
	}

protected:

private:
	IPathFindData* PathFindData = nullptr;// 이동가능 여부 인터페이스

	std::vector<FVector> WayDir;// 이동방향벡터 
	// A 알고리즘의 핵심 리스트*
	std::list<UPathFindNode*> OpenList;// 탐색후보 노드 저장(우선순위 큐역할)
	std::list<UPathFindNode*> CloseList;// 이미 탐색이 끝난 노드저장(재방문 금지)
	// 목표 지점, A* 탐색에서 휴리스틱(H) 계산에 사용
	FVector EndPoint;

	// pool방식, 미리만들고,지우지않는다 
	std::vector<UPathFindNode> NodePool;

	int PoolCount = 0;

	void NodeClear()// A 탐색을 초기화
	{
		OpenList.clear();// 비우고,
		CloseList.clear();
		PoolCount = 0;//리셋 
	}
	// 리스트들에서 위치노드, pos가 존재하는지 확인하는 함수 
	bool FindOpenNode(FVector _Point);
	bool FindCloseNode(FVector _Point);

	// 새로운 노드할당,F,G,H계산 , 부모노드가 있으면 G업데이트, 계산된 노드를 OpenList에 추가해서 탐색진행 
	// PathFind() 에서 사용됨 
	UPathFindNode* GetNewNode(FVector _Point, UPathFindNode* _ParentNode);


};

