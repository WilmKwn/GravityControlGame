#include "Window.h"
#include "Graphics.h"

#include "Game.h"

#include "MenuScreen.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstacne, LPSTR nCmdLine, int nCmdShow)
{
	Window* window = new Window();
	window->Init(hInstance, 0, 0, 800, 600);

	Graphics* graphics = new Graphics();
	graphics->Init(window->GetHandle());

	MenuScreen* menuScreen = new MenuScreen(graphics, window->GetHandle());
	menuScreen->Init();

	Game* level[10];

	int g_totalScore = 0;
	int g_lives = 3;
	bool g_menuScreen = true;

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		graphics->Begin();
		graphics->ClearScreen(D2D1::ColorF(0.0f, 0.0f, 0.0f));

		if (menuScreen->GetPlayButtonPressed()) {
			g_totalScore = 0;
			g_lives = 3;
			g_menuScreen = false;
			for (int i = 0; i < 10; i++) {
				level[i] = new Game(graphics, window->GetHandle());
				level[i]->Init(1 + (i / 3), 6 + (i / 3), i + 1);
			}
		}
		if (g_menuScreen) {
			menuScreen->Run();
		}
		else if (!g_menuScreen) {
			menuScreen->SetPlayButtonPressed(false);
			if (!level[0]->GetLevelOver()) {
				level[0]->Run(g_totalScore, g_lives);
				g_lives = level[0]->GetLives();
			}
			else {
				if (!level[0]->GetAddScore()) {
					g_totalScore += level[0]->GetTotalScore();
					level[0]->SetAddScore(true);
				}
			}
			for (int i = 0; i < 9; i++) {
				if (level[i]->GetReturnMenuScreen()) {
					g_menuScreen = true;
				}
				if (!level[i + 1]->GetLevelOver() && level[i]->GetLevelOver()) {
					level[i + 1]->Run(g_totalScore, g_lives);
					g_lives = level[i + 1]->GetLives();
				}
				else if (level[i + 1]->GetLevelOver()) {
					if (!level[i + 1]->GetAddScore()) {
						g_totalScore += level[i + 1]->GetTotalScore();
						level[i + 1]->SetAddScore(true);
					}
				}
			}
		}

		graphics->End();
	}
	return (int)msg.wParam;
}