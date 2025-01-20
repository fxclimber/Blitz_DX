#pragma once
#include <EngineBase/EngineMath.h>

// Ÿ�ϸʿ� Ưȭ�� Ŭ����, �밢�� �̵�����

// A* ��ã�� �˰��򿡼� ���� ��带 ��Ÿ���� Ŭ����
class UPathFindNode
{
public:
	UPathFindNode* ParentNode;//�θ���
	FVector pos = FVector(0.0f, 0.0f, 0.0f);//�� Ÿ���� ��ġ
	float F = 0.0f; // G + H
	float G = 0.0f; // ���� �� ��ġ���� ������������ �Ÿ�
	float H = 0.0f; // ���� �� ��ġ���� ������������ �Ÿ�

	FVector GetPointToVector()
	{
		return { pos.X, pos.Y, pos.Z };
	}
};

class IPathFindData // �� �̵����ɿ��� �Ǻ� �������̽�
{
public:
	virtual bool IsMove(const FVector& _Point) = 0;// ��ǥ�� �̵������������� Ȯ�� //Ÿ�ϸ�Ŭ������ ���,�����Ұ� 
};

// ��ã�� �˰��� Ŭ���� 
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

	// ���ã�� -> ��ǥ����Ʈ ���� 
	std::list<FVector> PathFind(const FVector& _Start, const FVector& _End);

	void SetData(IPathFindData* _PathFindData)
	{
		PathFindData = _PathFindData;// �̵����ɿ��� üũ , bool IsMove()
	}

protected:

private:
	IPathFindData* PathFindData = nullptr;// �̵����� ���� �������̽�

	std::vector<FVector> WayDir;// �̵����⺤�� 
	// A �˰����� �ٽ� ����Ʈ*
	std::list<UPathFindNode*> OpenList;// Ž���ĺ� ��� ����(�켱���� ť����)
	std::list<UPathFindNode*> CloseList;// �̹� Ž���� ���� �������(��湮 ����)
	// ��ǥ ����, A* Ž������ �޸���ƽ(H) ��꿡 ���
	FVector EndPoint;

	// pool���, �̸������,�������ʴ´� 
	std::vector<UPathFindNode> NodePool;

	int PoolCount = 0;

	void NodeClear()// A Ž���� �ʱ�ȭ
	{
		OpenList.clear();// ����,
		CloseList.clear();
		PoolCount = 0;//���� 
	}
	// ����Ʈ�鿡�� ��ġ���, pos�� �����ϴ��� Ȯ���ϴ� �Լ� 
	bool FindOpenNode(FVector _Point);
	bool FindCloseNode(FVector _Point);

	// ���ο� ����Ҵ�,F,G,H��� , �θ��尡 ������ G������Ʈ, ���� ��带 OpenList�� �߰��ؼ� Ž������ 
	// PathFind() ���� ���� 
	UPathFindNode* GetNewNode(FVector _Point, UPathFindNode* _ParentNode);


};

