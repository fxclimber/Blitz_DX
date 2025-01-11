#include "PreCompile.h"
#include "BzEnemy.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include <EngineBase/EngineMath.h>

ABzEnemy::ABzEnemy()
{
	//std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	//RootComponent = Default;

	//Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	//Renderer->SetupAttachment(RootComponent);
	//Renderer->SetScale3D({ 50.f,100.f,20.f });
	//Renderer->SetPivot(PivotType::Bottom);
	//Renderer->GetRenderUnit().SetTexture("bz_texture0", "CheckUP.png");


	////----collision
	//Collision = CreateDefaultSubObject<UCollision>();
	//Collision->SetupAttachment(Renderer);
	//Collision->SetCollisionProfileName("Enemy");
	//Collision->SetCollisionType(ECollisionType::OBB);
	//Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
	//	{
	//		//_Other->GetActor()->Destroy();
	//		//UEngineDebug::OutPutString("Enter");
	//	});




}
