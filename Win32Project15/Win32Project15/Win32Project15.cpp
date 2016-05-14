// Win32Project15.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Win32Project15.h"

#define MAX_LOADSTRING 100


WCHAR username[20], password[20], searchword[40];
int retine;
WCHAR ***mat;
int n = 0;


int binarySearch(int l, int r,WCHAR *srch)
{
	if (l>r)
		return -1;
	else
	{
		
		int m = (l + r) / 2;

		if (wcscmp(mat[m][0], srch) == 0)
		{
			return m;
		}

		if (wcscmp(srch, mat[m][0]) < 0)
			return  binarySearch(l, m-1,srch);
		else
			return  binarySearch(m+1, r,srch);
	}
}
int betweenSearch(int l, int r, WCHAR *srch)
{
		int m = (l + r) / 2;

		if (wcscmp(mat[m][0], srch) < 0 && wcscmp(mat[m+1][0], srch) > 0)
		{
			return m;
		}

		if (wcscmp(srch, mat[m][0]) < 0)
			return  betweenSearch(l, m - 1, srch);
		else
			return  betweenSearch(m + 1, r, srch);
}

void moveElements(int index,WCHAR *addwrd,WCHAR *addexplic)
{
	n++;
	mat[n-1] = (WCHAR**)malloc(sizeof(WCHAR*)* 2);
	for (int i = n-2; i >= index+1; i--)
	{
		mat[i + 1][0] = (WCHAR*)malloc(sizeof(WCHAR)*(wcslen(mat[i][0]) + 1));
		mat[i + 1][1] = (WCHAR*)malloc(sizeof(WCHAR)*(wcslen(mat[i][1]) + 1));

		wcscpy_s(mat[i + 1][0], wcslen(mat[i][0]) + 1, mat[i][0]);
		wcscpy_s(mat[i+ 1][1], wcslen(mat[i][1]) + 1, mat[i][1]);
	}
	free(mat[index + 1][0]);
	free(mat[index + 1][1]);
	mat[index + 1][0] = (WCHAR*)malloc(sizeof(WCHAR)*(wcslen(addwrd) + 1));
	mat[index + 1][1] = (WCHAR*)malloc(sizeof(WCHAR)*(wcslen(addexplic) + 1));
	wcscpy_s(mat[index+1][0], wcslen(addwrd) + 1, addwrd);
	wcscpy_s(mat[index+1][1], wcslen(addexplic) + 1, addexplic);
}


void crearemat()
{

	WCHAR sir[5000];
	//WCHAR *p;
	FILE *f = fopen("dictionar.txt", "r");
	fgetws(sir, 5000, f);
	WCHAR *x, *y;
	int test = 0;
	mat = NULL;
	for (int i = 0; i < 1000000; i++)
	{
		test++;
	}

	while (!feof(f))
	{
		mat = (WCHAR***)realloc(mat,sizeof(WCHAR**)*(n+1));
		mat[n] = NULL;
		mat[n] = (WCHAR**)realloc(mat[n], sizeof(WCHAR*)* 2);
		fgetws(sir, 5000, f);
		x = wcstok(LPWSTR(sir), L"*");
		y = wcstok(NULL, L"*");
		mat[n][0] = (WCHAR*)malloc(sizeof(WCHAR)*(1 + wcslen(x)));
		mat[n][1] = (WCHAR*)malloc(sizeof(WCHAR)*(1 + wcslen(y)));
		wcscpy_s(mat[n][0], wcslen(x) + 1, x);
		wcscpy_s(mat[n][1], wcslen(y) + 1, y);
		n++;
	}


}

void functiondel(int index)
{
	for (int i = index + 1; i < n; i++)
	{
		mat[i-1][0] = (WCHAR*)malloc(sizeof(WCHAR)*(wcslen(mat[i][0]) + 1));
		mat[i- 1][1] = (WCHAR*)malloc(sizeof(WCHAR)*(wcslen(mat[i][1]) + 1));

		wcscpy_s(mat[i- 1][0], wcslen(mat[i][0]) + 1, mat[i][0]);
		wcscpy_s(mat[i - 1][1], wcslen(mat[i][1]) + 1, mat[i][1]);
	}
	free(mat[n-1][0]);
	free(mat[n-1][1]);
	n--;

}

