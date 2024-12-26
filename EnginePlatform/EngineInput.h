#pragma once
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

#include <vector>
#include <functional>

// 싱글톤의 정의

// 디자인 패턴을 정의할때 4가지 부류를 만들었다.
// 관리패턴, xx패턴, xx패턴, 생성패턴
// 갱오브포가 싱글톤을 설명할때 다음과 같이 적어놨다.
// 싱글톤이란 객체를 프로그램을 통틀어서 절대 1개이상 생기지 못하게 하기 위한 패턴이다.
// 즉 이거 이외의 

// 싱글톤 할때 하면 안되는 말 
// 1. 값을 편하게 공유하려고 싱글톤을 썼다 => 안되죠.

// 1. 생성자를 private으로 막습니다.

// 어떤 클래스를 만들었다. 
// EngineWindow를 생각해보자. 
// 여기에서 싱글톤을 설명하겠다.
// 설명 : 

enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};

class UEngineInput
{
public:
	// constrcuter destructer
	~UEngineInput();

	// delete Function
	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;


	// 외부에 공개하기는 싫다.
private:
	class UEngineKey
	{
	public:
		int Key = -1;

		// 키가 안눌리다가 처음 눌렸을때
		bool IsDown = false;

		// 키가 눌린 이후로 계속 누르고 있을때
		bool IsPress = false;

		// 키가 눌리다가 땠을때
		bool IsUp = false;

		// 키가 안누르고 있을때
		bool IsFree = true;

		float PressTime = 0.0f;
		float FreeTime = 0.0f;

		std::vector<std::function<void()>> PressEvents;
		std::vector<std::function<void()>> DownEvents;
		std::vector<std::function<void()>> UpEvents;
		std::vector<std::function<void()>> FreeEvents;


		// 벡터나 리스트를 사용하면 에러가 난다.
		// 학생들이 대처를 못하는데
		// 결국 맨위로 올라가면 됩니다.

		UEngineKey()
		{
		}

		UEngineKey(int _Key)
			: Key(_Key)
		{
		}

		void EventCheck();

		void KeyCheck(float _DeltaTime);
		
	};

	ENGINEAPI static UEngineInput& GetInst();
	ENGINEAPI static void EventCheck(float _DeltaTime);

public:
	ENGINEAPI static void KeyCheck(float _DeltaTime);

	// UEngineInput::GetInst().IsDown('A')

	bool IsDoubleClick(int _KeyIndex, float _Time)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[_KeyIndex].IsDown && Keys[_KeyIndex].FreeTime < _Time;
	}

	static bool IsDown(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		// 
		// Keys[_KeyIndex] => 없으면 내부에서 노드를 만든다.
		// UMapNode
		// {
		//     UEngineKey Value = UEngineKey();
		// }

		return GetInst().Keys[_KeyIndex].IsDown;
	}

	bool IsUp(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInst().Keys[_KeyIndex].IsUp;
	}

	static bool IsPress(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInst().Keys[_KeyIndex].IsPress;
	}

	float IsPressTime(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInst().Keys[_KeyIndex].PressTime;
	}


	bool IsFree(int _KeyIndex)
	{
		if (false == GetInst().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInst().Keys[_KeyIndex].IsFree;
	}

	void BindAction(int _KeyIndex, KeyEvent _EventType,  std::function<void()> _Function);

protected:

private:
	// 이러면 값형
	// static 값형 변수 선언하고 
	// 지울필요 없다.
	// static UEngineInput Inst;
	
	// 포인터형
	// static UEngineInput* Inst;

	// 싱글톤의 정의
	// 싱글톤 만들기 1
	// 1. 생성자를 private으로 막습니다.

	// 100개까지는 
	std::map<int, UEngineKey> Keys;

	UEngineInput();

};

