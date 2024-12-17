#include "PreCompile.h"
#include "EngineGraphicDevice.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
}

void UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
    // 이걸 통해서 만든 애는 그래픽카드에 메모리가 잡힙니다.
    IDXGIFactory* Factory = nullptr;
    IDXGIAdapter* Adapter = nullptr;


    // Factory는 다이렉트 x에서 지원하는 그래픽카드 메모리에 생성을 담당해주는 인터페이스 입니다.
    // #pragma comment(lib, "dxguid")
    // 다이렉트x와 같은 라이브러리들은 클래스를 인지하는게 아니고
    // GUID라는 것으로 코드 덩어리를 그때그때마다 로드하는 방식을 취하는데.

    //MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369") => GUID라고 한다.
    //   IDXGIFactory : public IDXGIObject


    HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

    if (nullptr == Factory)
    {
        MSGASSERT("그래픽카드 조사용 팩토리 생성에 실패했습니다.");
        return;
    }

    for (int Index = 0;; ++Index)
    {
        IDXGIAdapter* CurAdapter = nullptr;

        Factory->EnumAdapters(Index, &CurAdapter);

        if (nullptr == CurAdapter)
        {
            break;
        }

        Adapter = CurAdapter;
    }

    if (nullptr != Factory)
    {
        Factory->Release();
    }

    if (nullptr == Adapter)
    {
        MSGASSERT("그래픽카드가 달려있지 않은 컴퓨터입니다.");
        return;
    }


    Adapter->Release();
}

void UEngineGraphicDevice::CreateDeviceAndContext()
{
    // 디바이스를 만들려면
    // 디바이스 버전부터 정해줘야 합니다.
    // 디바이스의 모드를 정해줘야 합니다


    //IDXGIAdapter* pAdapter,
    // 그래픽장지 사양정보를 알려주세요.
    // nullptr 넣어주면 알아서 찾아.
    // 그래픽카드 2개 달려있는 사람들이 있다.


    //D3D_DRIVER_TYPE DriverType,
    //HMODULE Software,
    //UINT Flags,
    //_In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    //UINT FeatureLevels,
    //UINT SDKVersion,
    //_COM_Outptr_opt_ ID3D11Device** ppDevice,
    //_Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    //_COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext

    GetHighPerFormanceAdapter();

#ifdef _DEBUG
#endif

    // D3D11CreateDevice();

}

void UEngineGraphicDevice::CreateBackBuffer(const UEngineWindow& _Window)
{
    int a = 0;
}