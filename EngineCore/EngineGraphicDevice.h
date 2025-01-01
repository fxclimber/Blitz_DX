#pragma once
// 기본적으로 지원해주기 때문
// windowsdk에 포함되어 있고 windowsdk 폴더는 여러분들 설정중 디렉토리에 자동포함되어 있습니다.
#include <wrl.h>
#include <d3d11_4.h> // directx 11 버전4용 헤더
#include <d3dcompiler.h> // 쉐이더 컴파일러용 인터페이스 쉐이더는 추후 설명
#include <EnginePlatform/EngineWindow.h>

// 라이브러리들
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

// GetHighPerFormanceAdapter 등등을 위해서는 모니터 정보나 그래픽카드 정보를 얻어와야하는데
// 이녀석이 그 함수들을 가지고 있다.
#pragma comment(lib, "DXGI") 

class UEngineGraphicDevice
{
public:
	ENGINEAPI UEngineGraphicDevice();
	ENGINEAPI ~UEngineGraphicDevice();

	void CreateDeviceAndContext();

	void CreateBackBuffer(const UEngineWindow& _Window);

	IDXGIAdapter* GetHighPerFormanceAdapter();

	ENGINEAPI void Release();

	void RenderStart();

	void RenderEnd();

	ENGINEAPI ID3D11Device* GetDevice()
	{
		return Device.Get();
	}

	ENGINEAPI ID3D11DeviceContext* GetContext()
	{
		return Context.Get();
	}

	ENGINEAPI ID3D11RenderTargetView* GetRTV()
	{
		return RTV.Get();
	}

protected:

private:
	Microsoft::WRL::ComPtr<ID3D11Device> Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> MainAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> DXBackBufferTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RTV = nullptr;

	ENGINEAPI void DefaultResourcesInit();
	ENGINEAPI void MeshInit();
	ENGINEAPI void BlendInit();
};

