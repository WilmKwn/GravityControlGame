#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;

	writeFactory = NULL;
	textFormat = NULL;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();

	if (writeFactory) writeFactory->Release();
	if (textFormat) textFormat->Release();
}

void Graphics::Init(HWND windowHandle)
{
	RECT rect;
	GetClientRect(windowHandle, &rect);
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &renderTarget);

	renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &brush);

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&writeFactory));
}

void Graphics::Begin()
{
	renderTarget->BeginDraw();
}

void Graphics::End()
{
	renderTarget->EndDraw();
}

void Graphics::ClearScreen(D2D1_COLOR_F color)
{
	renderTarget->Clear(color);
}

void Graphics::DrawRect(RECT rect, D2D1_COLOR_F color)
{
	renderTarget->CreateSolidColorBrush(color, &brush);
	renderTarget->DrawRectangle(D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom), brush, 2.0f, 0);
}

void Graphics::DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, D2D1_COLOR_F color)
{
	renderTarget->CreateSolidColorBrush(color, &brush);
	renderTarget->DrawLine(p1, p2, brush, 2.0f, 0);
}

void Graphics::DrawTexts(const WCHAR* text, float size, int length, int x, int y, D2D1_COLOR_F color)
{
	renderTarget->CreateSolidColorBrush(color, &brush);

	writeFactory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_THIN, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", &textFormat);

	renderTarget->DrawText(text, sizeof(text) + length, textFormat, D2D1::RectF(x, y, x + 1000, y + 100), brush);
}