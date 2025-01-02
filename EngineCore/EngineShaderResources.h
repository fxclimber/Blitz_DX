#pragma once
#include "EngineConstantBuffer.h"

class UEngineConstantBufferRes
{
public:
	void* Data; // �ڽſ��� ���õ� �����ʹ� ������ ������ ���� ���̴�.
	UINT BufferSize;
	std::shared_ptr<UEngineConstantBuffer> Res;
};

// Render�� 2�� �������.
// Renderer1
// ������ �׸��� �ʹ�.
// 
// Renderer2
// ����� �׸��� �;�.

// ���� : �ְ� ���̴��� �˻��ؼ� 
// �� ���������� �����ؾ��� ���� �ٸ���?
// �̳༮�� ������ ũ�� 2���� �Դϴ�.

// ���̴��� ������ �ִ� �� �������� ���̴� ���ҽ��� �����ϴ� ����
// �������� ������ �ִ� �� �׷��� �ؼ� ����� ���ҽ����� �����͸� �����ϴ� ���ҷ� ������ ���� �̴ϴ�.
class UEngineShaderResources
{
	// 

public:
	// constrcuter destructer
	UEngineShaderResources();
	~UEngineShaderResources();

	// delete Function
	UEngineShaderResources(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources(UEngineShaderResources&& _Other) noexcept = delete;
	UEngineShaderResources& operator=(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources& operator=(UEngineShaderResources&& _Other) noexcept = delete;

	void CreateConstantBufferRes(std::string_view Name, UEngineConstantBufferRes Res);

protected:

private:
	std::map<std::string, UEngineConstantBufferRes> ConstantBufferRess;
	// std::map<std::string, UEngineConstantBufferRes> TextureSetters;
	// std::map<std::string, UEngineConstantBufferRes> ConstantBufferSetters;
	// std::map<std::string, UEngineConstantBufferRes> ConstantBufferSetters;

};

