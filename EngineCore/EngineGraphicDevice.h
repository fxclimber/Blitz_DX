#pragma once
// �⺻������ �������ֱ� ����
// windowsdk�� ���ԵǾ� �ְ� windowsdk ������ �����е� ������ ���丮�� �ڵ����ԵǾ� �ֽ��ϴ�.
#include <wrl.h>
#include <d3d11_4.h> // directx 11 ����4�� ���
#include <d3dcompiler.h> // ���̴� �����Ϸ��� �������̽� ���̴��� ���� ����
#include <EnginePlatform/EngineWindow.h>

// ���̺귯����
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

// GetHighPerFormanceAdapter ����� ���ؼ��� ����� ������ �׷���ī�� ������ ���;��ϴµ�
// �̳༮�� �� �Լ����� ������ �ִ�.
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

