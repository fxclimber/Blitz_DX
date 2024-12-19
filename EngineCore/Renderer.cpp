#include "PreCompile.h"
#include "Renderer.h"
#include <EngineBase/EngineString.h>

URenderer::URenderer()
{
}

URenderer::~URenderer()
{
	VertexBuffer = nullptr;
	VSShaderCodeBlob = nullptr;
	VSErrorCodeBlob = nullptr;

}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();
	UObject::SetOrder(_Order);
	ULevel* Level = GetActor()->GetWorld();
	// std::shared_ptr<URenderer> Render(this);
	// std::enable_shared_from_this<UObject> 상속받은 클래스가 자기자신을 this
	// std::shared_ptr로 만들어진 this를 사용하고 싶을대 호출하는 함수.
	// std::shared_ptr<UObject> ObjectPtr = UObject::shared_from_this();
	// dynmaic_cast를 사용하는 방법이 있을 것이다. 
	// dynamic_cast <= 는 순수한 포인터를 변환시키는 녀석이지 std::shared_ptr
	// std::shared_ptr<int> NewInt = std::make_shared<int>();
	// std::shared_ptr<URenderer> RendererPtr = std::dynamic_pointer_cast<URenderer>(ObjectPtr);
	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();
	Level->ChangeRenderGroup(PrevOrder, RendererPtr);
}

ENGINEAPI void URenderer::BeginPlay()
{
	SetOrder(0);

	// 기본적인 랜더링 파이프라인을 익히기 위한 
	// 모든 기본 코드들을 다 쳐볼 생각입니다.

	InputAssembler1Init();
	VertexShaderInit();
	InputAssembler2Init();
	RasterizerInit();
	PixelShaderInit();
}

void URenderer::Render(float _DeltaTime)
{
	InputAssembler1Setting();
	VertexShaderSetting();
	InputAssembler2Setting();
	RasterizerSetting();
	PixelShaderSetting();
	OutPutMergeSetting();
	// 인덱스 버퍼를 통해서 그리겠다.
	UEngineCore::Device.GetContext()->DrawIndexed(6, 0, 0);

}



void URenderer::InputAssembler1Init()
{
	// 버텍스 버퍼를 그래픽카드에게 만들어 달라고 요청
	// CPU
	std::vector<EngineVertex> Vertexs;
	Vertexs.resize(4);

	Vertexs[0] = EngineVertex{ FVector(-0.5f, 0.5f, -0.0f), {} };
	Vertexs[1] = EngineVertex{ FVector(0.5f, 0.5f, -0.0f), {} };
	Vertexs[2] = EngineVertex{ FVector(-0.5f, -0.5f, -0.0f), {} };
	Vertexs[3] = EngineVertex{ FVector(0.5f, -0.5f, -0.0f), {} };
	// 0   1
	// 
	// 2   3


	D3D11_BUFFER_DESC BufferInfo = { 0 };

	BufferInfo.ByteWidth = sizeof(EngineVertex) * static_cast<int>(Vertexs.size());
	// 용도는 버텍스 버퍼
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPU에서 수정할수 있어?
	BufferInfo.CPUAccessFlags = 0;
	// 중요 메모리 위치를 그래픽카드로 할거냐 cpu로 할거야?
	// 여러가지 옵션

	// D3D11_USAGE_DEFAULT
	// GPU에서 읽기 및 쓰기 액세스가 필요한 리소스입니다.이는 가장 일반적인 사용 선택일 수 있습니다.

	// D3D11_USAGE_IMMUTABLE
	// GPU에서만 읽을 수 있는 리소스입니다.GPU에서 작성할 수 없으며 CPU에서 전혀 액세스할 수 없습니다.이 유형의 리소스는 만든 후에 변경할 수 없으므로 만들 때 초기화해야 합니다.

	// D3D11_USAGE_DYNAMIC
	// GPU(읽기 전용)와 CPU(쓰기 전용)에서 액세스할 수 있는 리소스입니다.동적 리소스는 CPU에서 프레임당 한 번 이상 업데이트되는 리소스에 적합합니다.동적 리소스를 업데이트하려면 Map 메서드를 사용합니다.

	// 비트코인 채굴할때. 
	// 	D3D11_USAGE_STAGING
	// GPU에서 CPU로의 데이터 전송(복사)을 지원하는 리소스입니다.

	BufferInfo.Usage = D3D11_USAGE_DEFAULT;


	// 초기값
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = &Vertexs[0];

	// GPU에 xxx 크기의 버퍼 만들어주세요는 모두 아래의 함수로 만듭니다.
	if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, &Data, &VertexBuffer))
	{
		MSGASSERT("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}

	// 인풋 레이아웃 이라는 것을 만들어야 한다.
	// 버텍스 쉐이더가 있어야 인풋레이아웃 이라는 것을 만들수 있다.
}

void URenderer::InputAssembler1Setting()
{
	UINT VertexSize = sizeof(EngineVertex);
	// 이 버텍스 버퍼가 10개짜리인데 3번째 버텍스 부터 세팅해줘.
	UINT Offset = 0;

	// 한번에 여러개의 버텍스 버퍼를 세팅할수 있다.
	// 버텍스버퍼포인터 1차원 배열을 넣어주는데.
	// 0번슬롯부터 1개 사용하겠다.
	// 버텍스 하나의 크기는 VertexSize
	// Offset부터 버텍스를 사용하겠다.



	ID3D11Buffer* ArrBuffer[1];
	ArrBuffer[0] = VertexBuffer.Get();

	UEngineCore::Device.GetContext()->IASetVertexBuffers(0, 1, ArrBuffer, &VertexSize, &Offset);
	UEngineCore::Device.GetContext()->IASetInputLayout(InputLayOut.Get());
}

void URenderer::InputAssembler1LayOut()
{
	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
	//UINT NumElements,
	//const void* pShaderBytecodeWithInputSignature, <= 쉐이더 중간 컴파일 코드 넣어달라는 겁니다
	//SIZE_T BytecodeLength,
	//ID3D11InputLayout** ppInputLayout

	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutData;


	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "POSITION";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 0;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

		// 인스턴싱을 설명할때 이야기 하겠습니다.
		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "COLOR";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 16;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

		// 인스턴싱을 설명할때 이야기 하겠습니다.
		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}



	// 쉐이더에서 어떤 인풋레이아웃을 사용하는지 알려줘.
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


void URenderer::VertexShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");


	std::string Path = File.GetPathToString();

	std::wstring WPath = UEngineString::AnsiToUnicode(Path);

	// 쉐이더 코드를 그냥 문자열로 만들어서 컴파일 할수도 있다.
	//std::string ShaderCode = "struct EngineVertex \	{ \		float4 COLOR : COLOR; \		float4 OSITION : POSITION; \	}; \	struct VertexShaderOutPut \	{ \		float4 SVPOSITION : V_POSITION; \		float4 COLOR : COLOR; \	}; \	VertexShaderOutPut VertexToWorldEngineVertex _Vertex) \	{ \		VertexShaderOutPut OutPut; \		utPut.SVPOSITION = _Vertex.POSITION; \		OutPut.COLOR = _Vertex.COLOR; \
	//	return OutPut; \	} 
	// D3DCompile()

	// 버전을 만든다.
	std::string version = "vs_5_0";

	int Flag0 = 0;
	int Flag1 = 0;

#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif

	// 행렬을 집어넣게 될것이다.
	// 조금 느려진다고하는 하는데 느낀적은 없습니다.
	// Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0]
	// [100][100][0][1]

	// [1][0][0][100]
	// [0][1][0][100]
	// [0][0][1][0]
	// [0][0][0][1]

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

void URenderer::VertexShaderSetting()
{
	UEngineCore::Device.GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);
}

