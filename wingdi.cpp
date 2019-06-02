//compile using g++ wingdi.cpp -mwindows -lgdiplus -w -os
//To make sure the software runs properly please add a bitmap image file name "dd" in the same folder as the binary for this code.

#ifndef UNICODE
#define UNICODE
#endif

#define WIDTH 800
#define HEIGHT 600

#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

HDC myHdc;
PAINTSTRUCT ps;

Gdiplus::GdiplusStartupInput gdiInput;

ULONG_PTR gdiToken;

int h = 90;

HANDLE hThread, ghRunning;

DWORD WINAPI thread(LPVOID lpar);

void paint ( );

bool running = true;

LRESULT CALLBACK WindowProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain (HINSTANCE hinst, HINSTANCE hprev, LPSTR lpCmdline, int nCmdShow) {	

	wchar_t className[] = L"Windows.h";

	srand(38973489);

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst;
	wc.lpszClassName = className;
	wc.hIcon = (HICON) LoadImage (NULL, L"ts.ico", IMAGE_ICON, 128, 128, LR_LOADFROMFILE);
	// or, LoadIcon(NULL, IDI_ASTERISK);

	RegisterClass (&wc);

	bool answer = Gdiplus::GdiplusStartup(&gdiToken, &gdiInput, NULL);		

	HWND hwnd = CreateWindowEx (
		WS_EX_CLIENTEDGE,
		className, 
		L"Microsoft Watercolour 3.0 ", 
		WS_OVERLAPPEDWINDOW,	
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		hinst,
		NULL
	);

	if (hwnd == NULL) return 0;

	ShowWindow(hwnd, nCmdShow);

	MSG msg ;

	msg.message = WM_NULL;	

	myHdc = GetDC(hwnd);		

	hThread = CreateThread(NULL, 0, thread, NULL, 0, NULL);

	while (1) {

			
		if (PeekMessage(&msg, hwnd, 0,0, PM_REMOVE))
			DispatchMessage(&msg);			
		
		Sleep(50);
	
	}	

	ReleaseDC ( hwnd, myHdc);

	Gdiplus::GdiplusShutdown(gdiToken);

	return 0;

}

LRESULT CALLBACK WindowProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {	

	switch (msg) {

		case WM_DESTROY:
			PostQuitMessage(0);
			exit(0);

		case WM_PAINT:			
			break;	

	}

	return DefWindowProc (hwnd, msg, wparam, lparam);

}

DWORD WINAPI thread(LPVOID lpar) {
	
	paint();

}

void paint() {		

	Gdiplus::Graphics gf(myHdc);
	
	Gdiplus::Color pixelColor;

	Gdiplus::Bitmap bmp(L"dd.bmp");	

	int i,j,sz;

	for (int k = 0 ; k < 4000; k++) {				
		
		for (int l = 0 ; l < 10; l++) {
		
			i = rand() % WIDTH + 1;
			j = rand() % HEIGHT + 1;
			sz = rand() % 10 + 25;
			bmp.GetPixel(i,j, &pixelColor);			
			Gdiplus::SolidBrush brush(Gdiplus::Color(pixelColor.GetR(), pixelColor.GetG(), pixelColor.GetB(), sz));
			gf.FillEllipse(&brush, i % WIDTH, j % HEIGHT, sz, sz);
		}

		if (k == 3999)	 {

			k--;
			Sleep(1);

		}

	}
	
}


