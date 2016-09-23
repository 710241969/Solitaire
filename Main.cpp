#include"CardCtrl.h"

CardCtrl g_oCardCtrl;
HINSTANCE g_hIns;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT pt;

	switch (message)
	{
	case WM_CREATE:
		g_oCardCtrl.InitValue(hWnd, g_hIns);
		g_oCardCtrl.GameInit();
		break;

	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		g_oCardCtrl.OnPaintWnd();
		break;

	case WM_KEYDOWN:
		break;

	case WM_LBUTTONDBLCLK:
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		break;

	case WM_LBUTTONDOWN:
		SetCapture(hWnd);//����괦�ڴ��ڷ�Χ֮��ʱ����������ꡣ
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		g_oCardCtrl.OnMouseLDown(pt);
		break;

	case WM_LBUTTONUP:
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		g_oCardCtrl.OnMouseLUp(pt);
		ReleaseCapture();
		break;

	case WM_MOUSEMOVE:
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		g_oCardCtrl.OnMouseMove(pt);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM1_NG:
			if (MessageBox(hWnd, L"ȷ������Ϸ��",
				L"��ʾ", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK)
			{
				g_oCardCtrl.DeleteCardsOb();
				g_oCardCtrl.InitValue(hWnd, g_hIns);
				g_oCardCtrl.GameInit();
				ValidateRect(hWnd, NULL);
				g_oCardCtrl.OnPaintWnd();
			}
			break;
		}
		/*{
		case 1:
		g_oCardCtrl.OnLeftCardButtonClick();
		break;

		default:
		break;
		}*/



		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	g_hIns = hInstance;

	//������WNDCLASSEX�����
	WNDCLASSEX wndClass =
	{
		wndClass.cbSize = sizeof(WNDCLASSEX),
		wndClass.style = CS_DBLCLKS,// | CS_HREDRAW | CS_VREDRAW,
		wndClass.lpfnWndProc = WndProc,
		wndClass.cbClsExtra = 0,
		wndClass.cbWndExtra = 0,
		wndClass.hInstance = hInstance,
		wndClass.hIcon = (HICON)LoadImage(hInstance,
		MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE),
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW),
		wndClass.hbrBackground = NULL,//(HBRUSH)GetStockObject(GRAY_BRUSH),
		wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1),
		wndClass.lpszClassName = L"MySoftware",
	};

	//������WNDCLASSEX��ע��
	if (!RegisterClassEx(&wndClass))
		return -1;

	//���ڵĴ���
	HWND hWnd = CreateWindow(L"MySoftware",
		L"Solitaire",
		WS_CAPTION | WS_SYSMENU | //WS_THICKFRAME | 
		WS_MINIMIZEBOX,//| WS_MAXIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);

	//���ڵ���ʾ
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	//��Ϣ��ϵ����
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}