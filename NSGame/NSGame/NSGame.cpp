// NSGame.cpp : This is where the program starts
//
#include "stdafx.h"
#include "NSGame.h"
#include "Game.h"

#define MAX_LOADSTRING 100

// Global Variables:
int game_state = GAME_INIT;
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int, HWND &hWnd);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// msg is used for windows to communicate with the window we create
	MSG msg;
	// no fucking idea
	HACCEL hAccelTable;

	// sets global variables
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NSGAME, szWindowClass, MAX_LOADSTRING);

	// Each window is contained in a window object this function creates it and 
	// registers it with windows
	MyRegisterClass(hInstance);
	
	// Game object
	Game GAME;
	// Window handle
	HWND hWnd;

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow, hWnd ))
	{
		return FALSE;
	}
	
	// Some wizardry pokery
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NSGAME));

	PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );

	// Main message loop:
	while (msg.message!=WM_QUIT)
	{
		// Windows checks msg from system makes sure nothing is on fire etc, 
		// this only does stuff if our program is not running now
		if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// it hands the message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// Main game loop!!
			switch(game_state)
			{
				case GAME_INIT:
				{
					// Here we could load a config file to initialize the game a different way

					// Load engine, graphics, sound, input, world
					if(! GAME.initialise(hWnd,hInst) )
					{
						GAME.error("Uncaught game initialization failure.",__FILE__, __LINE__);
					}
					else
					{
						game_state = GAME_MENU;
					}
					break;
				}
				case GAME_MENU:
				{
					if(! GAME.menu(hWnd) )
					{
						GAME.error("Uncaught game menu failure.",__FILE__, __LINE__);
					}
					else
					{
						game_state = GAME.getGameState();
					}
					break;

				}
			    case GAME_LOAD:
				{
					if(! GAME.load() )
					{
						GAME.error("Uncaught game load failure.",__FILE__, __LINE__);
					}
					break;
				}
			    case GAME_RUN:
				{
					if(! GAME.run() )
					{
						GAME.error("Uncaught game run failure.",__FILE__, __LINE__);
					}
					else
					{
						game_state = GAME.getGameState();
					}
					break;
				}
				case GAME_RESTART:
				{
					game_state = GAME.menu(hWnd);
					break;
				}
				case GAME_EXIT:
				{
					GAME.exit();
					msg.message=WM_DESTROY;
					SendMessage(hWnd,WM_DESTROY,NULL,NULL);
					break;
				}
				default: break;
			}
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//  
//	This function creates a WNDCLASSEX object that holds all the window data
//  we don't need to worry about it but this data is basiclly what makes our window.
//  It gets registered and windows looks after it!
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NSGAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_NSGAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hbrBackground	= (HBRUSH)COLOR_WINDOW;

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//	 This actually creates the window using the class data above, it's all
//   refered to by the HINSTANCE hInstance variable
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND &hWnd)
{
   //HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   // if window mode
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   // if fullscreen
   /*hWnd = CreateWindow(szWindowClass, szTitle, WS_EX_TOPMOST | WS_POPUP,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);*/

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
