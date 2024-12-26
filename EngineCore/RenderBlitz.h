#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"
#include "Renderer.h"

class URenderBlitz : public URenderer
{
	friend class UEngineCamera;

public:
	// constrcuter destructer
	ENGINEAPI URenderBlitz();
	ENGINEAPI ~URenderBlitz();


	void SetOrder(int _Order) override;

	void SetTexture(std::string_view _Value);

	ENGINEAPI void SetSpriteData(size_t _Index);

protected:
	ENGINEAPI void BeginPlay() override;

private:
	virtual void Render(class UEngineCamera* _Camera, float _DeltaTime);

public:
	FSpriteData SpriteData;

	std::shared_ptr<class UEngineSprite> Sprite = nullptr;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState = nullptr; // 샘플러 스테이트
	Microsoft::WRL::ComPtr<ID3D11Buffer> TransformConstBuffer = nullptr; // 상수버퍼
	Microsoft::WRL::ComPtr<ID3D11Buffer> SpriteConstBuffer = nullptr; // 스프라이트용 상수버퍼
	void ShaderResInit();
	void ShaderResSetting();

	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayOut = nullptr;
	void InputAssembler1Init();
	void InputAssembler1Setting();
	void InputAssembler1LayOut();

	Microsoft::WRL::ComPtr<ID3DBlob> VSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> VSErrorCodeBlob = nullptr; // 중간 컴파일 결과물
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader = nullptr;
	void VertexShaderInit();
	void VertexShaderSetting();


	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer = nullptr;
	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	void InputAssembler2Init();
	void InputAssembler2Setting();

	D3D11_VIEWPORT ViewPortInfo;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;
	void RasterizerInit();
	void RasterizerSetting();

	Microsoft::WRL::ComPtr<ID3DBlob> PSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> PSErrorCodeBlob = nullptr; // 중간 컴파일 결과물
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader = nullptr;
	void PixelShaderInit();
	void PixelShaderSetting();

	void OutPutMergeSetting();
};

