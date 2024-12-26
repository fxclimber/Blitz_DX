#include "PreCompile.h"
#include "RenderBlitz.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/EngineTexture.h>

URenderBlitz::URenderBlitz()
{
}

URenderBlitz::~URenderBlitz()
{
	VertexBuffer = nullptr;
	VSShaderCodeBlob = nullptr;
	VSErrorCodeBlob = nullptr;
}

void URenderBlitz::SetTexture(std::string_view _Value)
{
	std::string UpperName = UEngineString::ToUpper(_Value);

	Sprite = UEngineSprite::Find<UEngineSprite>(UpperName);

	if (nullptr == Sprite)
	{
		MSGASSERT("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}
}
void URenderBlitz::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();
	UObject::SetOrder(_Order);
	ULevel* Level = GetActor()->GetWorld();

	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();
	Level->ChangeRenderGroup(0, PrevOrder, RendererPtr);
}

ENGINEAPI void URenderBlitz::BeginPlay()
{
	USceneComponent::BeginPlay();
	SetOrder(0);

	InputAssembler1Init();
	VertexShaderInit();
	InputAssembler2Init();
	RasterizerInit();
	PixelShaderInit();
	ShaderResInit();
}


void URenderBlitz::ShaderResInit()
{
	{
		D3D11_BUFFER_DESC BufferInfo = { 0 };
		BufferInfo.ByteWidth = sizeof(FTransform);
		BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

		if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, nullptr, TransformConstBuffer.GetAddressOf()))
		{
			MSGASSERT("상수버퍼 생성에 실패했습니다..");
			return;
		}
	}

	{
		//D3D11_BUFFER_DESC BufferInfo = { 0 };
		//BufferInfo.ByteWidth = sizeof(FSpriteData);
		//BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		//BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

		//if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, nullptr, SpriteConstBuffer.GetAddressOf()))
		//{
		//	MSGASSERT("상수버퍼 생성에 실패했습니다..");
		//	return;
		//}
	}

	D3D11_SAMPLER_DESC SampInfo = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT };
	SampInfo.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER; // 0~1사이만 유효
	SampInfo.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER; // y
	SampInfo.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP; // z // 3중 

	SampInfo.BorderColor[0] = 0.0f;
	SampInfo.BorderColor[1] = 0.0f;
	SampInfo.BorderColor[2] = 0.0f;
	SampInfo.BorderColor[3] = 0.0f;

	UEngineCore::Device.GetDevice()->CreateSamplerState(&SampInfo, &SamplerState);
}

ENGINEAPI void URenderBlitz::SetSpriteData(size_t _Index)
{
	SpriteData = Sprite->GetSpriteData(_Index);
}

