#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{
}

URenderer::~URenderer()
{
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

}

void URenderer::InputAssembler1Setting()
{

}
