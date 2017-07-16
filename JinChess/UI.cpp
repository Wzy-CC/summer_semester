#include <windows.h> 
#include "ChessBoard.h"

/************* ȫ�ֱ��� ****************/
HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
RECT rectBoundary;// 

// ��������

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

//�߽�
Position boundary;

//��ñ߽�����
pPosition GetBoundary()
{
	return &boundary;
}

// ���ñ߽�����
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS window;
	HWND hwnd;
	MSG msg;
	hinst = hinstance;
	int fGotMessage;

	//����
	window.style = CS_HREDRAW | CS_VREDRAW;            // ���������ʽ
	window.lpfnWndProc = MainWndProc;                  // ���ڴ�����
	window.cbClsExtra = 0;                             // no extra class memory 
	window.cbWndExtra = 0;                             // no extra window memory
	window.hInstance = hinstance;                      // ����ʵ�����
	window.hIcon = LoadIcon(NULL,IDI_APPLICATION);     // ������С��ͼ�꣺Ԥ����
	window.hCursor = LoadCursor(NULL,IDC_CROSS);	   // ���ڲ��ü�ͷ���		
	window.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	                                                   // ���ڱ�����ɫ					  
	window.lpszMenuName = NULL;	                       // ���ڵĲ˵�:��	
	window.lpszClassName =TEXT("MainWClass");          // ��������
	
	if (!RegisterClass(&window))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, TEXT("��������ʧ��"), TEXT("����"), MB_ICONERROR | MB_OK);
		return -1;
	}                                                  // ����ע��ɹ����������С�	
													   // Create the main window. 

	hwnd = CreateWindowA("MainWClass",			       // �����������������Ѿ�ע���˵Ĵ�����
	                  	 "Tic-Tactics",		           // title-bar string 
		                 WS_OVERLAPPEDWINDOW,	       // ���ڵ�style�������ʾΪtop-level window 
		                 CW_USEDEFAULT,			       // ����ˮƽλ��default horizontal POINT 
		                 CW_USEDEFAULT,			       // ���ڴ�ֱλ��default vertical POINT 
		                 CW_USEDEFAULT,			       // ���ڿ�� default width 
		                 CW_USEDEFAULT,			       // ���ڸ߶� default height 
		                 (HWND)NULL,			       // �����ھ�� no owner window 
		                 (HMENU)NULL,			       // ���ڲ˵��ľ�� use class menu 
		                 hinstance,				       // Ӧ�ó���ʵ����� handle to application instance 
		                 (LPVOID)NULL);			       // ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd)
	{
		MessageBox(NULL, TEXT("��������ʧ��"), TEXT("����"), MB_ICONERROR | MB_OK);
		return -1;                                     // ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
    }

	ShowWindow(hwnd, nCmdShow);	
	UpdateWindow(hwnd);    

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;                                 //��ȡ��Ϣ--������Ϣ--������Ϣ
}

//������Ϸ����������ô��ڴ�С
void ReSizeGameWnd(HWND hwnd)
{
	MoveWindow(hwnd,90,90,328,360, TRUE);
}

//���ں���
LONG CALLBACK MainWndProc(	HWND hwnd,                 // ���
	                        UINT msg,                  // ��Ϣ
	                        WPARAM wParam,             // ��Ϣ����
	                        LPARAM lParam )            // ��Ϣ����
{                                                      // ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	POINT pos;
	switch (msg)
	{  
	case WM_CREATE:
		CreateChessBoard(hwnd, Position_X,Position_Y);
		ReSizeGameWnd(hwnd);
		break;
	case WM_PAINT:
		pos.x = LOWORD(lParam);
		pos.y = HIWORD(lParam);
		//BackgroundPaint(hwnd);
	    GamePaint(hwnd,pos.x, pos.y);
		break;
	case WM_LBUTTONDOWN:
		pos.x = LOWORD(lParam);
		pos.y = HIWORD(lParam);
		StepMove(hwnd,pos.x,pos.y);	

		GamePaint(hwnd,pos.x,pos.y);
		JudgeChessBoard();
		break;
	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}


