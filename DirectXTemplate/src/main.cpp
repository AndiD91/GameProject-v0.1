#include <DirectXTemplatePCH.h>
#include "../resource.h"
#include "../Engine.h"

const LONG g_WindowWidth = 1280;
const LONG g_WindowHeight = 720;
LPCSTR g_WindowClassName = "DirectXWindowClass";
LPCSTR g_WindowName = "DirectX Template";
HWND g_WindowHandle = 0;

Engine engine;
Camera camera;

WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };

void SetFullscreen(HWND hwnd, INT x, INT y, UINT keyFlags)
{
	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	if (dwStyle & WS_OVERLAPPEDWINDOW) {
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(hwnd, &g_wpPrev) &&
			GetMonitorInfo(MonitorFromWindow(hwnd,
			MONITOR_DEFAULTTOPRIMARY), &mi)) {
			SetWindowLong(hwnd, GWL_STYLE,
				dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP,
				mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}
	else {
		SetWindowLong(hwnd, GWL_STYLE,
			dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(hwnd, &g_wpPrev);
		SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (message)
	{
	case WM_PAINT:
	{
		hDC = BeginPaint(hwnd, &paintStruct);
		EndPaint(hwnd, &paintStruct);
	}
	case WM_KEYDOWN:
		if (wParam == VK_F11)
		{
			SetFullscreen(hwnd,0,0,0);
			return 0L;
		}
		if (wParam== VK_SPACE)
		{
			camera.setPerspective();
		}
		if (wParam == VK_SHIFT)
		{
			camera.setOrthographic();
		}

	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}



/**
 * Initialize the application window.
 */
int InitApplication( const HINSTANCE hInstance, const INT cmdShow )
{
    WNDCLASSEX wndClass = {0};
    wndClass.cbSize = sizeof( WNDCLASSEX );
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = &WndProc;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wndClass.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndClass.lpszMenuName = nullptr;
    wndClass.lpszClassName = g_WindowClassName;

    if ( !RegisterClassEx(&wndClass) )
    {
        return -1;
    }

    RECT windowRect = { 0, 0, g_WindowWidth, g_WindowHeight };
    AdjustWindowRect( &windowRect, WS_OVERLAPPEDWINDOW, FALSE );

    g_WindowHandle = CreateWindow( g_WindowClassName, g_WindowName, 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
        windowRect.right - windowRect.left, 
        windowRect.bottom - windowRect.top, 
        nullptr, nullptr, hInstance, nullptr );

    if ( !g_WindowHandle )
    {
        return -1;
    }

    ShowWindow( g_WindowHandle, cmdShow );
    UpdateWindow( g_WindowHandle );
	SetForegroundWindow(g_WindowHandle);
	SetFocus(g_WindowHandle);

    return 0;
}

/**
* The main application loop. Window Message Loop
*/
INT Run()
{
	MSG msg = { 0 };

	static DWORD previousTime = timeGetTime();
	static const FLOAT targetFramerate = 60.0f;
	static const FLOAT maxTimeStep = 1.0f / targetFramerate;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD currentTime = timeGetTime();
			FLOAT deltaTime = (currentTime - previousTime) / 1000.0f;
			previousTime = currentTime;

			// Cap the delta time to the max time step (useful if your 
			// debugging and you don't want the deltaTime value to explode.
			deltaTime = fmin(deltaTime, maxTimeStep);

			engine.Update(deltaTime);
			engine.Render();
		}
	}

	return static_cast<INT>(msg.wParam);
}

INT WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, INT cmdShow )
{
	
    if( InitApplication(hInstance, cmdShow) != 0 )
    {
        MessageBox( nullptr, TEXT("Failed to create applicaiton window."), TEXT("Error"), MB_OK );
        return -1;
    }


	// Setup the projection matrix.
	RECT clientRect;
	GetClientRect(g_WindowHandle, &clientRect);

	// Compute the exact client dimensions.
	// This is required for a correct projection matrix.
	FLOAT clientWidth = static_cast<FLOAT>(clientRect.right - clientRect.left);
	FLOAT clientHeight = static_cast<FLOAT>(clientRect.bottom - clientRect.top);

	 camera = Camera(DirectX::XMVectorSet(0, 0, -10, 1), DirectX::XMVectorSet(0, 0, 0, 1), DirectX::XMVectorSet(0, 1, 0, 0), clientWidth / clientHeight, DirectX::XMConvertToRadians(45), 0.1F, 100.0F);
	
	engine.setActiveCamera(camera);
	

	//SetWindowText(g_WindowHandle,"Cambodunum");
	if(!engine.initEngine(hInstance, g_WindowHandle,Engine::DIRECTX))
	{
		MessageBox(nullptr, TEXT("Failed to init Engine."), TEXT("Error"), MB_OK);
		return -1;
	}

	
    INT returnCode = Run();

	engine.Clear(DirectX::Colors::CornflowerBlue, 1.0f, 0);
	engine.Cleanup();

    return returnCode;
}






