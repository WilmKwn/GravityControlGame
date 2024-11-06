#include "Window.h"

Window::Window() {}

Window::~Window() {}

bool Window::LB_click = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		Window::SetLBClickValue(true);
		break;
	case WM_LBUTTONUP:
		Window::SetLBClickValue(false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void Window::Init(HINSTANCE hInstance, int x, int y, int width, int height)
{
	WNDCLASSEX wcex = { 0 };
	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"o";
	wcex.lpszMenuName = NULL;
	RegisterClassEx(&wcex);

	m_handle = CreateWindowEx(NULL, L"o", L"ok", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, width, height, NULL, NULL, hInstance, NULL);
}

HWND Window::GetHandle()
{
	return m_handle;
}