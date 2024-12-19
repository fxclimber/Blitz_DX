#include "PreCompile.h"
#include "EngineGraphicDevice.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
    Release();
}

void UEngineGraphicDevice::Release()
{
    MainAdapter = nullptr;
    DXBackBufferTexture = nullptr;
    RTV = nullptr;
    SwapChain = nullptr;
    Context = nullptr;
    Device = nullptr;
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
    // 이걸 통해서 만든 애는 그래픽카드에 메모리가 잡힙니다.
    IDXGIFactory* Factory = nullptr;
    unsigned __int64 MaxVideoMemory = 0;
    IDXGIAdapter* ResultAdapter = nullptr;


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
        return nullptr;
    }



    for (int Index = 0;; ++Index)
    {
        IDXGIAdapter* CurAdapter = nullptr;
        Factory->EnumAdapters(Index, &CurAdapter);

        if (nullptr == CurAdapter)
        {
            break;
        }

        // 정보구조체가 있고
        DXGI_ADAPTER_DESC Desc;

        // 장치 핸들에서 빼오는 식입니다.
        CurAdapter->GetDesc(&Desc);

        // 램 크기가 크면 성능도 좋겠지.
        // 100메가 짜리를      200
        if (MaxVideoMemory <= Desc.DedicatedVideoMemory)
        {
            MaxVideoMemory = Desc.DedicatedVideoMemory;
            //            100 
            if (nullptr != ResultAdapter)
            {
                ResultAdapter->Release();
            }

            // 100          200
            ResultAdapter = CurAdapter;
            continue;
        }

        CurAdapter->Release();
    }

    if (nullptr != Factory)
    {
        Factory->Release();
    }

    if (nullptr == ResultAdapter)
    {
        MSGASSERT("그래픽카드가 달려있지 않은 컴퓨터입니다.");
        return nullptr;
    }

    // int Test = MaxVideoMemory / (1024 * 1024 * 1024);

    return ResultAdapter;
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

    // 가장 성능 좋은 그래픽 카드를 찾았다.
    MainAdapter = GetHighPerFormanceAdapter();

    int iFlag = 0;

#ifdef _DEBUG
    // 디버그 모드일때만
//  D3D11_CREATE_DEVICE_SINGLETHREADED = 0x1,
//	D3D11_CREATE_DEVICE_DEBUG = 0x2,
//	D3D11_CREATE_DEVICE_SWITCH_TO_REF = 0x4,
//	D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,
//	D3D11_CREATE_DEVICE_BGRA_SUPPORT = 0x20,
//	D3D11_CREATE_DEVICE_DEBUGGABLE = 0x40,
//	D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY = 0x80,
//	D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT = 0x100,
//	D3D11_CREATE_DEVICE_VIDEO_SUPPORT = 0x800
    iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif


    //D3D_DRIVER_TYPE DriverType,
    // D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN 내가 넣어줬으니 그걸로 해
    // D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE 니가 알아서 그래픽 카드 찾아줘.
    // D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_SOFTWARE 그래픽카드 안쓸께.
    // 그래픽카드를 안쓰겠다.

    //HMODULE Software, // 특정 단계용(랜더링 파이프라인의 일부를 내가 만든 코드로 교체하기 위한 dll 핸들)

    //UINT Flags, // 옵션

    //_In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    //UINT FeatureLevels,
    //UINT SDKVersion,
    //_COM_Outptr_opt_ ID3D11Device** ppDevice,
    //_Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    // D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN 내가 준 어뎁터로 해라.

    D3D_FEATURE_LEVEL ResultLevel;

    // _COM_Outptr_opt_ ID3D11Device** ppDevice,
    // _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    // _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext

    HRESULT Result = D3D11CreateDevice(
        MainAdapter.Get(),
        D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
        nullptr, // 특정 단계를 내가 짠 코드로 대체하겠다.
        iFlag,
        nullptr, // 강제레벨 지정 11로 만들거니까. 배열을 넣어줄수
        0, // 내가 지정한 팩처레벨 개수
        D3D11_SDK_VERSION, // 현재 다이렉트x sdk 버전
        &Device,
        &ResultLevel,
        &Context);

    if (nullptr == Device)
    {
        MSGASSERT("그래픽 디바이스 생성에 실패했습니다.");
        return;
    }

    if (nullptr == Context)
    {
        MSGASSERT("그래픽 컨텍스트 생성에 실패했습니다.");
        return;
    }

    if (Result != S_OK)
    {
        MSGASSERT("뭔가 잘못됨.");
        return;
    }

    if (ResultLevel != D3D_FEATURE_LEVEL_11_0
        && ResultLevel != D3D_FEATURE_LEVEL_11_1)
    {
        MSGASSERT("다이렉트 11버전을 지원하지 않는 그래픽카드 입니다.");
        return;
    }

    // 다이렉트 x가 기본적으로 쓰레드 안정성을 안챙겨준다.
    // 고급 랜더링과 서버에서는 쓰레드는 필수이기 때문에
    // 쓰레드를 사용하겠다는 것을 미리 명시해줄수 있다.
    Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    if (Result != S_OK)
    {
        MSGASSERT("쓰레드 안정성 적용에 문제가 생겼습니다.");
        return;
    }
    // 초기화 종료
}

