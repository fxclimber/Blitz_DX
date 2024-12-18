#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{
}

URenderer::~URenderer()
{
	VertexBuffer->Release();

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
}

void URenderer::Render(float _DeltaTime)
{
	InputAssembler1Setting();

	// 버텍스 버퍼라는걸 세팅한다.
	// UEngineCore::Device.GetContext()->IASetVertexBuffers();

	// 레스터라이저를 세팅한다.
	// UEngineCore::Device.GetContext()->RSSetState();

	// 그린다 전에 세팅이건 뭐건 리소스건 어떤 순서로 하건 아무런 의미도 없다.
	// 이거 한번 호출이 드로우콜 1번이다.
	// UEngineCore::Device.GetContext()->Draw()


}

void URenderer::InputAssembler1Init()
{
	// 버텍스 버퍼를 그래픽카드에게 만들어 달라고 요청

	// 여기는 이미 ram
	// CPU
	std::vector<EngineVertex> Vertexs;
	Vertexs.resize(6);

	Vertexs[0] = EngineVertex{ FVector(-0.5f, 0.5f, -0.5f), {} };
	Vertexs[1] = EngineVertex{ FVector(0.5f, 0.5f, -0.5f), {} };
	Vertexs[2] = EngineVertex{ FVector(-0.5f, -0.5f, -0.5f), {} };
	Vertexs[3] = EngineVertex{ FVector(0.5f, 0.5f, -0.5f), {} };
	Vertexs[4] = EngineVertex{ FVector(0.5f, -0.5f, -0.5f), {} };
	Vertexs[5] = EngineVertex{ FVector(-0.5f, -0.5f, -0.5f), {} };


	D3D11_BUFFER_DESC BufferInfo = { 0 };

	BufferInfo.ByteWidth = sizeof(EngineVertex) * Vertexs.size();
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

	// 
}

void URenderer::InputAssembler1Setting()
{

}
