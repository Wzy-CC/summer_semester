#pragma once
#include <Windows.h>

#define status int 

/************* �궨�� ****************/

//����ÿ�����̸�checker����״̬
#define CheckerNull	0
#define Player1		1
#define Player2 	2

//����ÿ�����ӵĵı߳�
#define ChessLengh  92 // 92������

//���屳������
#define BITMAP_FILE_BK	   "chess.bmp"
#define TRANS_BK_COLOR		RGB(255,0,0)

//��������
#define ChessP1	   "ChessP1.bmp"
#define ChessP2	   "ChessP2.bmp"

//������Ӯ
#define Player1Win	10
#define Player2Win 	20
#define DrawnGame 	30
#define NoWinner 	40  //GO ON

// ������ͼ����ɫ
#define COLOR_BOUNDARY	RGB(139, 134, 130)

// ��Ϸ�Ĳ��������� 
#define Position_X		311	// ��Ϸ�����С
#define Position_Y		313	// ��Ϸ�����С

// ��ͼʱʹ���������ص������
#define CELL_PIXEL		5

// ��Ϸ����
typedef struct _Position
{
	short x;
	short y;
}Position, *pPosition;

void BackgroundPaint(HWND hwnd);

// ��ñ߽�����
pPosition GetBoundary();

//��ʼ�����̣�ChessBoard��
void CreateChessBoard(HWND,int,int);

//�������̣�ChessBoard��
void DistroyChessBoard();

//�ж����꣬�ı����̵�״̬(�������)
int StepMove(HWND,LONG,LONG);

//�ж����̵�ǰ��״̬(1��ʤ��2��ʤ����Ӯ��)
status JudgeChessBoard();

//��ӡͼ��
void GamePaint(HWND,LONG,LONG);


