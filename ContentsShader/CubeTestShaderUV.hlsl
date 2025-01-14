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


// ������۸� ����ϰڴ�.
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

	// ����
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

Input CubeTest_VS(EngineVertex _Vertex)
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

float4 CubeTest_PS(Input _Vertex) : SV_Target0
{
    float UVScale = 1;
    float2 scaledUV = _Vertex.UV.xy * UVScale; // UVScale�� float2 Ÿ������ �ݺ� Ƚ���� ����
    float4 texColor = bz_texture0.Sample(bz_sampler, frac(scaledUV));
    float4 multColor = 1; //{        1, 0.6, 0, 1};
    float4 finalColor = texColor * multColor;
    
    return finalColor;
};

// �����ʼ�
//float4 CubeTest_PS(Input _Vertex) : SV_Target0
//{
//    // UV ������ ����ȭ
//    float2 uv = frac(_Vertex.UV.xy);

//    float4 color;
//    if (uv.x < 0.25 && uv.y > 0.75)        // UV �� 0
//        color = float4(1, 0, 0, 1); // ����
//    else if (uv.x >= 0.25 && uv.x < 0.5 && uv.y > 0.75) // UV �� 1
//        color = float4(0, 1, 0, 1); // �ʷ�
//    else if (uv.x >= 0.5 && uv.x < 0.75 && uv.y > 0.75) // UV �� 2
//        color = float4(0, 0, 1, 1); // �Ķ�
//    else if (uv.x >= 0.75 && uv.x <= 1.0 && uv.y > 0.75) // UV �� 3
//        color = float4(1, 1, 0, 1); // ���
//    else if (uv.x < 0.25 && uv.y <= 0.75 && uv.y > 0.5)  // UV �� 4
//        color = float4(0.5, 0, 0.5, 1); // ����
//    else if (uv.x >= 0.25 && uv.x < 0.5 && uv.y <= 0.75 && uv.y > 0.5) // UV �� 5
//        color = float4(0, 1, 1, 1); // �ϴû�
//    else
//        color = float4(1, 1, 1, 1); // �⺻ ��� (���� ó��)

//    return color;
//};
