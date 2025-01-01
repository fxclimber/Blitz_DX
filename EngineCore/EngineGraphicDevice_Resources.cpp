#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "EngineBlend.h"

void UEngineGraphicDevice::DefaultResourcesInit()
{
	MeshInit();
	BlendInit();
}

void UEngineGraphicDevice::MeshInit()
{
	int a = 0;

	{
		std::vector<EngineVertex> Vertexs;
		Vertexs.resize(4);
		Vertexs[0] = EngineVertex{ FVector(-0.5f, 0.5f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[1] = EngineVertex{ FVector(0.5f, 0.5f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[2] = EngineVertex{ FVector(-0.5f, -0.5f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[3] = EngineVertex{ FVector(0.5f, -0.5f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

		UVertexBuffer::Create("Rect", Vertexs);
	}

	{
		std::vector<unsigned int> Indexs;

		Indexs.push_back(0);
		Indexs.push_back(1);
		Indexs.push_back(2);

		Indexs.push_back(1);
		Indexs.push_back(3);
		Indexs.push_back(2);
		UIndexBuffer::Create("Rect", Indexs);
	}

	{
		UMesh::Create("Rect");
	}
}

void UEngineGraphicDevice::BlendInit()
{
	// 머티리얼이나 이런곳에서 이 블랜드 세팅이 존재한다.
	// 컬러 블랜드랑 다른 블랜드랑 햇갈리면 안됩니다.
	// 대놓고 알파 블랜드라고 명칭되는 곳이 있고
	// transparent 라는 단어


	D3D11_BLEND_DESC Desc = {0};

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