void URenderBlitz::ShaderResSetting()
{
		{
			FTransform& RendererTrans = GetTransformRef();
			D3D11_MAPPED_SUBRESOURCE Data = {};
			UEngineCore::Device.GetContext()->Map(TransformConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

			if (nullptr == Data.pData)
			{
				MSGASSERT("그래픽카드가 수정을 거부했습니다.");
			}
			memcpy_s(Data.pData, sizeof(FTransform), &RendererTrans, sizeof(FTransform));
			UEngineCore::Device.GetContext()->Unmap(TransformConstBuffer.Get(), 0);

			ID3D11Buffer* ArrPtr[16] = { TransformConstBuffer.Get() };
			UEngineCore::Device.GetContext()->VSSetConstantBuffers(0, 1, ArrPtr);
		}

		//{
		//	D3D11_MAPPED_SUBRESOURCE Data = {};
		//	UEngineCore::Device.GetContext()->Map(SpriteConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

		//	if (nullptr == Data.pData)
		//	{
		//		MSGASSERT("그래픽카드가 수정을 거부했습니다.");
		//	}
		//	memcpy_s(Data.pData, sizeof(FSpriteData), &SpriteData, sizeof(FSpriteData));
		//	UEngineCore::Device.GetContext()->Unmap(SpriteConstBuffer.Get(), 0);

		//	ID3D11Buffer* ArrPtr[16] = { SpriteConstBuffer.Get() };
		//	UEngineCore::Device.GetContext()->VSSetConstantBuffers(1, 1, ArrPtr);
		//}

		//ID3D11ShaderResourceView* ArrSRV[16] = { Sprite->GetSRV() };
		//UEngineCore::Device.GetContext()->PSSetShaderResources(0, 1, ArrSRV);

		ID3D11SamplerState* ArrSMP[16] = { SamplerState.Get() };
		UEngineCore::Device.GetContext()->PSSetSamplers(0, 1, ArrSMP);	
}

void URenderBlitz::Render(UEngineCamera* _Camera, float _DeltaTime)
{
	FTransform& CameraTrans = _Camera->GetTransformRef();

	FTransform& RendererTrans = GetTransformRef();

	// 랜더러는 월드 뷰 프로젝트를 다 세팅받았고
	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;

	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;

	ShaderResSetting();
	InputAssembler1Setting();
	VertexShaderSetting();
	InputAssembler2Setting();
	RasterizerSetting();
	PixelShaderSetting();
	OutPutMergeSetting();
	// 인덱스 버퍼를 통해서 그리겠다.
	UEngineCore::Device.GetContext()->DrawIndexed(36, 0, 0);
}



void URenderBlitz::InputAssembler1Init()
{
	std::vector<EngineVertex> Vertexs;

	// 정점 데이터 (중복 제거)
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, -0.5000f, 0.5000f), {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} }); // 0
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, -0.5000f, 0.5000f), {0.5f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} }); // 1
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, -0.5000f, 0.0000f), {1.0f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f} }); // 2
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, -0.5000f, 0.0000f), {0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} }); // 3
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, -0.5000f, 0.5000f), {0.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} }); // 4
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, -0.5000f, -0.5000f), {1.0f, 0.0f}, {0.5f, 0.5f, 0.5f, 1.0f} }); // 5
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, -0.5000f, 0.0000f), {0.0f, 0.5f}, {0.8f, 0.3f, 0.1f, 1.0f} }); // 6
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, -0.5000f, -0.5000f), {0.5f, 0.0f}, {0.2f, 0.6f, 0.9f, 1.0f} }); // 7
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, -0.5000f, -0.5000f), {0.0f, 0.0f}, {0.9f, 0.1f, 0.4f, 1.0f} }); // 8
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, 0.5000f, 0.0000f), {1.0f, 0.5f}, {0.3f, 0.7f, 0.3f, 1.0f} }); // 9
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, 0.5000f, 0.5000f), {0.5f, 1.0f}, {0.7f, 0.2f, 0.5f, 1.0f} }); // 10
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, 0.5000f, 0.5000f), {1.0f, 1.0f}, {0.4f, 0.4f, 0.4f, 1.0f} }); // 11
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, 0.5000f, 0.0000f), {0.5f, 0.5f}, {0.8f, 0.8f, 0.0f, 1.0f} }); // 12
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, 0.5000f, -0.5000f), {1.0f, 0.0f}, {0.1f, 0.9f, 0.7f, 1.0f} }); // 13
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, 0.5000f, 0.5000f), {0.0f, 1.0f}, {0.6f, 0.3f, 0.7f, 1.0f} }); // 14
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, 0.5000f, -0.5000f), {0.5f, 0.0f}, {0.3f, 0.9f, 0.1f, 1.0f} }); // 15
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, 0.5000f, 0.0000f), {0.0f, 0.5f}, {0.7f, 0.8f, 0.2f, 1.0f} }); // 16
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, 0.5000f, -0.5000f), {0.0f, 0.0f}, {0.9f, 0.4f, 0.1f, 1.0f} }); // 17
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, -0.0000f, 0.5000f), {1.0f, 1.0f}, {0.3f, 0.7f, 0.3f, 1.0f} }); // 18
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, -0.5000f, 0.5000f), {0.5f, 1.0f}, {0.7f, 0.2f, 0.5f, 1.0f} }); // 19
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, -0.5000f, 0.5000f), {1.0f, 1.0f}, {0.4f, 0.4f, 0.4f, 1.0f} }); // 20
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, -0.0000f, 0.5000f), {0.5f, 0.5f}, {0.8f, 0.8f, 0.0f, 1.0f} }); // 21
	Vertexs.push_back(EngineVertex{ FVector(0.5000f, 0.5000f, 0.5000f), {1.0f, 1.0f}, {0.1f, 0.9f, 0.7f, 1.0f} }); // 22
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, -0.5000f, 0.5000f), {0.0f, 1.0f}, {0.6f, 0.3f, 0.7f, 1.0f} }); // 23
	Vertexs.push_back(EngineVertex{ FVector(0.0000f, 0.5000f, 0.5000f), {0.5f, 0.0f}, {0.3f, 0.9f, 0.1f, 1.0f} }); // 24
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, -0.0000f, 0.5000f), {0.0f, 0.5f}, {0.7f, 0.8f, 0.2f, 1.0f} }); // 25
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, -0.5000f, 0.0000f), {0.0f, 0.0f}, {0.9f, 0.4f, 0.1f, 1.0f} }); // 26
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, -0.5000f, 0.5000f), {0.0f, 1.0f}, {0.3f, 0.7f, 0.3f, 1.0f} }); // 27
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, -0.0000f, 0.0000f), {0.5f, 0.5f}, {0.8f, 0.2f, 0.5f, 1.0f} }); // 28
	Vertexs.push_back(EngineVertex{ FVector(-0.5000f, 0.5000f, 0.5000f), {0.0f, 0.5f}, {0.6f, 0.3f, 0.7f, 1.0f} }); // 29







	D3D11_BUFFER_DESC BufferInfo = { 0 };

	BufferInfo.ByteWidth = sizeof(EngineVertex) * static_cast<int>(Vertexs.size());
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data; // 초기값 넣어주는 용도의 구조체
	Data.pSysMem = &Vertexs[0];

	if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, &Data, VertexBuffer.GetAddressOf()))
	{
		MSGASSERT("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void URenderBlitz::InputAssembler1Setting()
{
	UINT VertexSize = sizeof(EngineVertex);
	UINT Offset = 0;

	ID3D11Buffer* ArrBuffer[1];
	ArrBuffer[0] = VertexBuffer.Get();

	UEngineCore::Device.GetContext()->IASetVertexBuffers(0, 1, ArrBuffer, &VertexSize, &Offset);
	UEngineCore::Device.GetContext()->IASetInputLayout(InputLayOut.Get());
}

void URenderBlitz::InputAssembler1LayOut()
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutData;

	// POSITION
	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "POSITION";
		Desc.SemanticIndex = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // 4 floats to match HLSL
		Desc.InputSlot = 0;
		Desc.AlignedByteOffset = 0; // Starting offset
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	// COLOR
	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "COLOR";
		Desc.SemanticIndex = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // 4 floats
		Desc.InputSlot = 0;
		Desc.AlignedByteOffset = 16; // After POSITION (4 floats = 16 bytes)
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	// Create Input Layout
	HRESULT Result = UEngineCore::Device.GetDevice()->CreateInputLayout(
		&InputLayOutData[0],
		static_cast<unsigned int>(InputLayOutData.size()),
		VSShaderCodeBlob->GetBufferPointer(),
		VSShaderCodeBlob->GetBufferSize(),
		&InputLayOut);

	if (S_OK != Result)
	{
		MSGASSERT("인풋 레이아웃 생성에 실패했습니다");
	}
}

void URenderBlitz::VertexShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("SimpleColorShader.hlsl");

	std::string Path = File.GetPathToString();
	std::wstring WPath = UEngineString::AnsiToUnicode(Path);

	std::string version = "vs_5_0";
	int Flag0 = 0;
	int Flag1 = 0;

#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif

	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	D3DCompileFromFile(
		WPath.c_str(),
		nullptr, // Define TEST 등으로 전처리기를 넣을수.
		nullptr,
		"VertexToWorld",
		version.c_str(),
		Flag0,
		Flag1,
		&VSShaderCodeBlob,
		&VSErrorCodeBlob
	);

	if (nullptr == VSShaderCodeBlob)
	{
		std::string ErrString = reinterpret_cast<char*>(VSErrorCodeBlob->GetBufferPointer());
		MSGASSERT("쉐이더 코드 중간빌드에서 실패했습니다\n" + ErrString);
		return;
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreateVertexShader(
		VSShaderCodeBlob->GetBufferPointer(),
		VSShaderCodeBlob->GetBufferSize(),
		nullptr,
		&VertexShader
	);

	if (S_OK != Result)
	{
		MSGASSERT("버텍스 쉐이더 생성에 실패했습니다.");
	}

	InputAssembler1LayOut();
}

void URenderBlitz::VertexShaderSetting()
{
	UEngineCore::Device.GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);
}

