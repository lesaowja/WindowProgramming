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

int PointTotalNum = 30;

struct EllipsePosition
{
	int x;
	int y;
	bool check = false;

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

struct RemovePoint
{
	int left;
	int top;
	int right;
	int bottom;

};
RemovePoint Rm[100];


TCHAR PointString[256]; 
TCHAR TotalNumString[256];
TCHAR BallNum[100];

TCHAR buf[128];
bool ResetGameBut = false;
void ResetGame(HWND hWnd)
{
	ResetGameBut = true;
	count = 0;
	Player.Point = 0;
}




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
		YSize = rect.bottom - (SIZE*6);
		hWndMain = hWnd; 
		 

		CreateWindow(TEXT("button"), TEXT("10개 설정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, XSize - 50, 0, 100, 25, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("30개 설정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, XSize - 50, 30, 100, 25, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("50개 설정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, XSize - 50, 60, 100, 25, hWnd, (HMENU)2, g_hInst, NULL);
		


		CreateWindow(TEXT("button"), TEXT("속도 느림."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, XSize - 150, 0, 100, 25, hWnd, (HMENU)3, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("속도 중간."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, XSize - 150, 30, 100, 25, hWnd, (HMENU)4, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("속도 빠름."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, XSize - 150, 60, 100, 25, hWnd, (HMENU)5, g_hInst, NULL);
		return 0; 
	
	case WM_TIMER:

		InvalidateRect(hWnd, NULL, TRUE);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);  
		wsprintf(TotalNumString, TEXT("공의 총 갯수: %d"), PointTotalNum);
		TextOut(hdc, 30, 20, TotalNumString, lstrlen(TotalNumString));

		wsprintf(PointString, TEXT("Your Point: %d"), Player.Point);
		TextOut(hdc, 30, 50, PointString, lstrlen(PointString));

		wsprintf(BallNum, TEXT("%d 번째 공"), count);
		TextOut(hdc, XSize/2, 20, BallNum, lstrlen(BallNum));

		Rm[count].top = CircleButton.x - SIZE;
		Rm[count].left = CircleButton.y - SIZE;
		Rm[count].right = CircleButton.x + SIZE;
		Rm[count].bottom = CircleButton.y + SIZE;
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		SelectObject(hdc, hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, Rm[count].top, Rm[count].left, Rm[count].right, Rm[count].bottom);
		  
		 
		if (count >= PointTotalNum &&!ResetGameBut)
		{
			ResetGameBut = true;
			wsprintf(buf, TEXT("재도전 하시겠습니까?"));
			if (MessageBox(hWnd, buf, TEXT("Game Over."), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			ResetGame(hWnd);
			else
			{ 
				SendMessage(hWnd, WM_CLOSE, NULL, NULL);
			}
			return 0;  
		}
		else if(count < PointTotalNum)
		{

			count++;
			CircleButton.x = rand() % XSize + SIZE;
			CircleButton.y = rand() % YSize + (SIZE * 4);
			CircleButton.check = false;
			hBrush = CreateSolidBrush(RGB(170, 110, 255));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, CircleButton.x - SIZE, CircleButton.y - SIZE, CircleButton.x + SIZE, CircleButton.y + SIZE);

			
			EndPaint(hWnd, &ps);
		}
		
		return 0;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case 0:
			PointTotalNum = 10;
			break;

		case 1:
			PointTotalNum = 30;
			break;

		case 2:
			PointTotalNum = 50;
			break;


		case 3:
			SetTimer(hWnd, 1, 1000, NULL);
			break;

		case 4:
			SetTimer(hWnd, 1, 750, NULL);
			break;

		case 5:
			SetTimer(hWnd, 1, 550, NULL);
			break;
		default:
			break;
		}
		return 0;
	
	case WM_LBUTTONDOWN:  // 마우스를 눌렀을때 

		hdc = GetDC(hWnd); 

		xPosition= LOWORD(lParam);
		yPosition = HIWORD(lParam); 
		if (xPosition <= CircleButton.x + 30 && xPosition >= CircleButton.x - SIZE && yPosition <= CircleButton.y + SIZE && yPosition >= CircleButton.y - SIZE && !CircleButton.check)
		{ 
			Player.Point++;
			CircleButton.check = true;
		}  

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
