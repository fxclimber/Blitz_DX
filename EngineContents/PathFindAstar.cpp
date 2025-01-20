#include "PreCompile.h"
#include "PathFindAStar.h"
#include <algorithm>

UPathFindAStar::UPathFindAStar()
{
	NodePool.resize(1000);
	PoolCount = 0;
	WayDir = {
		{1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}, // �����¿�
		{1, 0, 1}, {1, 0, -1}, {-1, 0, 1}, {-1, 0, -1} // �밢�� �̵�
	};
}

UPathFindAStar::~UPathFindAStar()
{
}

bool Comp(UPathFindNode* first, UPathFindNode* second)
{
	if (first->F < second->F) // F���� ���� ��带 �켱������ ���� -> �ִܰ�� 
	{
		return true;
	}
	else
	{
		return false;
	}
}


// ����~���� ������� ã�� // ���������� OpenList, CloseList�� ����� Ž�� ���� <- G, H, F ���� ���
std::list<FVector> UPathFindAStar::PathFind(const FVector& _Start, const FVector& _End)
{
	// 1. �ʱ�ȭ 
	NodeClear();
	EndPoint = _End;
	GetNewNode(_Start, nullptr);// ���۳�带 OpenList�� �߰�

	UPathFindNode* ResultNode = nullptr;

	// 2. Ž�� ���� 
	while (true)
	{
		if (OpenList.empty())//OpenList�� ������� ���� (��� ����)
		{
			break;
		}

		OpenList.sort(Comp);// Comp(�� �Լ�)�� ����� F ���� ���� ������� ����

		// ���� ���� ��带 CurNode�� ����
		UPathFindNode* CurNode = OpenList.front();// OpenList �� �Ǿճ�带 ������ 
		OpenList.pop_front();// OpenList���� �����ϰ�,
		CloseList.push_back(CurNode); // CloseList�� �߰� 

		// 3. ����Ÿ�� Ž�� 
		FVector CheckPoint = { 0.f , 0.f , 0.f };

		for (size_t i = 0; i < WayDir.size(); i++)// (8���� �̵� ����)�� ����Ͽ� ���� ��� �ֺ��� �̵� ������ ��ǥ(CheckPoint)�� ���.
		{
			CheckPoint = CurNode->pos + WayDir[i];

			if (false == PathFindData->IsMove(CheckPoint))
			{
				continue;//false�̸� �ش� ��ġ�� �� �Ǵ� ��ֹ��̹Ƿ� Ž������ ����.
			}

			if (true == FindCloseNode(CheckPoint))
			{
				continue;//CloseList�� �ִ� ���� �̹� ���� ��θ� �������Ƿ� �ٽ� �˻��� �ʿ� ����.
			}

			if (true == FindOpenNode(CheckPoint))
			{
				continue;//OpenList�� �ִ� ���� �̹� Ž�� �ĺ��� ���ԵǾ����Ƿ� �ߺ� �߰����� ����.
			}

			if (CheckPoint == EndPoint)
			{
				break;//���� Ž�� ���� ��尡 EndPoint�� �����ϸ� Ž�� ����.
			}

			GetNewNode(CheckPoint, CurNode);//���ο� Ž�� ��带 �߰��ϰ� �θ� ��带 CurNode�� ���� <- �������� ��� 
		}

		// �������� �����ߴٴ� ���̹Ƿ� �����Ѵ�.
		if (CheckPoint == EndPoint)
		{
			ResultNode = CurNode;
			break;
		}


	}

	// 4. ��� �籸�� 
	std::list<FVector> Result;

	 //ResultNode= �������� ��ó
	if (nullptr != ResultNode)
	{
		while (nullptr != ResultNode)
		{
			Result.push_front(ResultNode->pos);//��ΰ� ������� ����

			ResultNode = ResultNode->ParentNode;
		}
	}

	// Ž���� �����ϸ� _Start �� _End������ ���� ��� ����Ʈ(std::list<FVector>)�� ��ȯ
	return Result;
}


// OpenList �� ���� ��ǥ�ִ��� �˻� 
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

// CloseList �� ���� ��ǥ�ִ��� �˻� -> ��湮 �����ϱ����� 
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
	UPathFindNode* NewNode = &NodePool[PoolCount]; // �̸� �Ҵ�� ��� Ǯ���� ������
	NewNode->ParentNode = nullptr;
	NewNode->pos = _Point;
	NewNode->ParentNode = _ParentNode;

	FVector ThisPos = NewNode->GetPointToVector();

	if (nullptr != _ParentNode)
	{
		FVector ParentPos = _ParentNode->GetPointToVector();
		NewNode->G = _ParentNode->G + (ThisPos - ParentPos).Length(); // G ���
	}

	FVector EndPos = { EndPoint.X, 0.f , EndPoint.Z }; // ��ǥ�� ��ǥ
	NewNode->H = (EndPos - ThisPos).Length(); // H ���
	NewNode->F = NewNode->H + NewNode->G; // F = G + H

	OpenList.push_back(NewNode); // OpenList�� �߰�
	++PoolCount;
	return NewNode;
}
