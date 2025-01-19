#pragma once

class UBzFSMManager
{
public:
	UBzFSMManager(){}
	~UBzFSMManager(){}

	// FSM ���� Ŭ���� - �� ������ ����,����,������ ���� 
	class FSMState
	{
	public:
		std::function<void()> StartFunction = nullptr;
		std::function<void(float)> UpdateFunction = nullptr;
		std::function<void()> EndFunction = nullptr;
	};

	template<typename EnumType>
	void CreateState(EnumType _Key, std::function<void(float)> _UpdateFunction, std::function<void()> _StartFunction = nullptr)
	{

	}
	void CreateState(int _Key, std::function<void(float)> _UpdateFunction, std::function<void()> _StartFunction = nullptr)
	{
		if (true == States.contains(_Key))
		{
			MSGASSERT("�̹� �����ϴ� ������Ʈ�� �� ������ߴ�")
				return;
		}
		States[_Key].UpdateFunction = _UpdateFunction;
		States[_Key].StartFunction = _StartFunction;
	}

	void Update(float _DeltaTime)
	{
		if (nullptr == CurrentState)
		{
			MSGASSERT("���°� �������� ���� ������Ʈ �ӽ��̴�");
			return;
		}
		CurrentState->UpdateFunction(_DeltaTime);
	}
	// ���»����Լ� ���ø� 
	template<typename EnumType>
	void ChangeState(EnumType _Key)
	{
		ChangeState(static_cast<int>(_Key));
	}

	void ChageState(int _Key)
	{
		if (false == States.contains(_Key))
		{
			MSGASSERT("������ ���� ���·� �ٲٷ��ߴ�");
			return;
		}
		// ���縦 ���ο� ���·� ����
		CurrentState = &States[_Key];
		if (nullptr != CurrentState->StartFunction)// �������� �����Լ��� �����ϸ� ȣ�� 
		{
			CurrentState->StartFunction();
		}
	}

protected:

private:
	FSMState* CurrentState = nullptr; // ���� ���¸� ����Ű�� ������
	std::map<int, FSMState> States;//���������ϴ� ��(������ Ű, FSMState)
};