void UEngineGraphicDevice::CreateBackBuffer(const UEngineWindow& _Window)
{
    // 윈도우 크기로 만든게 관례에 가깝다.
    // 내가 원하는 크기로 만드는게 맞다.
    // 그런거 안끌어쓰고 직접 만드는 네이티브 다이렉트 x식 리소스는 이게 마지막

    FVector Size = _Window.GetWindowSize();

    DXGI_SWAP_CHAIN_DESC ScInfo = { 0 };

    ScInfo.BufferCount = 2;
    ScInfo.BufferDesc.Width = Size.iX();
    ScInfo.BufferDesc.Height = Size.iY();
    ScInfo.OutputWindow = _Window.GetWindowHandle();
    // 전체화면
    // false면 전체화면
    // true면 창화면
    ScInfo.Windowed = true;

    // 주 사율 모니터에 얼마나 빠르게 갱신할거냐
    // 할수 있으면 해라.
    ScInfo.BufferDesc.RefreshRate.Denominator = 1;
    ScInfo.BufferDesc.RefreshRate.Numerator = 60;
    // ScInfo.BufferDesc.RefreshRate.Numerator = 144;

    // 백버퍼의 색갈범위
    // 65536 단계
    // 색상의 단위가 더 큰 모니터에서는 의미가 있다.
    //                                     8 8 8 8 32비트 색상으로 백버퍼를 만들어
    ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // 모니터 때문에 의미 없음. HDR 모니터면 의미를 가질수도 있다.
    // ScInfo.BufferDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

    // 모니터나 윈도우에 픽셀이 갱신되는 순서를 어떻게 
    // 그냥 제일 빠른걸로 해줘
    ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    // 진짜 기억안남 아예 
    ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // 용도
    // DXGI_USAGE_RENDER_TARGET_OUTPUT 화면에 그려지는 용도로 사용한다.
    //                   여기에 그릴수 있음                  쉐이더에서 데이터로도 사용할수 있음
    ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

    // 샘플링
    // 퀄리티도 필요없고
    ScInfo.SampleDesc.Quality = 0;
    // 점 개수도 1개면 충분하다.
    ScInfo.SampleDesc.Count = 1;

    // 버퍼 n개 만들었네?
    // n개의 버퍼에 대한 
    ScInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    // 전혀 기억안남
    ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    //MainAdapter->Release();

    IDXGIFactory* pF = nullptr;

    // 날 만든 팩토리를 얻어올수 있다.
    MainAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));

    // IUnknown* pDevice,
    // DXGI_SWAP_CHAIN_DESC* pDesc,
    // IDXGISwapChain** ppSwapChain

    pF->CreateSwapChain(Device.Get(), &ScInfo, &SwapChain);
    pF->Release();
    MainAdapter->Release();

    if (nullptr == SwapChain)
    {
        MSGASSERT("스왑체인 제작에 실패했습니다.");
    }

    // HDC라고 보면 됩니다.
    // 스왑체인 내부에 존재하는 
    // HDC안에 bitmap이 들어있는 개념이었죠?
    // bitmap => 진짜 색깔 배열에 대한 핸들
    // FColor Arr[100][100];
    // directx에서는 이런 bitmap이 id3d11texture2d*

    // SwapChain내부에 id3d11texture2d*들고 있다.
    // DXBackBufferTexture => 는 BITMAP입니다.

    if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(DXBackBufferTexture.GetAddressOf())))
    {
        MSGASSERT("백버퍼 텍스처를 얻어오는데 실패했습니다.");
    };


    // id3d11texture2d* 이녀석 만으로는 할수 있는게 많이 없습니다.
    // 애는 이미지의 2차원 데이터를 나타낼뿐 수정권한은 없기 때문입니다.
    // 이미지를 수정하거나 사용할수 있는 권한을 id3d11texture2d*을 얻어내야 합니다.
    // WINAPI에서 HDC 얻어내는 것처럼 id3d11texture2d* 수정권한인
    // 텍스처에서 만들어내야 합니다.

    //                             HBITMAP                       HDC
    if (S_OK != Device->CreateRenderTargetView(DXBackBufferTexture.Get(), nullptr, &RTV))
    {
        MSGASSERT("텍스처 수정권한 획득에 실패했습니다");
    }

}


void UEngineGraphicDevice::RenderStart()
{
    FVector ClearColor;

    ClearColor = FVector(0.0f, 0.0f, 1.0f, 1.0f);

    // 이미지 파란색으로 채색해줘.
    Context->ClearRenderTargetView(RTV.Get(), ClearColor.Arr1D);
}

void UEngineGraphicDevice::RenderEnd()
{
    // 내가 지정한 hwnd에 다이렉트 랜더링 결과를 출력해라.
    // 
    HRESULT Result = SwapChain->Present(0, 0);

    //             디바이스가 랜더링 도중 삭제          디바이스가 리셋되었을경우
    if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
    {
        MSGASSERT("해상도 변경이나 디바이스 관련 설정이 런타임 도중 수정되었습니다");
        return;
    }
}