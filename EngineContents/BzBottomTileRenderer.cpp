#include "PreCompile.h"
#include "BzBottomTileRenderer.h"
#include <EngineCore/EngineCamera.h>



UBzBottomTileRenderer::UBzBottomTileRenderer()
{
	CreateRenderUnit();
	SetMesh("Cube");
	SetMaterial("BzDefault");

	//GetRenderUnit().ConstantBufferLinkData("ResultColor", ColorData);
	//GetRenderUnit().ConstantBufferLinkData("FSpriteData", SpriteData);
	//GetRenderUnit().ConstantBufferLinkData("FUVValue", UVValue);



}

UBzBottomTileRenderer::~UBzBottomTileRenderer()
{
}

void UBzBottomTileRenderer::SetTileSetting(std::string_view _Name, FVector _TileSize)
{
	GetRenderUnit().ConstantBufferLinkData("FBzColor", TestColor);

	TileSize = _TileSize;
}

void UBzBottomTileRenderer::BeginPlay()
{
	URenderer::BeginPlay();

}

BzFTileIndex UBzBottomTileRenderer::WorldPosToTileIndex(FVector _Pos)
{
	BzFTileIndex Result = BzFTileIndex();

		FVector ConvertVector = _Pos /= TileSize;
		//Result.X = ConvertVector.iX();
		//Result.Y = ConvertVector.iY();
		//Result.Z = ConvertVector.iZ();
		Result.X = static_cast<int>(ConvertVector.X);
		Result.Y = static_cast<int>(ConvertVector.Y);
		Result.Z = static_cast<int>(ConvertVector.Z);

	return Result;
}

FVector UBzBottomTileRenderer::TileIndexToWorldPos(BzFTileIndex _Index)
{
	FVector Result;
		Result.X = _Index.X * TileSize.X;
		Result.Y = _Index.Y * TileSize.Y;
		Result.Z = _Index.Z * TileSize.Z;

	return Result;
}

void UBzBottomTileRenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
{
	// URenderer::Render(_Camera, _DeltaTime);
	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();
	//	// 랜더러는 월드 뷰 프로젝트를 다 세팅받았고
	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;


	if (0 == Tiles.size())
	{
		return;
	}

	URenderUnit& Unit = GetRenderUnit();

	FTransform Trans;
	FMatrix Scale;
	FMatrix Pos;

	for (std::pair<const __int64, BzFTileData>& TilePair : Tiles)
	{
		BzFTileData& Tile = TilePair.second;
		BzFTileIndex Index;

		GetRenderUnit().SetTexture("bz_texture0", "b22.jpg");

		Index.Key = TilePair.first;

		FVector ConvertPos = TileIndexToWorldPos(Index);

		Pos.Position({ ConvertPos.X, ConvertPos.Y, 0.0f });

		Trans.WVP = Scale * Pos * RendererTrans.View * RendererTrans.Projection;

		GetRenderUnit().ConstantBufferLinkData("FTransform", Trans);
		GetRenderUnit().ConstantBufferLinkData("ResultColor", Tile.ColorData);
		Unit.Render(_Camera, _DeltaTime);
	}

}

void UBzBottomTileRenderer::SetTile(FVector _Pos, int _Index)
{
	BzFTileIndex Index = WorldPosToTileIndex(_Pos);

	SetTile(Index.X, Index.Y, Index.Z, _Index);
}

void UBzBottomTileRenderer::RemoveTile(FVector _Pos)
{
	BzFTileIndex Index = WorldPosToTileIndex(_Pos);

	RemoveTile(_Pos.X, _Pos.Y, _Pos.Z);
}

void UBzBottomTileRenderer::SetTile(int _X, int _Y, int _Z, int _Index)
{
	BzFTileIndex Index = { _X, _Y, _Z};

	BzFTileData& NewTile = Tiles[Index.Key];

	NewTile.Index = Index;
	NewTile.ColorData.PlusColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	NewTile.ColorData.MulColor = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void UBzBottomTileRenderer::RemoveTile(int _X, int _Y , int _Z)
{
	BzFTileIndex Index = { _X, _Y , _Z };

	if (false == Tiles.contains(Index.Key))
	{
		return;
	}

	Tiles.erase(Index.Key);
}


void UBzBottomTileRenderer::ComponentTick(float _DeltaTime)
{
	URenderer::ComponentTick(_DeltaTime);
}

void UBzBottomTileRenderer::SetPivot(PivotType _pivot)
{
	FVector scale = GetWorldScale3D();
	FVector loc = { 0.f,0.f,0.f };

	switch (_pivot)
	{
	case PivotType::Center:
		loc = { 0.f,0.f,0.f };
		AddRelativeLocation(loc);
		break;
	case PivotType::Bottom:
		loc = { 0.f,scale.Y,0.f };
		AddRelativeLocation(loc);
		break;
	case PivotType::Top:
		loc = { 0.f,-scale.Y / 2,0.f };
		AddRelativeLocation(loc);
		break;

	default:
		break;
	}
}


void UBzBottomTileRenderer::Serialize(UEngineSerializer& _Ser)
{
	_Ser << TileSize;
	_Ser << TilePivot;

	_Ser << static_cast<int>(Tiles.size());
	for (std::pair<const __int64, BzFTileData>& Pair : Tiles)
	{
		_Ser.Write(&Pair.second, sizeof(BzFTileData));
	}
}
// 데이터를 복구(할때)
void UBzBottomTileRenderer::DeSerialize(UEngineSerializer& _Ser)
{
	Tiles.clear();

	//_Ser.Read(&TileMapType, sizeof(int));
	_Ser >> TileSize;
	_Ser >> TilePivot;


	int Count = 0;
	_Ser >> Count;
	for (size_t i = 0; i < Count; i++)
	{
		BzFTileData TileData;
		_Ser.Read(&TileData, sizeof(TileData));
		Tiles.insert({ TileData.Index.Key, TileData });
	}
}