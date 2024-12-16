#include "PreCompile.h"
#include "EngineDebug.h"


namespace UEngineDebug
{
	void LeakCheck()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	// 분리해야 하겠네요
	void OutPutString(const std::string& Text)
	{
		std::string ResultText = Text + "\n";
		OutputDebugStringA(ResultText.c_str());
	}

	ENGINEAPI void StartConsole()
	{
		AllocConsole();
		FILE* pCout = nullptr;
		FILE* pErr = nullptr;
		FILE* pCin = nullptr;
		errno_t Err;

		// 콘솔창의 기본 출력버퍼는 stdout이라는 것으로 변경해 달라
		// &pCout 전에 쓰던 디폴트 입출력 버퍼는 pCout에 담아줘.
		// 입력 및 출력버퍼는 FILE*로 표현합니다.
		// &pCout
		// __acrt_iob_func(1) 현재 사용하고 있는 프로그램의 입력버퍼(FILE*)를 가져오는 함수인것 같습니다.
		// OS 블로그에서 봤습니다.
		Err = freopen_s(&pCout, "CONOUT$", "w", stdout);
		if (pCout != stdout)
		{
			fclose(pCout);
		}
		Err = freopen_s(&pCin, "CONIN$", "r", stdin);
		if (pCin != stdin)
		{
			fclose(pCin);
		}
		Err = freopen_s(&pErr, "CONERR$", "w", stderr);
		if (pErr != stderr)
		{
			fclose(pErr);
		}

		// fclose(pCout);
		// fclose(pCin);
		// fclose(pErr);
		// std::cout << "Console Log Start" << std::endl;
	}

	ENGINEAPI void EndConsole()
	{
		FreeConsole();
	}
}