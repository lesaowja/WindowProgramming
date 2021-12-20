#include <windows.h>
#include<time.h>
#include<stdlib.h>
#define SIZE 30


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Aim Hero");
 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

//Thread Func
DWORD WINAPI ThreadFunc(LPVOID temp)
{ 
	return 0;
} 

struct EllipsePosition
{
	int x;
	int y;
};
EllipsePosition CircleButton;

struct PlayerPoint
{
	int Point; 
};
PlayerPoint Player;
int yPosition;
int xPosition;

int count;

int XSize;
int YSize;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static RECT rect;
	PAINTSTRUCT ps;
	HPEN hPen;
	HBRUSH hBrush;
	switch (iMessage) {
	case WM_CREATE: 

		srand(time(NULL)); 
		SetTimer(hWnd, 1, 1000, NULL);
		GetClientRect(hWnd, &rect);
		XSize = rect.right-60;
		YSize = rect.bottom - (SIZE*5);
		hWndMain = hWnd;
		return 0;

	case WM_TIMER:  
		 
		hdc = GetDC(hWnd);
		count++;
		CircleButton.x = rand() % XSize+ SIZE;
		CircleButton.y = rand() % YSize + (SIZE*3);
		hBrush = CreateSolidBrush(RGB(170, 110, 255));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, CircleButton.x - SIZE, CircleButton.y - SIZE, CircleButton.x + SIZE, CircleButton.y + SIZE); 
		return 0;
 
	case WM_LBUTTONDOWN:  // 마우스를 눌렀을때 

		hdc = GetDC(hWnd); 
		xPosition= LOWORD(lParam);
		yPosition = HIWORD(lParam); 
		if(xPosition <= CircleButton.x+30 && xPosition >= CircleButton.x - SIZE && yPosition <= CircleButton.y + SIZE && yPosition >= CircleButton.y - SIZE)
		Player.Point++;
		 
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
