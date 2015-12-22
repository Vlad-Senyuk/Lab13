#pragma once
#include <Windows.h>
#include <tchar.h>
#include <cstdlib>


HWND *nhmainwnd = new HWND[5];
char buffer[2];
static int f = 1;
LRESULT CALLBACK WndProc(HWND hmainWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	COLORREF colorText = RGB(150, 0, 0);
	//HWND *nhmainwnd = new HWND[5];
	
	switch (uMsg)
	{
	case WM_DESTROY:
		//MessageBox(NULL, L"Exit?", L"Window", MB_OK | MB_OKCANCEL);
		//PostQuitMessage(NULL);
		DestroyWindow(hmainWnd);
		break;
	case WM_NCLBUTTONDBLCLK: 
		SetWindowText(hmainWnd, L"NewMain");
		break;
	case WM_LBUTTONDOWN: 
		for (int i = 0; i < 5; i++) {
			_itoa_s(f, buffer, 10);
			nhmainwnd[i] = CreateWindow(L"Window", L"Window", WS_OVERLAPPEDWINDOW, 60+(i*10), 60+(i*10), 100, 100, NULL, NULL, NULL, NULL);
			SetWindowText(nhmainwnd[i], (LPCWSTR)buffer);
			f++;
			}
		for (int i = 0; i < 5; i++)
		{
			ShowWindow(nhmainwnd[i], 1);
			Sleep(1000);
		}
		break;

	case WM_KEYDOWN:
		for (int i = 5; i>-1; i--) {
			DestroyWindow(nhmainwnd[i]);
			Sleep(2000);
		}
		break;
	case WM_CLOSE:
	{
		MessageBox(NULL, L"Close?", L"Window", MB_OK | MB_OKCANCEL);
	case MB_OK: 
	{
		PostQuitMessage(NULL);
	}
	}
	break;

	default:
		return DefWindowProc(hmainWnd, uMsg, wParam, lParam);
	}

	return NULL;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpstr, int cmdshow)
{
	HWND hmainWnd;; // descriptor window
	MSG msg;
	TCHAR szClassName[] = L"Window";

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW;
	wc.lpszClassName = szClassName;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm= LoadIcon(NULL, IDI_WINLOGO);
	wc.lpszMenuName = NULL;
	wc.hInstance = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error!!!", L"Error", MB_OK);
	}
	hmainWnd = CreateWindow(szClassName, L"SubWindow",  WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, NULL, CW_USEDEFAULT, NULL, (HWND)NULL, NULL, NULL, NULL);

	if (!hmainWnd)
	{
		MessageBox(NULL, L"Error!!!", L"Error", MB_OK);
	}

	ShowWindow(hmainWnd, cmdshow);
	UpdateWindow(hmainWnd);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;

}
