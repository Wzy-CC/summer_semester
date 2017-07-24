import MChess_ArmyGroup
import pygame
status=(0,1,2)
#状态：tuple存储：
    #0：无棋子
    #1：朝鲜棋子
    #2：韩国棋子

#两个国家的棋子：
SKoreaChess = 'SKorea.png'
NKoreaChess = 'NKorea.png'

#加载并转换图像:
SKorea = pygame.image.load(SKoreaChess).convert()
NKorea = pygame.image.load(NKoreaChess).convert()

#设置图像的宽和高与背景图的
width,height = background.get_size()
background = pygame.transform.smoothscale(background,(580*2,480*2))

# 二维数组存储整个棋盘（逻辑结构）
# 初始化棋盘为0（空）
MChessBoard = [([0] * 13) for i in range(10)]

#初始化游戏
def CreatGame():
    #将朝鲜军队初始化：
    for N_x in range(13):
        for N_y in range(10):
             NKorea = (N_x,N_y)
             if NKorea in MChess_ArmyGroup.NKorea_ArmyPos:
                 MChessBoard[N_x][N_y] = 1
             if NKorea in MChess_ArmyGroup.NKorea_NavyPos:
                 MChessBoard[N_x][N_y] = 1

    #将韩国军队初始化：
    for S_x in range(13):
         for S_y in range(10):
              SKorea = (S_x, S_y)
              if SKorea in MChess_ArmyGroup.SKorea_ArmyPos:
                  MChessBoard[S_x][S_y] = 2
              if SKorea in MChess_ArmyGroup.SKorea_NavyPos:
                  MChessBoard[S_x][S_y] = 2

  #画图时遍历整个棋盘
def JudgeChecker(x,y):
    x_Checker = x / 130
    # 计算逻辑坐标
    y_Checker = y / 130
    # 计算逻辑坐标

   # if
#    if (x_Checker,y_Checker) in NKorea_ArmyPos :
   #  return status(0)

#画出棋子
def GamePaint():
    #遍历二维数组，根据二维数组的值打印出棋子
    for pos_x in range(13):
        for pos_y in range(10):
            if MChessBoard[pos_x][pos_y] == 1:
                blit
