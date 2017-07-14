/************** ͷ�ļ� ****************/
#include <Windows.h>
#include "ChessBoard.h"

//#pragma comment (lib, "Winmm.lib")

/************* ȫ�ֱ��� ****************/
status ChessBoard[3][3];

HBITMAP hbmpBackground;
HDC  hdc, hdcMem, hdcMem2;

HBITMAP HBoard;                              BITMAP Board;
HBITMAP HP1;                                 BITMAP P1;
HBITMAP HP2;                                 BITMAP P2;

/**************��������****************/
//��ʼ������
void CreateChessBoard(HWND hwnd, int boundary_x, int boundary_y)
{
	int ChessBoard[3][3] = { CheckerNull };

	// ����λͼ
	hbmpBackground = (HBITMAP)LoadImageA(NULL, BITMAP_FILE_BK, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmpBackground == NULL)
	{
		MessageBoxA(hwnd,"not find","ERROR",MB_OK|MB_ICONERROR);
		ExitProcess(0);
	}
	HP1 = (HBITMAP)LoadImageA(NULL, ChessP1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (HP1 == NULL)
	{
		MessageBoxA(hwnd, "not find", "ERROR", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	HP2 = (HBITMAP)LoadImageA(NULL, ChessP2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (HP2 == NULL)
	{
		MessageBoxA(hwnd, "not find", "ERROR", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
}

//�ж���Ӯ
status JudgeChessBoard()
{
	if (ChessBoard[0][0] * ChessBoard[0][1] * ChessBoard[0][2] * ChessBoard[1][0] * ChessBoard[1][1] * ChessBoard[1][2] * ChessBoard[2][0] * ChessBoard[2][1] * ChessBoard[2][2] == 0)
		//��������ϻ���λ�ÿ�����
	{
		if (ChessBoard[0][0] == ChessBoard[1][1] && ChessBoard[1][1] == ChessBoard[2][2] && ChessBoard[2][2] == 1
			|| ChessBoard[0][2] == ChessBoard[1][1] && ChessBoard[1][1] == ChessBoard[2][0] && ChessBoard[2][0] == 1
			|| ChessBoard[0][0] == ChessBoard[0][1] && ChessBoard[0][1] == ChessBoard[0][2] && ChessBoard[0][2] == 1
			|| ChessBoard[1][0] == ChessBoard[1][1] && ChessBoard[1][1] == ChessBoard[1][2] && ChessBoard[1][2] == 1
			|| ChessBoard[2][0] == ChessBoard[2][1] && ChessBoard[2][1] == ChessBoard[2][2] && ChessBoard[2][2] == 1
			|| ChessBoard[0][0] == ChessBoard[1][0] && ChessBoard[1][0] == ChessBoard[2][0] && ChessBoard[2][0] == 1
			|| ChessBoard[0][1] == ChessBoard[1][1] && ChessBoard[1][1] == ChessBoard[2][1] && ChessBoard[2][1] == 1
			|| ChessBoard[0][2] == ChessBoard[1][2] && ChessBoard[1][2] == ChessBoard[2][2] && ChessBoard[2][2] == 1)
		{
			MessageBoxA(NULL, "��Ϸ����", "Tic!", MB_OKCANCEL);
			return Player1Win;
		}
		if (ChessBoard[0][0] == ChessBoard[1][1] && ChessBoard[1][1] == ChessBoard[2][2] && ChessBoard[2][2] == 2
			|| ChessBoard[0][2] == ChessBoard[1][1] && ChessBoard[1][1] == ChessBoard[2][0] && ChessBoard[2][0] == 2
			|| ChessBoard[0][0] == ChessBoard[0][1] && ChessBoard[0][1] == ChessBoard[0][2] && ChessBoard[0][2] == 2
			|| ChessBoard[1][0] == ChessBoard[1][1] && ChessBoard[1][1] == ChessBoard[1][2] && ChessBoard[1][2] == 2
			|| ChessBoard[2][0] == ChessBoard[2][1] && ChessBoard[2][1] == ChessBoard[2][2] && ChessBoard[2][2] == 2
			|| ChessBoard[0][0] == ChessBoard[1][0] && ChessBoard[1][0] == ChessBoard[2][0] && ChessBoard[2][0] == 2
			|| ChessBoard[0][1] == ChessBoard[1][1] && ChessBoard[1][1] == ChessBoard[2][1] && ChessBoard[2][1] == 2
			|| ChessBoard[0][2] == ChessBoard[1][2] && ChessBoard[1][2] == ChessBoard[2][2] && ChessBoard[2][2] == 2)
		{
			MessageBoxA(NULL, "��Ϸ����", "Tic!", MB_OKCANCEL);
			return Player2Win;
		}
		else
			return NoWinner; // GO ON
	}
	if (ChessBoard[0][0] * ChessBoard[0][1] * ChessBoard[0][2] * ChessBoard[1][0] * ChessBoard[1][1] * ChessBoard[1][2] * ChessBoard[2][0] * ChessBoard[2][1] * ChessBoard[2][2] != 0)
	{
		MessageBoxA(NULL, "��Ϸ����", "Tic!", MB_OKCANCEL);
		//���û��������û��λ�ÿ����£�����
		return DrawnGame;
	}
}

//����(�߼��ṹ)
int StepMove(HWND _hwnd,LONG _posx, LONG _posy)
{
	//Position point;
	int Move = 1;
	//ʶ������
	if (_posx < 112 && _posx >= 20  && _posy >= 19  && _posy < 110 )
	{
		if (ChessBoard[0][0] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
		/*		ChessPaint1(_hwnd,_posx,_posy);*/
				ChessBoard[0][0] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
				/*ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[0][0] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	if (_posx < 204 && _posx >= 112  && _posy >= 19  && _posy < 110 )
	{
		if (ChessBoard[0][1] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
				/*ChessPaint1(_hwnd, _posx, _posy);*/
				ChessBoard[0][1] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
				/*ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[0][1] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	if (_posx < 295 && _posx >= 204  && _posy >= 19  && _posy < 110 )
	{
		if (ChessBoard[0][2] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
				/*ChessPaint1(_hwnd, _posx, _posy);*/
				ChessBoard[0][2] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
				/*ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[0][2] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	if (_posx < 112 && _posx >= 20  && _posy >= 110  && _posy < 202 )
	{
		if (ChessBoard[1][0] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
				/*ChessPaint1(_hwnd, _posx, _posy);*/
				ChessBoard[1][0] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
				/*ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[1][0] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	if (_posx < 204 && _posx >= 112  && _posy >= 110  && _posy < 202 )
	{
		if (ChessBoard[1][1] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
				/*ChessPaint1(_hwnd, _posx, _posy);*/
				ChessBoard[1][1] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
				/*ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[1][1] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	if (_posx < 295 && _posx >= 204  && _posy >= 110  && _posy < 202 )
	{
		if (ChessBoard[1][2] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
				/*ChessPaint1(_hwnd, _posx, _posy);*/
				ChessBoard[1][2] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
				/*ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[1][2] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	if (_posx < 112 && _posx >= 20  && _posy >= 202  && _posy < 293 )
	{
		if (ChessBoard[2][0] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
				/*ChessPaint1(_hwnd, _posx, _posy);*/
				ChessBoard[2][0] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
				/*ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[2][0] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	if (_posx < 204 && _posx >= 112  && _posy >= 202  && _posy < 293 )
	{
		if (ChessBoard[2][1] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
				/*ChessPaint1(_hwnd, _posx, _posy);*/
				ChessBoard[2][1] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
				/*ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[2][1] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	if (_posx < 295 && _posx >= 204  && _posy >= 202  && _posy < 293 )
	{
		if (ChessBoard[2][2] == CheckerNull)
		{
			//�ж�������˭����
			if (Move % 2 == 1)
			{
			/*	ChessPaint1(_hwnd, _posx, _posy);*/
				ChessBoard[2][2] = Player1;
				Move++;
			}
			if (Move % 2 == 0)
			{
			/*	ChessPaint2(_hwnd, _posx, _posy);*/
				ChessBoard[2][2] = Player2;
				Move++;
			}
		}
		else
			MessageBoxA(NULL, "���λ���Ѿ��������ˣ�", "����", MB_OK);
	}
	return 1;
}

//��ӡ
void GamePaint(HWND _hwnd, LONG _posx, LONG _posy)
{
	//���ھ���                           
	RECT rect;                          

	//��ȡ�������Ĵ�С
	GetClientRect(_hwnd, &rect);
	
	hdc = GetDC(_hwnd);

	hdcMem = CreateCompatibleDC(hdc);

	SelectObject(hdcMem, hbmpBackground);	
	GetObjectW(hbmpBackground, sizeof(BITMAP), &Board);
	StretchBlt(hdc, 
		rect.left, rect.top, 311,313,
		hdcMem,
		0, 0, Board.bmWidth, Board.bmHeight, 
		SRCCOPY);
	
	//GetObjectW(hbmpBackground, sizeof(BITMAP), &rect);
	if (StepMove( _hwnd, _posx, _posy))
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (ChessBoard[i][j] == 1)
				{
					if (_posx < 112 && _posx >= 20 && _posy >= 19 && _posy < 110)
					{
						SelectObject(hdcMem, HP1);
						GetObjectW(HP1, sizeof(BITMAP), &Board);
						//BitBlt(hdcMem2, 20, 19, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, 
							rect.left, rect.top, 
							92,92,
							hdcMem, 
							0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}

					if (_posx < 204 && _posx >= 112 && _posy >= 19 && _posy < 110)
					{
						SelectObject(hdcMem, HP1);
						BitBlt(hdcMem2, 112, 19, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 295 && _posx >= 204 && _posy >= 19 && _posy < 110)
					{
						SelectObject(hdcMem, HP1);
						BitBlt(hdcMem2, 204, 19, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 112 && _posx >= 20 && _posy >= 110 && _posy < 202)
					{
						SelectObject(hdcMem, HP1);
						BitBlt(hdcMem2, 20, 110, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 204 && _posx >= 112 && _posy >= 110 && _posy < 202)
					{
						SelectObject(hdcMem, HP1);
						BitBlt(hdcMem2, 112, 110, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 295 && _posx >= 204 && _posy >= 110 && _posy < 202)
					{
						SelectObject(hdcMem, HP1);
						BitBlt(hdcMem2, 204, 110, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 112 && _posx >= 20 && _posy >= 202 && _posy < 293)
					{
						SelectObject(hdcMem, HP1);
						BitBlt(hdcMem2, 20, 202, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 204 && _posx >= 112 && _posy >= 202 && _posy < 293)
					{
						SelectObject(hdcMem, HP1);
						BitBlt(hdcMem2, 112, 202, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 295 && _posx >= 204 && _posy >= 202 && _posy < 293)
					{
						SelectObject(hdcMem, HP1);
						BitBlt(hdcMem2, 204, 202, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
				}
				if (ChessBoard[i][j] == 2)
				{
					if (_posx < 112 && _posx >= 20 && _posy >= 19 && _posy < 110)
					{
						SelectObject(hdcMem, HP2);
						GetObjectW(HP2, sizeof(BITMAP), &Board);
						BitBlt(hdc, rect.left, rect.top, 92, 92, hdcMem, 0, 0, SRCCOPY);
						//StretchBlt(hdc,
						//	rect.left, rect.top, 
						//	92, 92,
						//	hdcMem,
						//	0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 204 && _posx >= 112 && _posy >= 19 && _posy < 110)
					{
						SelectObject(hdcMem, HP2);
						BitBlt(hdcMem2, 112, 19, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 295 && _posx >= 204 && _posy >= 19 && _posy < 110)
					{
						SelectObject(hdcMem, HP2);
						BitBlt(hdcMem2, 204, 19, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 112 && _posx >= 20 && _posy >= 110 && _posy < 202)
					{
						SelectObject(hdcMem, HP2);
						BitBlt(hdcMem2, 20, 110, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 204 && _posx >= 112 && _posy >= 110 && _posy < 202)
					{
						SelectObject(hdcMem, HP2);
						BitBlt(hdcMem2, 112, 110, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 295 && _posx >= 204 && _posy >= 110 && _posy < 202)
					{
						SelectObject(hdcMem, HP2);
						BitBlt(hdcMem2, 204, 110, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 112 && _posx >= 20 && _posy >= 202 && _posy < 293)
					{
						SelectObject(hdcMem, HP2);
						BitBlt(hdcMem2, 20, 202, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 204 && _posx >= 112 && _posy >= 202 && _posy < 293)
					{
						SelectObject(hdcMem, HP2);
						BitBlt(hdcMem2, 112, 202, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
					if (_posx < 295 && _posx >= 204 && _posy >= 202 && _posy < 293)
					{
						SelectObject(hdcMem, HP2);
						BitBlt(hdcMem2, 204, 202, 92, 92, hdcMem, 0, 0, SRCCOPY);
						StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
							hdcMem2, 0, 0, Board.bmWidth, Board.bmHeight, SRCCOPY);
					}
				}
			}
		}
	}
	    DeleteObject(hdcMem);
		DeleteDC(hdcMem);
		ReleaseDC(_hwnd, hdc);
		DeleteDC(hdc);
}