#pragma once
#include <Windows.h>

#define status int 

/************* 宏定义 ****************/

//定义每个棋盘格（checker）的状态
#define CheckerNull	0
#define Player1		1
#define Player2 	2

//定义每个格子的的边长
#define ChessLengh  92 // 92个像素

//定义背景参数
#define BITMAP_FILE_BK	   "chess.bmp"
#define TRANS_BK_COLOR		RGB(255,0,0)

//定义棋子
#define ChessP1	   "ChessP1.bmp"
#define ChessP2	   "ChessP2.bmp"

//定义输赢
#define Player1Win	10
#define Player2Win 	20
#define DrawnGame 	30
#define NoWinner 	40  //GO ON

// 用来绘图的颜色
#define COLOR_BOUNDARY	RGB(139, 134, 130)

// 游戏的参数的设置 
#define Position_X		311	// 游戏界面大小
#define Position_Y		313	// 游戏界面大小

// 画图时使用棋盘像素点个数。
#define CELL_PIXEL		5

// 游戏坐标
typedef struct _Position
{
	short x;
	short y;
}Position, *pPosition;

void BackgroundPaint(HWND hwnd);

// 获得边界坐标
pPosition GetBoundary();

//初始化棋盘（ChessBoard）
void CreateChessBoard(HWND,int,int);

//销毁棋盘（ChessBoard）
void DistroyChessBoard();

//判断坐标，改变棋盘的状态(下棋过程)
int StepMove(HWND,LONG,LONG);

//判断棋盘当前的状态(1获胜，2获胜，无赢家)
status JudgeChessBoard();

//打印图像
void GamePaint(HWND,LONG,LONG);