void URenderBlitz::InputAssembler2Init()
{
	std::vector<unsigned int> Indexs;

	// 앞면
	Indexs.push_back(0); Indexs.push_back(1); Indexs.push_back(11);
	Indexs.push_back(1); Indexs.push_back(10); Indexs.push_back(11);

	// 뒷면
	Indexs.push_back(5); Indexs.push_back(7); Indexs.push_back(13);
	Indexs.push_back(7); Indexs.push_back(15); Indexs.push_back(13);

	// 왼쪽면
	Indexs.push_back(4); Indexs.push_back(6); Indexs.push_back(14);
	Indexs.push_back(6); Indexs.push_back(16); Indexs.push_back(14);

	// 오른쪽면
	Indexs.push_back(2); Indexs.push_back(0); Indexs.push_back(9);
	Indexs.push_back(2); Indexs.push_back(9); Indexs.push_back(13);

	// 윗면
	Indexs.push_back(11); Indexs.push_back(10); Indexs.push_back(14);
	Indexs.push_back(11); Indexs.push_back(14); Indexs.push_back(9);

	// 아랫면
	Indexs.push_back(1); Indexs.push_back(0); Indexs.push_back(6);
	Indexs.push_back(1); Indexs.push_back(6); Indexs.push_back(7);

	D3D11_BUFFER_DESC BufferInfo = { 0 };
	BufferInfo.ByteWidth = sizeof(unsigned int) * static_cast<int>(Indexs.size());
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = &Indexs[0];

	if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, &Data, &IndexBuffer))
	{
		MSGASSERT("인덱스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void URenderBlitz::InputAssembler2Setting()
{
	int Offset = 0;
	UEngineCore::Device.GetContext()->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, Offset);

	UEngineCore::Device.GetContext()->IASetPrimitiveTopology(Topology);
}

void URenderBlitz::RasterizerInit()
{
	D3D11_RASTERIZER_DESC Desc = {};
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	UEngineCore::Device.GetDevice()->CreateRasterizerState(&Desc, RasterizerState.GetAddressOf());

	ViewPortInfo.Width = 1280.0f;
	ViewPortInfo.Height = 720.0f;
	ViewPortInfo.TopLeftX = 0.0f;
	ViewPortInfo.TopLeftY = 0.0f;
	ViewPortInfo.MinDepth = 0.0f;
	ViewPortInfo.MaxDepth = 1.0f;
}

void URenderBlitz::RasterizerSetting()
{
	UEngineCore::Device.GetContext()->RSSetViewports(1, &ViewPortInfo);
	UEngineCore::Device.GetContext()->RSSetState(RasterizerState.Get());
}

void URenderBlitz::PixelShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("SimpleColorShader.hlsl");

	std::string Path = File.GetPathToString();
	std::wstring WPath = UEngineString::AnsiToUnicode(Path);
	std::string version = "ps_5_0";

	int Flag0 = 0;
	int Flag1 = 0;

#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif

	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	D3DCompileFromFile(
		WPath.c_str(),
		nullptr, // Define TEST 등으로 전처리기를 넣을수.
		nullptr,
		"PixelToWorld",
		version.c_str(),
		Flag0,
		Flag1,
		&PSShaderCodeBlob,
		&PSErrorCodeBlob
	);
	if (nullptr == PSShaderCodeBlob)
	{
		std::string ErrString = reinterpret_cast<char*>(PSErrorCodeBlob->GetBufferPointer());
		MSGASSERT("쉐이더 코드 중간빌드에서 실패했습니다\n" + ErrString);
		return;
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreatePixelShader(
		PSShaderCodeBlob->GetBufferPointer(),
		PSShaderCodeBlob->GetBufferSize(),
		nullptr,
		&PixelShader
	);

	if (S_OK != Result)
	{
		MSGASSERT("픽셀 쉐이더 생성에 실패했습니다.");
	}
}

void URenderBlitz::PixelShaderSetting()
{
	UEngineCore::Device.GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}

void URenderBlitz::OutPutMergeSetting()
{
	ID3D11RenderTargetView* RTV = UEngineCore::Device.GetRTV();

	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
	ArrRtv[0] = RTV; // SV_Target0

	UEngineCore::Device.GetContext()->OMSetRenderTargets(1, &ArrRtv[0], nullptr);
}