void final()
{
	FILE *g = fopen("dictionar.txt", "w");
	WCHAR exxit[5000];
	fwprintf(g, L"\n");
	for (int i = 0; i < n; i++)
	{
		wcscpy_s(exxit, wcslen(mat[i][0])+1, mat[i][0]);
		wcscat_s(exxit, L"*");
		wcscat_s(exxit, L" ");
		wcscat_s(exxit, mat[i][1]);
		wcscat_s(exxit, L"*");
		fwprintf(g, exxit);
		if (i!=n-1)
			fwprintf(g, L"\n");


	}
}




// Global Variables:
HINSTANCE hInst,hInstword,hInstdel;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Dial(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	addword(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    dellwords(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK editwords(HWND, UINT, WPARAM, LPARAM);
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT15, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT15));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT15));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT15);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
  
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
HWND editbox, search, edit, dell, add, exxit, hwndPB,hDlg;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//creare();
	///create data base of words

	switch (message)
	{
		
	case WM_CREATE:
	{
					  DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd,Dial);
					  
					  //CreateWindowEx(0L, L"STATIC", L"asdaS", NULL, 50, 50, 20, 80, hWnd, NULL,NULL, NULL);
					  CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", username,
						  WS_CHILD | WS_VISIBLE,
						  1050, 0, 70, 20, hWnd, NULL, NULL, NULL);


						editbox= CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",  ///textbox for searching word
						  WS_CHILD | WS_VISIBLE|WS_BORDER,
						  150, 100, 300, 50, hWnd, (HMENU)IDC_MAIN_EDIT, NULL, NULL);


					  search=CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Cauta", ////search button
						  WS_CHILD | WS_VISIBLE|WS_BORDER,
						  470, 105, 90, 40, hWnd, NULL, NULL, NULL);

					
						add = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Adauga", ////search button
						  WS_CHILD | WS_VISIBLE | WS_BORDER,
						  950, 105, 70, 40, hWnd, NULL, NULL, NULL);


					  edit = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Editeaza", ////search button
						  WS_CHILD | WS_VISIBLE | WS_BORDER,
						  950, 155, 70, 40, hWnd, NULL, NULL, NULL);


					  dell = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Sterge", ////search button
						  WS_CHILD | WS_VISIBLE | WS_BORDER,
						  950, 205, 70, 40, hWnd, NULL, NULL, NULL);

					  exxit = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Exit", ////search button
						  WS_CHILD | WS_VISIBLE | WS_BORDER,
						  950, 255, 70, 40, hWnd, NULL, NULL, NULL);


					  crearemat();//////create the list of words
		
					  

					 
	}
	case WM_COMMAND:
	{

					   wmId = LOWORD(wParam);
					   wmEvent = HIWORD(wParam);
					   // Parse the menu selections:
					   switch (wmId)
					   {
					   case IDM_ABOUT:
					   {
										 DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
										 break;
					   }
					   case IDM_EXIT:
					   {
										DestroyWindow(hWnd);
										break;
					   }

					   case IDM_MAXIMIZE:
					   {
											SetWindowPos(hWnd, HWND_TOPMOST, 1050, 500, 1000, 650, WM_MOVING);
											break;
					   }
					   case IDM_MEDIUM:
					   {
										  SetWindowPos(hWnd, HWND_TOPMOST, 950, 500, 700, 450, WM_MOVING);
										  break;
					   }
					   case IDM_MINIMIZE:
					   {
											SetWindowPos(hWnd, HWND_TOPMOST, 950, 500, 450, 300, WM_MOVING);
											break;
					   }
					   case IDM_CHANGE:
					   {
										  //CloseWindow(hWnd);
										  DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dial);
										  CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", username,
											  WS_CHILD | WS_VISIBLE,
											  1050, 0, 70, 20, hWnd, NULL, NULL, NULL);
										 

										  break;

					   }
					   case BN_CLICKED:
					   {
										  if (search == (HWND)lParam)
										  {

											  int index;
											  int get = GetWindowText(editbox, &searchword[0], 40);

											  index = binarySearch(0, n, searchword);
											  if (index != -1)
											  {

												  retine = index;
												  CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", mat[index][1],
													  WS_CHILD | WS_VISIBLE | WS_VSCROLL,
													  150, 200, 700, 200, hWnd, NULL, NULL, NULL);
												  
											  }
											  else
												  ::MessageBox(hWnd, L"Cuvantul nu exista in baza de date!", L"Warning", MB_OK);



										  }

										  if (add == (HWND)lParam&&wcscmp(username, L"admin") == 0)
										  {
											  DialogBox(hInstword, MAKEINTRESOURCE(IDD_ADD), hDlg, addword);
											  //::MessageBox(hWnd, username, L"add", MB_OK);
										  }
										  else
										  {
											  if (add == (HWND)lParam)
												  ::MessageBox(hWnd, L"Nu esti admin! Nu poti adauga cuvinte", L"Warning!", MB_OK);
										  }
										  if (edit == (HWND)lParam&&wcscmp(username, L"admin") == 0)
										  {
											  DialogBox(hInstword, MAKEINTRESOURCE(IDD_DIALOG3), hDlg, editwords);
											  CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"",
												  WS_CHILD | WS_VISIBLE,
												  150, 200, 700, 200, hWnd, NULL, NULL, NULL);
											  SetWindowText(GetDlgItem(hWnd, IDC_MAIN_EDIT), L"");
											 
										  }
										  else
										  {
											  if (edit == (HWND)lParam&&wcscmp(username, L"admin") != 0)
												  ::MessageBox(hWnd, L"Nu esti admin! Nu poti edita cuvinte!", L"Warning!", MB_OK);
	
										  }


										  if (dell == (HWND)lParam&&wcscmp(username, L"admin") != 0)
											  ::MessageBox(hWnd, L"Nu esti admin! Nu poti sterge cuvinte!", L"Warning!", MB_OK);
										  else
										  {
											  if (dell == (HWND)lParam&&wcscmp(username, L"admin") == 0)
											  {

												  DialogBox(hInstdel, MAKEINTRESOURCE(IDD_DIALOG2), hDlg, dellwords);
												  CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"",
													  WS_CHILD | WS_VISIBLE,
													  150, 200, 700, 200, hWnd, NULL, NULL, NULL);
												  SetWindowText(GetDlgItem(hWnd, IDC_MAIN_EDIT), L"");
											  }
										  }
					   
										  if (exxit == (HWND)lParam)
										  {
											  final();
											  DestroyWindow(hWnd);
										  }
										  break;
					   }
					   default:
						   return DefWindowProc(hWnd, message, wParam, lParam);
					   }
					   break;
	}
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
INT_PTR CALLBACK dellwords(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
						 
						  return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDNODEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOKDEL)
		{
			int get = GetWindowText(editbox, &searchword[0], 40);
			int index;
			index = binarySearch(0, n, searchword);
			if (index==-1)
				MessageBox(hDlg, L"Cuvantul nu a fost gasit in abza de date!", L"Warning!", MB_OK);
			else
			{
				functiondel(index);
				EndDialog(hDlg, LOWORD(wParam));
			}
		}
		break;
	}
	return (INT_PTR)FALSE;
}
HWND editwordbox,edittexplicbox,buton1ok,buton1no;
INT_PTR CALLBACK editwords(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	switch (message)
	{
	case WM_INITDIALOG:
	{
						  editwordbox = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", searchword,  ///textbox for searching word
							  WS_CHILD | WS_VISIBLE | WS_BORDER,
							  30, 30, 400, 50, hDlg, (HMENU)IDC_MAIN_EDIT, NULL, NULL);
						  edittexplicbox = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", mat[retine][1],  ///textbox for searching word
							  WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_LEFT | WS_HSCROLL | WM_SETTEXT | EM_SCROLLCARET,
							  30, 100, 400, 300, hDlg, (HMENU)IDC_MAIN_EDIT, NULL, NULL);

							  
						  break;

	}

		case WM_COMMAND:
	{
					   if (LOWORD(wParam) == IDOKEDITT)
					   {
						   WCHAR sir1[50], sir2[5000];
						   
						   GetWindowText(editwordbox, &sir1[0], 50);
						   GetWindowText(edittexplicbox, &sir2[0], 5000);
						   
						   functiondel(retine);
						   int variabila;
						   variabila = betweenSearch(0, n, sir1);

						   moveElements(variabila, sir1, sir2);
						  
						   EndDialog(hDlg, LOWORD(wParam));

					   }
					  
					   if (LOWORD(wParam) == IDNOEDITT)
					   {
						   
						   EndDialog(hDlg, LOWORD(wParam));
						   return (INT_PTR)TRUE;
					   }
					   break;
	}
	}
	return (INT_PTR)FALSE;

}


