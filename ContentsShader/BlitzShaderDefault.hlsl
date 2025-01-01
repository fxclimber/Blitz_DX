// ���� ����ü ����
struct vertexShaderInput
{
    float4 POSITION : POSITION; // ��ġ ������
    //float4 UV : TEXCOORD; // UV ������ (������� ����)
    float4 COLOR : COLOR; // ���� ������
};
// ���� ���̴� ��� ����ü
struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // Ŭ�� ���� ��ġ
    float4 COLOR : COLOR; // ���� ������
};
// ��� ���� ����
cbuffer FTransform : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Location;
    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 LocationMat;
    float4x4 RevoleMat;
    float4x4 ParentMat;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};
// ������ ���� ���̴�
VertexShaderOutPut TestToVertex(vertexShaderInput _Vertex)
{
    VertexShaderOutPut OutPut;
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
		
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}
// �ȼ� ���̴� ����
float4 PixelToWorld(VertexShaderOutPut _Vertex) : SV_Target0
{
    //return _Vertex.COLOR;
    return float4(1, 1, 0, 1);
}
