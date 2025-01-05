#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "Mesh.h"
#include "EngineBlend.h"
#include "EngineShader.h"
#include "EngineMaterial.h"
#include "EngineTexture.h"

void UEngineGraphicDevice::DefaultResourcesInit()
{
	TextureInit();
	MeshInit();
	BlendInit();
	RasterizerStateInit();
	ShaderInit();
	MaterialInit();
}

void UEngineGraphicDevice::TextureInit()
{

	D3D11_SAMPLER_DESC SampInfo = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT };
	SampInfo.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP; // 0~1사이만 유효
	SampInfo.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP; // y
	SampInfo.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP; // z // 3중 

	SampInfo.BorderColor[0] = 0.0f;
	SampInfo.BorderColor[1] = 0.0f;
	SampInfo.BorderColor[2] = 0.0f;
	SampInfo.BorderColor[3] = 0.0f;

	// SampInfo.ComparisonFunc = D3D11_COMPARISON_NEVER;
	// Lod라고 불리는 것은 z값이 얼마나 멀어지면 얼마나 대충 색깔 빼올거냐. 
	// SampInfo.MaxLOD = 0.0f;
	// SampInfo.MinLOD = 0.0f;

	UEngineSampler::Create("WRAPSampler", SampInfo);


	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("EngineShader"))
		{
			MSGASSERT("EngineShader 폴더를 찾지 못했습니다.");
			return;
		}
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}
}

void UEngineGraphicDevice::ShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");

	std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

	for (size_t i = 0; i < ShaderFiles.size(); i++)
	{
		UEngineShader::ReflectionCompile(ShaderFiles[i]);
	}
}



