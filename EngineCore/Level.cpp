#include "PreCompile.h"
#include "Level.h"
#include "Actor.h"
#include "Renderer.h"
#include "EngineCore.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
}
void ULevel::LevelChangeStart()
{

}

void ULevel::LevelChangeEnd()
{

}


void ULevel::Tick(float _DeltaTime)
{
	std::list<std::shared_ptr<class AActor>>::iterator StartIter = BeginPlayList.begin();
	std::list<std::shared_ptr<class AActor>>::iterator EndIter = BeginPlayList.end();
	for (; StartIter != EndIter; )
	{
		std::shared_ptr<AActor> CurActor = *StartIter;

		if (false == CurActor->IsActive())
		{
			++StartIter;
			continue;
		}

		StartIter = BeginPlayList.erase(StartIter);

		CurActor->BeginPlay();
		AllActorList.push_back(CurActor);
	}

	// 절대 Ranged for안에서는 erase 리스트의 구조가 변경될 일을 하지 말라고 했ㅅ어요.
	for (std::shared_ptr<AActor> CurActor : AllActorList)
	{
		CurActor->Tick(_DeltaTime);
	}
}

void ULevel::Render(float _DeltaTime)
{
	UEngineCore::Device.RenderStart();

	// Ranged for를 돌릴때는 복사가 일어나므로
	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& RenderList = RenderGroup.second;

		for (std::shared_ptr<URenderer> Renderer : RenderList)
		{
			Renderer->Render(_DeltaTime);
		}
	}

	UEngineCore::Device.RenderEnd();
}



void ULevel::ChangeRenderGroup(int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer)
{
	// std::shared_ptr<URenderer> Renderer;

	Renderers[_PrevGroupOrder].remove(_Renderer);

	Renderers[_Renderer->GetOrder()].push_back(_Renderer);
}




