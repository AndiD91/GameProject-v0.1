#include <DirectXTemplatePCH.h>
#include "../resource.h"
#include "../Engine.h"

const LONG g_WindowWidth = 1280;
const LONG g_WindowHeight = 720;
LPCSTR g_WindowClassName = "DirectXWindowClass";
LPCSTR g_WindowName = "DirectX Template";
HWND g_WindowHandle = 0;

Engine engine;

// Forward declarations.
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int Run();

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

    g_WindowHandle = CreateWindowA( g_WindowClassName, g_WindowName, 
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

    return 0;
}



int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow )
{
    UNREFERENCED_PARAMETER( prevInstance );
    UNREFERENCED_PARAMETER( cmdLine );

    // Check for DirectX Math library support.
    if ( !DirectX::XMVerifyCPUSupport() )
    {
        MessageBox( nullptr, TEXT("Failed to verify DirectX Math library support."), TEXT("Error"), MB_OK );
        return -1;
    }

    if( InitApplication(hInstance, cmdShow) != 0 )
    {
        MessageBox( nullptr, TEXT("Failed to create applicaiton window."), TEXT("Error"), MB_OK );
        return -1;
    }

	engine.initEngine(hInstance, g_WindowHandle);
    

    int returnCode = Run();

	engine.Clear(DirectX::Colors::CornflowerBlue, 1.0f, 0);
	engine.Cleanup();

    return returnCode;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT paintStruct;
    HDC hDC;

    switch ( message )
    {
    case WM_PAINT:
        {
            hDC = BeginPaint( hwnd, &paintStruct );
            EndPaint( hwnd, &paintStruct );
        }
        break;
    case WM_DESTROY:
        {
            PostQuitMessage( 0 );
        }
        break;
    default: 
        return DefWindowProc( hwnd, message, wParam, lParam );
    }

    return 0;
}



/**
* The main application loop. Window Message Loop
*/
int Run()
{
	MSG msg = { 0 };

	static DWORD previousTime = timeGetTime();
	static const FLOAT targetFramerate = 30.0f;
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
			deltaTime = std::fmin(deltaTime, maxTimeStep);

			engine.Update(deltaTime);
			engine.Render();
		}
	}

	return static_cast<int>(msg.wParam);
}

