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
	// 100번이 되었죠?
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
}

void URenderer::Render(float _DeltaTime)
{
	// 랜더링 파이프라인

}