#include <windows.h> 
#include "ChessBoard.h"

/************* 全局变量 ****************/
HINSTANCE hinst; /// HINSTANCE是用来表示程序运行实例的句柄，某些API函数会使用到这个变量。
RECT rectBoundary;// 

// 函数声明

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

//边界
Position boundary;

//获得边界坐标
pPosition GetBoundary()
{
	return &boundary;
}

// 设置边界坐标
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

	//窗口
	window.style = CS_HREDRAW | CS_VREDRAW;            // 窗口类的样式
	window.lpfnWndProc = MainWndProc;                  // 窗口处理函数
	window.cbClsExtra = 0;                             // no extra class memory 
	window.cbWndExtra = 0;                             // no extra window memory
	window.hInstance = hinstance;                      // 窗口实例句柄
	window.hIcon = LoadIcon(NULL,IDI_APPLICATION);     // 窗口最小化图标：预定义
	window.hCursor = LoadCursor(NULL,IDC_CROSS);	   // 窗口采用箭头光标		
	window.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	                                                   // 窗口背景颜色					  
	window.lpszMenuName = NULL;	                       // 窗口的菜单:无	
	window.lpszClassName =TEXT("MainWClass");          // 窗口类名
	
	if (!RegisterClass(&window))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, TEXT("创建窗口失败"), TEXT("错误！"), MB_ICONERROR | MB_OK);
		return -1;
	}                                                  // 窗口注册成功，继续运行。	
													   // Create the main window. 

	hwnd = CreateWindowA("MainWClass",			       // 窗口类名，必须是已经注册了的窗口类
	                  	 "Tic-Tactics",		           // title-bar string 
		                 WS_OVERLAPPEDWINDOW,	       // 窗口的style，这个表示为top-level window 
		                 CW_USEDEFAULT,			       // 窗口水平位置default horizontal POINT 
		                 CW_USEDEFAULT,			       // 窗口垂直位置default vertical POINT 
		                 CW_USEDEFAULT,			       // 窗口宽度 default width 
		                 CW_USEDEFAULT,			       // 窗口高度 default height 
		                 (HWND)NULL,			       // 父窗口句柄 no owner window 
		                 (HMENU)NULL,			       // 窗口菜单的句柄 use class menu 
		                 hinstance,				       // 应用程序实例句柄 handle to application instance 
		                 (LPVOID)NULL);			       // 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		MessageBox(NULL, TEXT("创建窗口失败"), TEXT("错误！"), MB_ICONERROR | MB_OK);
		return -1;                                     // 窗口创建失败，消息框提示，并退出。
    }

	ShowWindow(hwnd, nCmdShow);	
	UpdateWindow(hwnd);    

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;                                 //获取消息--翻译消息--分配消息
}

//根据游戏坐标界面设置窗口大小
void ReSizeGameWnd(HWND hwnd)
{
	MoveWindow(hwnd,90,90,328,360, TRUE);
}

//窗口函数
LONG CALLBACK MainWndProc(	HWND hwnd,                 // 句柄
	                        UINT msg,                  // 消息
	                        WPARAM wParam,             // 消息参数
	                        LPARAM lParam )            // 消息参数
{                                                      // 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
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


