#include "PreCompile.h"
#include "EngineCamera.h"
#include "Renderer.h"

UEngineCamera::UEngineCamera()
{

}

void UEngineCamera::BeginPlay()
{
	FVector Scale = UEngineCore::GetScreenScale();

	ProjectionScale = Scale;
}

UEngineCamera::~UEngineCamera()
{
	Renderers.clear();
}

void UEngineCamera::Tick(float _DetlaTime)
{
	// 카메라는 틱에서 자신의 뷰와 프로젝트를 계산한다음 랜더러들에게 전달해줄 겁니다.
	Transform.View;
	Transform.Projection;
}

void UEngineCamera::Render(float _DetlaTime)
{
	//// Ranged for를 돌릴때는 복사가 일어나므로
	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& RenderList = RenderGroup.second;

		for (std::shared_ptr<URenderer> Renderer : RenderList)
		{
			Renderer->Render(this, _DetlaTime);
		}
	}
}

void UEngineCamera::ChangeRenderGroup(int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer)
{
	Renderers[_PrevGroupOrder].remove(_Renderer);
	Renderers[_Renderer->GetOrder()].push_back(_Renderer);
}

void UEngineCamera::CalculateViewAndProjection()
{
	FTransform& Trans = GetTransformRef();

	Trans.View.View(Trans.World.ArrVector[3], Trans.World.GetFoward(), Trans.World.GetUp());

	Trans.Projection.OrthographicLH(ProjectionScale.X, ProjectionScale.Y, Near, Far);

	int a = 0;
}