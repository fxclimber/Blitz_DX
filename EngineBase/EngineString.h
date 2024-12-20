#pragma once
#include <string>

// 설명 : 문자열에 관련된 static 함수들만 만들겁니다.
//        헬퍼클래스 문자열에 도움주는 클래스
class UEngineString
{
public:
	// constrcuter destructer
	~UEngineString();

	// delete Function
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;

	ENGINEAPI static std::string ToUpper(std::string_view);

	ENGINEAPI static std::wstring AnsiToUnicode(std::string_view _Name);

private:
	UEngineString();
};