void URenderer::RasterizerInit()
{
	D3D11_RASTERIZER_DESC Desc = {};

	// FXAA 느려 다이렉트가 직접 만든것들은 다 느려요.
	// Desc.AntialiasedLineEnable = true;
	// Desc.DepthClipEnable = true;

	// Face컬링 
	// None이면 시계방향 반시계방향 다 출력
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

	// 면에 색깔이 보인다.
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	// 면에 뼈대만 보인다.
	// Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

	UEngineCore::Device.GetDevice()->CreateRasterizerState(&Desc, RasterizerState.GetAddressOf());

	ViewPortInfo.Height = 720.0f;
	ViewPortInfo.Width = 1280.0f;
	ViewPortInfo.TopLeftX = 0.0f;
	ViewPortInfo.TopLeftY = 0.0f;
	ViewPortInfo.MinDepth = 0.0f;
	ViewPortInfo.MaxDepth = 1.0f;
}


void URenderer::RasterizerSetting()
{
	UEngineCore::Device.GetContext()->RSSetViewports(1, &ViewPortInfo);
	UEngineCore::Device.GetContext()->RSSetState(RasterizerState.Get());
}

void URenderer::InputAssembler2Init()
{
	std::vector<unsigned int> Indexs;

	Indexs.push_back(0);
	Indexs.push_back(1);
	Indexs.push_back(2);

	Indexs.push_back(1);
	Indexs.push_back(3);
	Indexs.push_back(2);


	D3D11_BUFFER_DESC BufferInfo = { 0 };
	BufferInfo.ByteWidth = sizeof(unsigned int) * static_cast<int>(Indexs.size());
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = &Indexs[0];
	if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, &Data, &IndexBuffer))
	{
		MSGASSERT("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void URenderer::InputAssembler2Setting()
{
	int Offset = 0;

	// DXGI_FORMAT_R8_UINT; <= 옛날에는 아꼈다.
	// DXGI_FORMAT_R16_UINT; <= 옛날에는 아꼈다.
	UEngineCore::Device.GetContext()->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, Offset);

	UEngineCore::Device.GetContext()->IASetPrimitiveTopology(Topology);
}





void URenderer::PixelShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");


	std::string Path = File.GetPathToString();

	std::wstring WPath = UEngineString::AnsiToUnicode(Path);

	// 버전을 만든다.
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

void URenderer::PixelShaderSetting()
{
	UEngineCore::Device.GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
}

void URenderer::OutPutMergeSetting()
{
	// 배열 넣어줄수 있다. 
	// 0번이면 sv_target0
	ID3D11RenderTargetView* RTV = UEngineCore::Device.GetRTV();

	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
	ArrRtv[0] = RTV; // SV_Target0

	UEngineCore::Device.GetContext()->OMSetRenderTargets(1, &ArrRtv[0], nullptr);
}