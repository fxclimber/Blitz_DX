#pragma once
#include <EngineCore/Renderer.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>

using Microsoft::WRL::ComPtr;

struct FBzColor
{
	float4 Albedo;
};

struct FVertex
{
	float4 POSITION;
	float4 UV;
	float4 COLOR;
};

class UBzRendererDefault : public URenderer
{
public:
	UBzRendererDefault();
	~UBzRendererDefault();

	//// Shader
	//ComPtr<ID3D11VertexShader> m_colorVertexShader;
	//ComPtr<ID3D11PixelShader> m_colorPixelShader;
	//ComPtr<ID3D11InputLayout> m_colorInputLayout;

	//ComPtr<ID3D11Buffer> m_vertexBuffer;
	//ComPtr<ID3D11Buffer> m_indexBuffer;
	//ComPtr<ID3D11Buffer> m_constantBuffer;
	//ComPtr<ID3D11Buffer> m_pixelShaderConstantBuffer;
	//UINT m_indexCount;

	//// Texturing
	//static ComPtr<ID3D11Texture2D> m_texture;
	//static ComPtr<ID3D11ShaderResourceView> m_textureResourceView;
	//ComPtr<ID3D11Texture2D> m_texture2;
	//ComPtr<ID3D11ShaderResourceView> m_textureResourceView2;
	//ComPtr<ID3D11SamplerState> m_samplerState;



protected:

private:
	FBzColor TestColor;


};

