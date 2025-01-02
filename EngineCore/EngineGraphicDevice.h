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

// 내일 4시 전까지 
// 첫번째 목표 블루스크린(단색스크린)
// 다이렉트 x기반으로한 구조를 완성하면 
// 다이렉트 x에서 무슨색깔로 다 지운다음에 그릴건지를 알려달라고 합니다. 


// 진짜 멀티플랫폼이 되려면
// 여기에는 directx가 뭐하나라도 보이면 안되게 짜야 합니다.

// 설명 :
class UEngineGraphicDevice
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineGraphicDevice();
	ENGINEAPI ~UEngineGraphicDevice();

	// delete Function
	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	void CreateDeviceAndContext();

	void CreateBackBuffer(const UEngineWindow& _Window);

	// Adapter 그래픽카드의 정보를 가지고 있는 인터페이스
	// 다이렉트 x 디바이스가 되죠.
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

	// 그래픽디바이스
	// 9에서는 그려라와 로드해라를 다했다.

	// 11로 오면서 인터페이스를 2가지 부류로 분류했다.

	// 절대 안지울 거니까.

	// 메모리 로드해라 관련
	// 그래픽카드에한테 그림 저장좀 해달라고 할수 있습니다.
	Microsoft::WRL::ComPtr<ID3D11Device> Device = nullptr;

	// 랜더링 그려라 관련
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context = nullptr;

	// 다이렉트 x에서는 백버퍼를 스왑 체인이라고 부르고
	// 내가 교체나 
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain = nullptr;

	Microsoft::WRL::ComPtr<IDXGIAdapter> MainAdapter = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> DXBackBufferTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RTV = nullptr;

	//FVector ClearColor = FVector::BLUE;
	ENGINEAPI void DefaultResourcesInit();

	ENGINEAPI void MeshInit();
	ENGINEAPI void BlendInit();
	ENGINEAPI void ShaderInit();
	ENGINEAPI void MaterialInit();
	ENGINEAPI void RasterizerStateInit();
};

