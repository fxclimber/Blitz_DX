#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>

// 이러한 템플릿 클래스는 아예 헤더에서 다 구현해버리는게 더 속편할수 있다.
template<typename ResType>
class UEngineResources : public UObject
{
public:
	// constrcuter destructer
	UEngineResources() {

	}
	~UEngineResources() {

	}

	// delete Function
	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;

	static std::string ToUpperName(std::string_view _Name)
	{
		return UEngineString::ToUpper(_Name);
	}

	static std::shared_ptr<ResType> Find(std::string_view _Name)
	{
		void* Ptr = &ResMap;

		if (false == ResMap.contains(_Name.data()))
		{
			return nullptr;
		}

		return ResMap[_Name.data()];
	}

	static bool Contains(std::string_view _Name)
	{
		return ResMap.contains(_Name.data());
	}

	static void Release()
	{
		ResMap.clear();
	}


	ENGINEAPI static std::shared_ptr<ResType> MakeRes(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		NewRes->SetName(UpperName);
		NewRes->Path = _Path;
		ResMap.insert({ UpperName, NewRes });

		void* Ptr = &ResMap;

		return NewRes;
	}

protected:
	UEnginePath Path;

private:

	// dll 메모리 분립상황에 대한 해결책
	// 얼록케이터 => 자료구조에서 메모리 할당할때 그 메모리를 어떻게 할당할거야를 
	// 메모리풀이나 이런것들을 따로 자신의 배보다 배꼽이 더 큰 상황이 된다.
	// std::vector<int, 얼록케이터>

	static std::map<std::string, std::shared_ptr<ResType>> ResMap;
};

// 템플릿 static 초기화 방법
template<typename ResType>
std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::ResMap;


