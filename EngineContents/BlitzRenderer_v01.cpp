#include "PreCompile.h"
#include "BlitzRenderer_v01.h"

BlitzRenderer_v01::BlitzRenderer_v01()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("BlitzMaterial");
	//SetMaterial("MyMaterial");

	myColor.Albedo = float4(1.0f, 1.0f, 1.0f, 1.0f);

	GetRenderUnit().ConstantBufferLinkData("myColor", myColor);
}

BlitzRenderer_v01::~BlitzRenderer_v01()
{

}
