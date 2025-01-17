// WindowsProject4.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject4.h"
#include<Windows.h>
#include<string>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR mainMessage[] = L"Hello World";

void createClass(WNDCLASSEX& wc, const HINSTANCE& hinst, const int r, const int g, const int b, const TCHAR Name[],
	WNDPROC proc) {

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = proc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = Name;
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(r, g, b));
	wc.hInstance = hinst;
}
HWND hMainWind[20];
LRESULT numSymb = 0;
int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	TCHAR szClassName[] = L"My class";


	MSG msg;
	WNDCLASSEX wc[1];

	createClass(wc[0], hInst, 0, 165, 80, szClassName, WndProc);
	for (WNDCLASSEX wclass : wc) {
		if (!RegisterClassEx(&wclass)) {
			MessageBox(NULL, (L"Не получилось зарегистрировать класс " + std::wstring(wc->lpszClassName)).c_str(), L"Ошибка", MB_OK);
			return NULL;
		}
	}
	INT cxScreen = GetSystemMetrics(SM_CXSCREEN);
	INT cyScreen = GetSystemMetrics(SM_CYSCREEN);
	hMainWind[0] = CreateWindow(szClassName,
		L"Полноценная оконная процедура",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		cxScreen/2,
		cyScreen/2,
		(HWND)NULL,
		NULL, // 
		HINSTANCE(hInst),
		NULL
	);
	hMainWind[1] = CreateWindow(
		(TCHAR*)(L"Edit"),
		NULL,
		WS_BORDER | WS_CHILD | WS_VISIBLE | NULL | NULL,
		10,
		10,
		200,
		20,
		hMainWind[0],
		NULL,
		hInst,
		NULL
	);
	hMainWind[2] = CreateWindow(
		(TCHAR*)(L"listbox"),
		NULL,
		WS_BORDER | WS_CHILD | WS_VISIBLE | LBS_NOTIFY | NULL,
		10,
		60,
		200,
		300,
		hMainWind[0],
		(HMENU)1001,
		hInst,
		NULL
	);
	hMainWind[3] = CreateWindow(
		(TCHAR*)(L"BUTTON"),
		(TCHAR*)(L"Font"),
		WS_CHILD | WS_VISIBLE,
		300,
		60,
		240,
		20,
		hMainWind[0],
		(HMENU)1002,
		hInst,
		NULL
	);
	hMainWind[4] = CreateWindow(
		(TCHAR*)(L"BUTTON"),
		(TCHAR*)(L"ADD"),
		WS_CHILD | WS_VISIBLE,
		300,
		80,
		240,
		20,
		hMainWind[0],
		(HMENU)1003,
		hInst,
		NULL
	);
	hMainWind[7] = CreateWindow(
		(TCHAR*)(L"BUTTON"),
		(TCHAR*)(L"CHANGE"),
		WS_CHILD | WS_VISIBLE,
		300,
		100,
		240,
		20,
		hMainWind[0],
		(HMENU)1004,
		hInst,
		NULL
	);
	hMainWind[8] = CreateWindow(
		(TCHAR*)(L"BUTTON"),
		(TCHAR*)(L"DELETE"),
		WS_CHILD | WS_VISIBLE,
		300,
		120,
		240,
		20,
		hMainWind[0],
		(HMENU)1005,
		hInst,
		NULL
	);
	hMainWind[9] = CreateWindow(
		(TCHAR*)(L"BUTTON"),
		(TCHAR*)(L"OK"),
		WS_CHILD | WS_VISIBLE,
		300,
		140,
		240,
		20,
		hMainWind[0],
		(HMENU)1006,
		hInst,
		NULL
	);
	hMainWind[10] = CreateWindow(
		(TCHAR*)(L"BUTTON"),
		(TCHAR*)(L"EXIT"),
		WS_CHILD | WS_VISIBLE,
		10,
		360,
		50,
		20,
		hMainWind[0],
		(HMENU)1007,
		hInst,
		NULL
	);
	hMainWind[5] = CreateWindow(
		(TCHAR*)(L"Edit"),
		NULL,
		WS_BORDER | WS_CHILD | WS_VISIBLE | NULL | NULL,
		340,
		10,
		200,
		20,
		hMainWind[0],
		(HMENU)10020,
		hInst,
		NULL
	);
	hMainWind[6] = CreateWindow(
		(TCHAR*)(L"Edit"),
		NULL,
		WS_BORDER | WS_CHILD | WS_VISIBLE | NULL | NULL,
		340,
		30,
		200,
		20,
		hMainWind[0],
		(HMENU)10021,
		hInst,
		NULL
	);
	
	for (int i = 0; i < 2; i++) {
		if (!hMainWind[i]) {

			MessageBox(NULL, (L"Не получилось создать окно " + std::to_wstring(i)).c_str(), L"Ошибка", MB_OK);
			return NULL;
		}
	}
	for (HWND hwd : hMainWind) {
		ShowWindow(hwd, nCmdShow);
		UpdateWindow(hwd);
	}
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	COLORREF colorText = RGB(255, 0, 0);
	INT wmid;
	INT eventId;
	INT xitem;
	INT xf = 0;
	INT yf = 0;
	LRESULT item;
	BOOL istp;
	HFONT hFontEa;


	switch (uMsg) {
	case WM_PAINT:
		hDC = BeginPaint(hMainWind[0], &ps);
		SetBkColor(hDC, RGB(0, 165, 80));
		TextOut(hDC, 300, 10, L"X", strlen("X"));
		TextOut(hDC, 300, 30, L"Y", strlen("Y"));
		EndPaint(hMainWind[0], &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	case WM_COMMAND:

	
		WCHAR cBuffer[2222];
		wmid = LOWORD(wParam);
		eventId = HIWORD(wParam);

		switch (wmid)
		{

		case 1001:
			if (eventId == LBN_DBLCLK) {
				INT nitem = SendMessage(hMainWind[2], LB_GETCARETINDEX, (WPARAM)0, (LPARAM)0);
				LPARAM lp = SendMessage(hMainWind[2], LB_GETTEXT, (WPARAM)nitem, (LPARAM)cBuffer);
				SendMessage(hMainWind[1], WM_SETTEXT, (WPARAM)0, (LPARAM)cBuffer);
			}
			break;

		case 1002:
		
			xf = GetDlgItemInt(hWnd,10020,&istp,false);
			if (istp) {
				yf = GetDlgItemInt(hWnd, 10021, &istp, false);
				if (istp) {
					hFontEa = CreateFont(xf, yf, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
					SendMessage(hMainWind[1], WM_SETFONT, WPARAM(hFontEa), TRUE);
					SendMessage(hMainWind[2], WM_SETFONT, WPARAM(hFontEa), TRUE);
				}
			}
				
			
			break;

		case 1003:
			numSymb = SendMessage(hMainWind[1], WM_GETTEXTLENGTH, 0, 0) + 1;
			SendMessage(hMainWind[1], WM_GETTEXT, numSymb, LPARAM(cBuffer));
			item=SendMessage(hMainWind[2],LB_ADDSTRING,(WPARAM)0,LPARAM(cBuffer));
			break;
		case 1004:
			xitem = SendMessage(hMainWind[2], LB_GETCARETINDEX, (WPARAM)0, (LPARAM)0);
			numSymb = SendMessage(hMainWind[1], WM_GETTEXTLENGTH, 0, 0) + 1;
			SendMessage(hMainWind[1], WM_GETTEXT, numSymb, LPARAM(cBuffer));
			SendMessage(hMainWind[2], LB_DELETESTRING, (WPARAM)xitem, (LPARAM)0);
			SendMessage(hMainWind[2],LB_INSERTSTRING,(WPARAM)xitem,LPARAM(cBuffer));
			break;
		case 1005:
			xitem = SendMessage(hMainWind[2], LB_GETCARETINDEX, (WPARAM)0, (LPARAM)0);
			SendMessage(hMainWind[2],LB_DELETESTRING,(WPARAM)xitem,(LPARAM)0);
			break;
		case 1007:
			SendMessage(hMainWind[0],WM_CLOSE,(WPARAM)0,LPARAM(0));
			break;
	
		}
		
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}
