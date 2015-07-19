#pragma once
#include "Engine.h"
class Game
{
public:
	Game();
	explicit Game(HWND hwnd, HINSTANCE hInstance, Engine* engine);
	void tick(const float DeltaTime);
	~Game();
private:
	Engine* theEngine;
	Camera camera;
};

