struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};


struct Input
{
    float4 SVPOSITION : SV_POSITION; 
    float4 UV : TEXCOORD; 
    float4 COLOR : COLOR;
};

Texture2D bz_texture0 : register(t0);
SamplerState bz_sampler : register(s0);


// 상수버퍼를 사용하겠다.
cbuffer FTransform : register(b0)
{

    float4 Scale;
    float4 Rotation;
    float4 Qut;
    float4 Location;

    float4 RelativeScale;
    float4 RelativeRotation;
    float4 RelativeQut;
    float4 RelativeLocation;

	// 월드
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuat;
    float4 WorldLocation;

    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 LocationMat;
    float4x4 RevolveMat;
    float4x4 ParentMat;
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};

Input Bz_VS(EngineVertex _Vertex)
{
    Input OutPut;
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
    OutPut.UV = _Vertex.UV;
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}

cbuffer FBzColor : register(b0)
{
    float4 Albedo;
};

float4 Bz_PS(Input _Vertex) : SV_Target0
{
    float UVScale = 50;
    float2 scaledUV = _Vertex.UV.xy * UVScale; // UVScale은 float2 타입으로 반복 횟수를 설정
    float4 texColor = bz_texture0.Sample(bz_sampler, frac(scaledUV));
    float4 multColor = {1,0.6,0,1 };
    float4 finalColor = texColor * multColor;
    
    //return bz_texture0.Sample(bz_sampler, _Vertex.UV.xy);
    return finalColor;
	
};
