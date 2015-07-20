#include "DirectXTemplatePCH.h"
#include "Game.h"


Game::Game()
{
}


Game::Game(HWND hwnd, HINSTANCE hInstance, Engine* engine) :theEngine(engine)
{
	// Setup the projection matrix.
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	// Compute the exact client dimensions.
	// This is required for a correct projection matrix.
	FLOAT clientWidth = static_cast<FLOAT>(clientRect.right - clientRect.left);
	FLOAT clientHeight = static_cast<FLOAT>(clientRect.bottom - clientRect.top);

	camera=Camera(DirectX::XMVectorSet(0, 0, -10, 1), DirectX::XMVectorSet(0, 0, 0, 1), DirectX::XMVectorSet(0, 1, 0, 0), clientWidth / clientHeight, DirectX::XMConvertToRadians(45), 0.1F, 100.0F);

	if (!theEngine->initEngine(hInstance, hwnd, Engine::DIRECTX))
	{
		MessageBox(nullptr, TEXT("Failed to init Engine."), TEXT("Error"), MB_OK);
	}

	theEngine->setActiveCamera(camera);
}

void Game::tick(const float deltaTime)
{
	//camera.yaw(DirectX::XMConvertToRadians(1));
	theEngine->Update(deltaTime);
}

Game::~Game()
{
}
