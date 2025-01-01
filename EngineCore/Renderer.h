#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"
#include "RenderUnit.h"

struct FUVValue 
{
	float4 PlusUVValue;
};

// 설명 : 어떤 랜더링이든 할수 잇는 구조로 만들겠다.
// 랜더링이란 랜더러만 하는게 아닙니다. 3D
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

	ENGINEAPI void SetOrder(int _Order) override;
 
	ENGINEAPI void SetTexture(std::string_view _Value);

	ENGINEAPI void SetTexture(UEngineTexture* _Value);

	ENGINEAPI void SetSpriteData(UEngineSprite* _Sprite, size_t _Index);

	ENGINEAPI void AddUVPlusValue(float4 _Value);

	ENGINEAPI void SetMesh(std::string_view _Name);

	ENGINEAPI void SetBlend(std::string_view _Name);

	ENGINEAPI void BeginPlay() override;
	ENGINEAPI virtual void Render(UEngineCamera* _Camera, float _DeltaTime);

private:

public:
	class UMesh* Mesh = nullptr;
	class UEngineBlend* Blend = nullptr;

	FSpriteData SpriteData;
	FUVValue UVValueData;
	UEngineTexture* Texture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState = nullptr; // 샘플러 스테이트
	Microsoft::WRL::ComPtr<ID3D11Buffer> TransformConstBuffer = nullptr; // 상수버퍼
	Microsoft::WRL::ComPtr<ID3D11Buffer> SpriteConstBuffer = nullptr; // 스프라이트용 상수버퍼
	Microsoft::WRL::ComPtr<ID3D11Buffer> UVValue = nullptr; // 상수버퍼
	void ShaderResInit();
	void ShaderResSetting();

	// Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayOut = nullptr;
	// void InputAssembler1Init();
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


	// Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer = nullptr;
	// 삼각형을 면으로 생각하고 그려주세요.
	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	// void InputAssembler2Init();
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

	std::vector<URenderUnit> Units;
};

