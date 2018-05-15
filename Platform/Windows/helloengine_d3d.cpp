// include the basic windows header file.
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdint.h>

#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

// global declarations
IDXGISwapChain			*g_pSwapchain	= nullptr;	// the pointer to the swap chain interface
ID3D11Device			*g_pDev			= nullptr;	// the pointer to our Direct3D device interface
ID3D11DeviceContext		*g_pDevcon		= nullptr;	// the pointer to our Direct3D device context

ID3D11RenderTargetView	*g_pRTView		= nullptr;

ID3D11InputLayout		*g_pLayout		= nullptr;	// the pointer to the input layout
ID3D11VertexShader		*g_pVS			= nullptr;	// the pointer to the vertex shader
ID3D11PixelShader		*g_pPS			= nullptr;	// the pointer to the pixel shader

ID3D11Buffer			*g_pVBuffer		= nullptr;	// Vertex Buffer

// vertex buffer structure
struct VERTEX{
	XMFLOAT3	Position;
	XMFLOAT4	Color;	
};

template<class T>
inline void SafeRelease(T ** ppInterfaceToRelease)
{
    if(*ppInterfaceToRelease != nullptr)
    {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = nullptr;       
    }    
}

void CreateRenderTarget()
{
	HRESULT hr;
	ID3D11Texture2D *pBackBuffer;
	
	// Get a pointer to the back buffer
	g_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	
	// Create a render-target view
	g_pDev->CreateRenderTargetView(pBackBuffer, NULL, &g_pRTView);
	
	pBackBuffer->Release();
	
	// Bind the view
	g_pDevcon->OMSetRenderTargets(1, &g_pRTView, NULL);
	
}

void SetViewPort()
{	
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;
	
	g_pDevcon->RSSetViewports(1, &viewport);
}

// this is the function that loads and prepares the shaders
void InitPipeline()
{
	// load and compile the two shaders
	ID3DBlob *VS, *PS;
	
	D3DReadFileToBlob(L"copy.vso", &VS);
	D3DReadFileToBlob(L"copy.pso", &PS);
	
	// encapsulate both shaders into shader objects
	g_pDev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &g_pVS);
	g_pDev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &g_pPS);
	
	// set the shader objects
	g_pDevcon->VSSetShader(g_pVS, 0, 0);
	g_pDevcon->PSSetShader(g_pPS, 0, 0);
	
	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},		
	};
	
	g_pDev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &g_pLayout);
	g_pDevcon->IASetInputLayout(g_pLayout);
	
	VS->Release();
	PS->Release();
}

// this is the function that creates the shape to render-target
void InitGraphics()
{
	// create a triangle using the VERTEX struct
	VERTEX OurVertices[] = 
	{
		{XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
	};
	
	// create the vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	
	bd.Usage = D3D11_USAGE_DYNAMIC;		// write access by CPU and GPU
	bd.ByteWidth = sizeof(VERTEX) * 3;	// size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// allow CPU to write in buffer
	
	g_pDev->CreateBuffer(&bd, NULL, &g_pVBuffer);	// create the buffer
	
	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	g_pDevcon->Map(g_pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);	// map the buffer
	memcpy(ms.pData, OurVertices, sizeof(VERTEX) * 3);		// copy the data
	g_pDevcon->Unmap(g_pVBuffer, NULL);				// unmap the buffer
}

HRESULT CreateGraphicsResources(HWND hWnd)
{
    HRESULT hr = S_OK;
    if(pRenderTarget == nullptr)
    {
        RECT rc;
        GetClientRect(hWnd, &rc);
        
        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
        
        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size),
            &pRenderTarget);
            
        if(SUCCEEDED(hr))
        {
            hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &pLightSlateGrayBrush);
        }
        
        if(SUCCEEDED(hr))
        {
            hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &pCornflowerBlueBrush);            
        }
    }
    
    return hr;
    
}

void DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pLightSlateGrayBrush);
    SafeRelease(&pCornflowerBlueBrush);    
}



// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);
                         
// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPTSTR lpCmdLine,
                    int nCmdShow)
{
    // the handle for the window, filled by a function
    HWND hWnd;
    
    // this struct holds information for the window class
    WNDCLASSEX wc;
    
    // initialize COM
    if(FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) return -1;
    
    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    
    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");
    
    // register the window class
    RegisterClassEx(&wc);
    
    // create the window and use the result as the handle
    hWnd = CreateWindowEx(0,
                        _T("WindowClass1"),     // name of the window class
                        _T("Hello, Engine![Direct 2D]"),   // title of the window
                        WS_OVERLAPPEDWINDOW,    // window style
                        100,    // x-position of the window
                        100,    // y-position of the window
                        960,    // width of the window
                        540,    // height of the window
                        NULL,   // we have no parent window, NULL
                        NULL,   // we aren't using menus, NULL
                        hInstance,  // application handle
                        NULL);  // used with multiple windows, NULL
    
    // display the window on the screen
    ShowWindow(hWnd, nCmdShow);
    
    // enter the main loop
    
    // this struct holds Windows event messages
    MSG msg;
    
    // wait for the next message in the queue, store the result in 'msg'
    while(GetMessage(&msg, NULL, 0, 0))
    {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);
        
        // send the message to the WindowProc function
        DispatchMessage(&msg);        
    }
    
    CoUninitialize();
    
    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    bool wasHandled = false;
    
    // sort through and find what code to run for the message given
    switch(message)
    {
        case WM_CREATE:
            if(FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
            {
                result = -1;
                return result;
            }
            wasHandled = true;
            result = 0;
            break;
        case WM_PAINT:
            {
                HRESULT hr = CreateGraphicsResources(hWnd);
                if(SUCCEEDED(hr)){
                    PAINTSTRUCT ps;
                    BeginPaint(hWnd, &ps);
                    
                    // start build GPU draw command
                    pRenderTarget->BeginDraw();
                    
                    // clear the background with white color
                    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
                    
                    // retrieve the size of drawing area
                    D2D1_SIZE_F rtSize = pRenderTarget->GetSize();
                    
                    // draw a grid background.
                    int width = static_cast<int>(rtSize.width);
                    int height = static_cast<int>(rtSize.height);
                    
                    for(int x = 0; x < width; x += 10)
                    {
                        pRenderTarget->DrawLine(D2D1::Point2F(static_cast<FLOAT>(x), 0.0f), 
                                                D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
                                                pLightSlateGrayBrush,
                                                0.5f);
                    }
                    
                    for(int y = 0; y < height; y += 10)
                    {
                        pRenderTarget->DrawLine(D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                                                D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
                                                pLightSlateGrayBrush,
                                                0.5f);
                    }
                    
                    // draw two rectangles
                    D2D1_RECT_F rectangle1 = D2D1::RectF(
                        rtSize.width/2 - 50.0f,
                        rtSize.height/2 - 50.0f,
                        rtSize.width/2 + 50.0f,
                        rtSize.height/2 + 50.0f
                    );
                    
                    D2D1_RECT_F rectangle2 = D2D1::RectF(
                        rtSize.width/2 - 100.0f,
                        rtSize.height/2 - 100.0f,
                        rtSize.width/2 + 100.0f,
                        rtSize.height/2 + 100.0f
                    );
                    
                    // draw a filled rectangle
                    pRenderTarget->FillRectangle(&rectangle1, pLightSlateGrayBrush);
                    
                    // draw a outline only rectangle
                    pRenderTarget->DrawRectangle(&rectangle2, pCornflowerBlueBrush);
                    
                    // end GPU draw command building
                    hr = pRenderTarget->EndDraw();
                    if(FAILED(hr) || hr == D2DERR_RECREATE_TARGET){
                        DiscardGraphicsResources();
                    }
                    EndPaint(hWnd, &ps);
                }
                wasHandled = true;
            }break;
            
        case WM_SIZE:
            if(pRenderTarget != nullptr)
            {
                RECT rc;
                GetClientRect(hWnd, &rc);
                
                D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
                
                pRenderTarget->Resize(size);
            }
            wasHandled = true;
            break;
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                DiscardGraphicsResources();
                if(pFactory){
                    pFactory->Release();
                    pFactory = nullptr;
                }
                // close the application entirely
                PostQuitMessage(0);
                result = 0;
                wasHandled = true;
            }break;
        case WM_DISPLAYCHANGE:
            InvalidateRect(hWnd, nullptr, false);
            wasHandled = true;
            break;
    }
    
    // handle any messages the switch statement didn't
    if(!wasHandled){result = DefWindowProc(hWnd, message, wParam, lParam);}
    return result;    
}
















