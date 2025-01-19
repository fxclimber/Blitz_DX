#pragma once

class UBzFSMManager
{
public:
	UBzFSMManager(){}
	~UBzFSMManager(){}

	// FSM 상태 클래스 - 각 상태의 시작,업뎃,종료기능 정의 
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
			MSGASSERT("이미 존재하는 스테이트를 또 만들려했다")
				return;
		}
		States[_Key].UpdateFunction = _UpdateFunction;
		States[_Key].StartFunction = _StartFunction;
	}

	void Update(float _DeltaTime)
	{
		if (nullptr == CurrentState)
		{
			MSGASSERT("상태가 지정되지 않은 스테이트 머신이다");
			return;
		}
		CurrentState->UpdateFunction(_DeltaTime);
	}
	// 상태생성함수 템플릿 
	template<typename EnumType>
	void ChangeState(EnumType _Key)
	{
		ChangeState(static_cast<int>(_Key));
	}

	void ChageState(int _Key)
	{
		if (false == States.contains(_Key))
		{
			MSGASSERT("만든적 없는 상태로 바꾸려했다");
			return;
		}
		// 현재를 새로운 상태로 변경
		CurrentState = &States[_Key];
		if (nullptr != CurrentState->StartFunction)// 새상태의 시작함수가 존재하면 호출 
		{
			CurrentState->StartFunction();
		}
	}

protected:

private:
	FSMState* CurrentState = nullptr; // 현재 상태를 가리키는 포인터
	std::map<int, FSMState> States;//상태저장하는 맵(정수형 키, FSMState)
};

