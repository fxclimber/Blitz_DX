#include "PreCompile.h"
#include "EngineDirectory.h"
#include "EngineFile.h"
#include "EngineDebug.h"

UEngineDirectory::UEngineDirectory()
	: UEnginePath()
{
	// 만들어지면 현재로 
}

UEngineDirectory::UEngineDirectory(std::string_view _Path)
	: UEnginePath(_Path)
{

}

UEngineDirectory::UEngineDirectory(std::filesystem::path _Path)
	: UEnginePath(_Path)
{

}


UEngineDirectory::~UEngineDirectory()
{
}


std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecursive /*= true*/)
{
	std::vector<class UEngineFile> Result;

	// 경로를 넣어주면 그 경로의 첫번째 파일을 가리키게 된다.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	while (false == Diriter._At_end())
	{
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			if (true == _IsRecursive)
			{
				GetAllFileRecursive(FilePath, Result);
			}

			++Diriter;
			continue;
		}

		Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}

	return Result;
}

std::vector<class UEngineDirectory> UEngineDirectory::GetAllDirectory()
{
	std::vector<class UEngineDirectory> Result;

	// 경로를 넣어주면 그 경로의 첫번째 파일을 가리키게 된다.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	while (false == Diriter._At_end())
	{
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);
		if (false == Path.IsDirectory())
		{
			++Diriter;
			continue;
		}

		Result.push_back(UEngineDirectory(FilePath));
		++Diriter;
	}

	return Result;
}


void UEngineDirectory::GetAllFileRecursive(std::filesystem::path _Path
	, std::vector<class UEngineFile>& _Result)
{
	// 경로를 넣어주면 그 경로의 첫번째 파일을 가리키게 된다.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(_Path);

	while (false == Diriter._At_end())
	{
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			GetAllFileRecursive(FilePath, _Result);
			++Diriter;
			continue;
		}

		_Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}
}

UEngineFile UEngineDirectory::GetFile(std::string_view _FileName)
{
	UEnginePath FilePath = Path;
	FilePath.Append(_FileName);

	if (false == FilePath.IsExists())
	{
		MSGASSERT("존재하지 않는 파일을 객체화하려고 했습니다.");
	}

	return UEngineFile(FilePath);
}