void UEngineGraphicDevice::MeshInit()
{
	int a = 0;

	// Rect 
	{
		std::vector<FEngineVertex> Vertexs;
		Vertexs.resize(4);
		Vertexs[0] = FEngineVertex{ FVector(-0.5f, 0.5f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[1] = FEngineVertex{ FVector(0.5f, 0.5f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[2] = FEngineVertex{ FVector(-0.5f, -0.5f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[3] = FEngineVertex{ FVector(0.5f, -0.5f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

		UEngineVertexBuffer::Create("Rect", Vertexs);
	}

	{
		std::vector<unsigned int> Indexs;

		Indexs.push_back(0);
		Indexs.push_back(1);
		Indexs.push_back(2);

		Indexs.push_back(1);
		Indexs.push_back(3);
		Indexs.push_back(2);
		UEngineIndexBuffer::Create("Rect", Indexs);
	}
	UMesh::Create("Rect");



	//Tri
	{
		std::vector<FEngineVertex> Vertexs;
		Vertexs.resize(3);
		Vertexs[0] = FEngineVertex{ FVector(-0.5f, 0.5f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[1] = FEngineVertex{ FVector(0.5f, 0.5f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[2] = FEngineVertex{ FVector(-0.5f, -0.5f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		UEngineVertexBuffer::Create("Tri", Vertexs);

		std::vector<unsigned int> Indexs;
		Indexs = { 0,1,2 };
		Indexs.push_back(0);
		Indexs.push_back(1);
		Indexs.push_back(2);
		UEngineIndexBuffer::Create("Tri", Indexs);

		UMesh::Create("Tri");
	}

	// cube
	{
		std::vector<FEngineVertex> Vertexs;
		Vertexs.resize(24);

		// 윗면
		Vertexs[0] = FEngineVertex{ FVector(-1.0f, 1.0f, -1.0f), {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} }; // 빨강
		Vertexs[1] = FEngineVertex{ FVector(-1.0f, 1.0f, 1.0f), {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[2] = FEngineVertex{ FVector(1.0f, 1.0f, 1.0f), {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[3] = FEngineVertex{ FVector(1.0f, 1.0f, -1.0f), {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} };

		// 아랫면
		Vertexs[4] = FEngineVertex{ FVector(-1.0f, -1.0f, -1.0f), {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} }; // 초록
		Vertexs[5] = FEngineVertex{ FVector(1.0f, -1.0f, -1.0f), {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[6] = FEngineVertex{ FVector(1.0f, -1.0f, 1.0f), {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[7] = FEngineVertex{ FVector(-1.0f, -1.0f, 1.0f), {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} };

		// 앞면
		Vertexs[8] = FEngineVertex{ FVector(-1.0f, -1.0f, -1.0f), {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} }; // 파랑
		Vertexs[9] = FEngineVertex{ FVector(-1.0f, 1.0f, -1.0f), {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[10] = FEngineVertex{ FVector(1.0f, 1.0f, -1.0f), {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[11] = FEngineVertex{ FVector(1.0f, -1.0f, -1.0f), {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} };

		// 뒷면
		Vertexs[12] = FEngineVertex{ FVector(-1.0f, -1.0f, 1.0f), {0.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} }; // 노랑
		Vertexs[13] = FEngineVertex{ FVector(1.0f, -1.0f, 1.0f), {1.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[14] = FEngineVertex{ FVector(1.0f, 1.0f, 1.0f), {1.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[15] = FEngineVertex{ FVector(-1.0f, 1.0f, 1.0f), {0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} };

		// 왼쪽면
		Vertexs[16] = FEngineVertex{ FVector(-1.0f, -1.0f, 1.0f), {0.0f, 0.0f}, {0.5f, 0.0f, 0.5f, 1.0f} }; // 보라
		Vertexs[17] = FEngineVertex{ FVector(-1.0f, 1.0f, 1.0f), {1.0f, 0.0f}, {0.5f, 0.0f, 0.5f, 1.0f} };
		Vertexs[18] = FEngineVertex{ FVector(-1.0f, 1.0f, -1.0f), {1.0f, 1.0f}, {0.5f, 0.0f, 0.5f, 1.0f} };
		Vertexs[19] = FEngineVertex{ FVector(-1.0f, -1.0f, -1.0f), {1.0f, 0.0f}, {0.5f, 0.0f, 0.5f, 1.0f} };

		// 오른쪽면
		Vertexs[20] = FEngineVertex{ FVector(1.0f, -1.0f, 1.0f), {0.0f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f} }; // 하늘색
		Vertexs[21] = FEngineVertex{ FVector(1.0f, -1.0f, -1.0f), {1.0f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f} };
		Vertexs[22] = FEngineVertex{ FVector(1.0f, 1.0f, -1.0f), {1.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} };
		Vertexs[23] = FEngineVertex{ FVector(1.0f, 1.0f, 1.0f), {0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} };

		UEngineVertexBuffer::Create("Cube", Vertexs);

		//---------
		std::vector<unsigned int> Indexs;

		// 윗면 (Vertexs[0] ~ Vertexs[3])
		Indexs.push_back(0);
		Indexs.push_back(1);
		Indexs.push_back(2);
		Indexs.push_back(0);
		Indexs.push_back(2);
		Indexs.push_back(3);

		// 아랫면 (Vertexs[4] ~ Vertexs[7])
		Indexs.push_back(4);
		Indexs.push_back(5);
		Indexs.push_back(6);
		Indexs.push_back(4);
		Indexs.push_back(6);
		Indexs.push_back(7);

		// 앞면 (Vertexs[8] ~ Vertexs[11])
		Indexs.push_back(8);
		Indexs.push_back(9);
		Indexs.push_back(10);
		Indexs.push_back(8);
		Indexs.push_back(10);
		Indexs.push_back(11);

		// 뒷면 (Vertexs[12] ~ Vertexs[15])
		Indexs.push_back(12);
		Indexs.push_back(13);
		Indexs.push_back(14);
		Indexs.push_back(12);
		Indexs.push_back(14);
		Indexs.push_back(15);

		// 왼쪽면 (Vertexs[16] ~ Vertexs[19])
		Indexs.push_back(16);
		Indexs.push_back(17);
		Indexs.push_back(18);
		Indexs.push_back(16);
		Indexs.push_back(18);
		Indexs.push_back(19);

		// 오른쪽면 (Vertexs[20] ~ Vertexs[23])
		Indexs.push_back(20);
		Indexs.push_back(21);
		Indexs.push_back(22);
		Indexs.push_back(20);
		Indexs.push_back(22);
		Indexs.push_back(23);

		UEngineIndexBuffer::Create("Cube", Indexs);

		UMesh::Create("Cube");
	}






}

void UEngineGraphicDevice::BlendInit()
{
	// 머티리얼이나 이런곳에서 이 블랜드 세팅이 존재한다.
	// 컬러 블랜드랑 다른 블랜드랑 햇갈리면 안됩니다.
	// 대놓고 알파 블랜드라고 명칭되는 곳이 있고
	// transparent 라는 단어


	D3D11_BLEND_DESC Desc = { 0 };

	// 자동으로 알파부분을 
	// 알파가 0.0f 색상부분을 알아서 안그리게 도와주는 기능
	// 굉장히 많이 느려져서 그냥 내가 다 처리하는게 더 빨랐다.

	Desc.AlphaToCoverageEnable = false;

	//BOOL AlphaToCoverageEnable;
	//BOOL IndependentBlendEnable;
	//D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
	// 0번 세팅으로 8개를 다 합니다.
	Desc.IndependentBlendEnable = true;
	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	// 알베도컬러 RGB A
	// 알베도컬러 SrcColor 옵션 SrcFactor  BlendOp  DestColor  옵션 DestFactor  
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	// 알파블랜드의 기본 공식

	// SrcColor 1.0, 0.0f, 0.0f, 0.8f; * 0.8f 0.8f 0.8f 0.8f

	// SrcColor 0.0, 0.0f, 1.0f, 1.0f; * 1 - 0.8f,  1 - 0.8f, 1 - 0.8f, 1 - 0.8f

	// 알베도컬러 SrcColor 옵션 SrcFactor  BlendOp  DestColor  옵션 DestFactor  
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;



	UEngineBlend::Create("AlphaBlend", Desc);
}

void UEngineGraphicDevice::RasterizerStateInit()
{
	D3D11_RASTERIZER_DESC Desc = {};
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

	UEngineRasterizerState::Create("EngineBase", Desc);
}

void UEngineGraphicDevice::MaterialInit()
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("SpriteMaterial");
		Mat->SetVertexShader("EngineSpriteShader.fx");
		Mat->SetPixelShader("EngineSpriteShader.fx");
	}
}