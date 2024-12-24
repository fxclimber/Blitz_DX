#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"

struct EngineVertex
{
	float4 POSITION;
	float4 TEXCOORD; // UV값이라고 불리는 존재로 텍스처가 매핑되는 비율을 지정해줍니다.
	float4 COLOR;
};



// 설명 :
class URenderer : public USceneComponent
{
	friend class UEngineCamera;

public:
	// constrcuter destructer
	ENGINEAPI URenderer();
	ENGINEAPI ~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;

	void SetTexture(std::string_view _Value);

	ENGINEAPI void SetSpriteData(size_t _Index);

protected:
	ENGINEAPI void BeginPlay() override;

private:
	virtual void Render(UEngineCamera* _Camera, float _DeltaTime);

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

	// 점에 행렬곱해주는(변형시키는 단계) 단계입니다.
	// 그걸 내가 코딩해서 다 짜줘야한다.
	// HLSL이라는 인터프린터 언어를 이용해서 내가 새로운 언어를 배워서 다 짜야합니다.

	Microsoft::WRL::ComPtr<ID3DBlob> VSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> VSErrorCodeBlob = nullptr; // 중간 컴파일 결과물
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader = nullptr;
	void VertexShaderInit();
	void VertexShaderSetting();


	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer = nullptr;
	// 삼각형을 면으로 생각하고 그려주세요.
	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	void InputAssembler2Init();
	void InputAssembler2Setting();

	D3D11_VIEWPORT ViewPortInfo;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState = nullptr;
	void RasterizerInit();
	void RasterizerSetting();

	// 쉐이더이기 때문에 버텍스쉐이더랑 비슷합니다. 
	Microsoft::WRL::ComPtr<ID3DBlob> PSShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> PSErrorCodeBlob = nullptr; // 중간 컴파일 결과물
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader = nullptr;
	void PixelShaderInit();
	void PixelShaderSetting();

	void OutPutMergeSetting();
};