//login window


INT_PTR CALLBACK Dial(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{

	case WM_COMMAND:
	{
		  switch (LOWORD(wParam))
		  {
		  case IDCANCEL:
			{
							 PostQuitMessage(0);
							// EndDialog(hDlg, LOWORD(wParam));
							
			}
			break;

		  case IDLOGIN:
			{
				//WCHAR username[MAX_PATH], password[MAX_PATH];
				

				HWND usernameX = GetDlgItem(hDlg, IDC_USERNAME);
				HWND passwordX = GetDlgItem(hDlg, IDC_PASSWORD);

				GetWindowText(usernameX, LPWSTR(username), MAX_PATH);
				GetWindowText(passwordX, LPWSTR(password), MAX_PATH);

				//MessageBox(hDlg, username, L"", MB_OK);

				if (wcscmp(username, L"admin") == 0 && wcscmp(password, L"admin")!=0)
				{
					MessageBox(hDlg, L"Parola incorecta sau adauga alt username", L"Warning", MB_OK);
					
				}
				else
				if(wcscmp(username, L"admin") == 0 && wcscmp(password, L"admin") == 0)
				{
					MessageBox(hDlg, L"Hi Admin!", L"...", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
				}
				else
				{
					MessageBox(hDlg, L"Hi Guest",L"", MB_OK);
					EndDialog(hDlg, LOWORD(wParam));
				}
				
				

			}
			 

		  }



		
	}
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK addword(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{

	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {
					   case IDCANCEL:
					   {
										EndDialog(hDlg, LOWORD(lParam));
										

					   }
						   break;

					   case IDADD:
					   {

							WCHAR addwrd[30], addexplic[5000],*x;
							addwrd[0] ='\0';
							addexplic[0] = '\0';
							 HWND addwordX = GetDlgItem(hDlg, IDC_ENTERWORDS);
							 HWND addexplX = GetDlgItem(hDlg, IDC_ENTEREXPL);

							GetWindowText(addwordX, LPWSTR(addwrd), MAX_PATH);
							GetWindowText(addexplX, LPWSTR(addexplic), MAX_PATH);

							if (addwrd[0]==NULL||addexplic[0]==NULL)
								MessageBox(hDlg,L"Completati toate informatiile!",L"Warning!", MB_OK);
							else
							{
								//MessageBox(hDlg, addexplic,L"...", MB_OK);

								int index;
								index = binarySearch(0, n, addwrd);
								if (index != -1)
								{
									MessageBox(hDlg, L"Cuvantul acesta deja exista in baza de date!", L"Warning", MB_OK);
								}
								else
								{
									index = betweenSearch(0, n, addwrd);
									moveElements(index, addwrd, addexplic);

									MessageBox(hDlg, L"Cuvantul a fost adaugat!", L"Information", MB_OK);
									EndDialog(hDlg, LOWORD(lParam));
									///////////////////
								}
							}
							

							break;

					   }
						   


					   }

		}
	}
	return (INT_PTR)FALSE;
}

