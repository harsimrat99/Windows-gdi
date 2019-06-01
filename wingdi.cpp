//compile using g++ wingdi.cpp -mwindows -lgdiplus -w
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

HDC myHdc;
PAINTSTRUCT ps;

Gdiplus::GdiplusStartupInput gdiInput;
ULONG_PTR gdiToken;

void paint ( Gdiplus::Bitmap *,  Gdiplus::Graphics * gf, Gdiplus::Color * pixelColor);

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
	Gdiplus::Bitmap bmp(L"dd.bmp");
	
	

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

	MSG msg = {};

	myHdc = BeginPaint(hwnd, &ps);

	Gdiplus::Graphics gf(myHdc);

	Gdiplus::Color pixelColor;

	while (GetMessage(&msg, NULL, 0, 0)) {
			
		TranslateMessage(&msg);		

		DispatchMessage(&msg);
		
		paint(&bmp, &gf, &pixelColor);	
			
	}

	EndPaint(hwnd, &ps);

	Gdiplus::GdiplusShutdown(gdiToken);
	return 0;

}

LRESULT CALLBACK WindowProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {	

	switch (msg) {

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:		
			break;		

	}

	return DefWindowProc (hwnd, msg, wparam, lparam);

}


void paint(Gdiplus::Bitmap * bmp, Gdiplus::Graphics * gf, Gdiplus::Color * pixelColor) {	

	for (int g = 0; g < 40000; g++) {				

		long i = rand() % WIDTH + 1;
		long j = rand() % HEIGHT + 1;
		int sz = rand() % 10 + 25;
		bmp->GetPixel(i,j,pixelColor);			
		Gdiplus::SolidBrush brush(Gdiplus::Color(pixelColor->GetR(), pixelColor->GetG(), pixelColor->GetB(), sz));
		gf->FillEllipse(&brush, i % WIDTH, j % HEIGHT, sz, sz);					
	}
	
}




