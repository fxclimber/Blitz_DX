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

	ENGINEAPI static std::string InterString(const std::string& _Text, std::string_view _Start, std::string_view _End, size_t& _Offset);

	ENGINEAPI static std::wstring AnsiToUnicode(std::string_view _Name);

	ENGINEAPI static std::string UniCodeToUTF8(std::wstring_view _Name);

	ENGINEAPI static std::string AnsiToUTF8(std::string_view _Name);

private:
	UEngineString();
};

