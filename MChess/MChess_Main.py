#!/usr/bin/env python

#背景图片：
BackGround_MChess = 'MChessBoard.jpg'
#两个国家的棋子：
SKoreaChess = 'SKorea.png'
NKoreaChess = 'NKorea.png'
#黑叉
Block = 'Block_Black.png'
#鼠标
mouse = 'mouse.png'

#导入pygame库
import pygame

#导入MChess_Global.py
import MChess_Global

#导入一些常用的函数和常量
from pygame.locals import *

#向sys模块借一个exit函数用来退出程序
from sys import exit

#初始化pygame,为使用硬件做准备
pygame.init()

#创建了一个窗口
screen = pygame.display.set_mode((845, 715),0, 32)

#设置窗口标题
pygame.display.set_caption("Milltary Chess")

#加载并转换图像
background = pygame.image.load(BackGround_MChess).convert()
SKorea = pygame.image.load(SKoreaChess).convert_alpha()
NKorea = pygame.image.load(NKoreaChess).convert_alpha()
Block_Black = pygame.image.load(Block).convert_alpha()
mouse_cursor = pygame.image.load(mouse).convert_alpha()

#设置图像的宽和高与窗口相等
width,height = background.get_size()
background = pygame.transform.smoothscale(background,(845,715))

#设置图像的宽和高与背景图的每个格子相匹配
SKorea_width,SKorea_height = SKorea.get_size()
NKorea_width,NKorea_height = NKorea.get_size()
SKorea = pygame.transform.smoothscale(SKorea,(60,60))
NKorea = pygame.transform.smoothscale(NKorea,(65,65))
Block_Black = pygame.transform.smoothscale(Block_Black,(70,70))
mouse_cursor = pygame.transform.smoothscale(mouse_cursor,(80,60))

# 二维数组存储整个棋盘（逻辑结构）
# 初始化棋盘为0（空）
MChessBoard = [([0] * 10) for i in range(13)]

#初始化游戏
def CreatGame():
    #将朝鲜军队初始化：
    for N_x in range(13):
        for N_y in range(10):
             NKorea_pos = [N_x+1,N_y+1]
             if NKorea_pos in MChess_Global.NKorea_ArmyPos:
                 MChessBoard[N_x][N_y] = 1
             if NKorea_pos in MChess_Global.NKorea_NavyPos:
                 MChessBoard[N_x][N_y] = 1
             if NKorea_pos in MChess_Global.Peace_Zone:
                 MChessBoard[N_x][N_y] = 3

    #将韩国军队初始化：
    for S_x in range(13):
         for S_y in range(10):
              SKorea_pos = [S_x+1, S_y+1]
              if SKorea_pos in MChess_Global.SKorea_ArmyPos:
                  MChessBoard[S_x][S_y] = 2
              if SKorea_pos in MChess_Global.SKorea_NavyPos:
                  MChessBoard[S_x][S_y] = 2

CreatGame()

#画出棋子
def GamePaint():
    #遍历二维数组，根据二维数组的值打印出棋子
    for pos_x in range(13):
        for pos_y in range(10):
            if MChessBoard[pos_x][pos_y] == 1:
                #pass
               screen.blit(NKorea, (pos_x*65, pos_y*65))
            if MChessBoard[pos_x][pos_y] == 2:
                screen.blit(SKorea, (pos_x*65, pos_y*65))
            if MChessBoard[pos_x][pos_y] == 3:
                screen.blit(Block_Black, (pos_x*65, pos_y*65))

#回合计数(朝鲜率先发动进攻)：
turn = 1
#记录鼠标点击次数：
mouse_count = 0
#标记当前选中的格子(初值为[0,0])：
selected = [0,0]
#标记攻击棋子：
Attacker = [0,0]
#标记被攻击棋子：
Victim = [0,0]

def Attack(Attacker,Victim,int):
    #M_x = Victim[0]
    #M_y = Victim[1]
    M_x,M_y = Victim
    MChessBoard[M_x][M_y] = 0

#游戏主循环
while True:
    for event in pygame.event.get():
        # 接收到退出事件后退出程序
        if event.type == QUIT:
            exit()

        # 接收到鼠标点击的事件
        if event.type == MOUSEBUTTONDOWN:
            mouse_count = mouse_count + 1

            # 获得鼠标位置:
            x, y = pygame.mouse.get_pos()

            # 计算逻辑坐标：
            x_Checker = int (x / 65)
            y_Checker = int (y / 65)
            selected = [x_Checker, y_Checker]

            if mouse_count % 2 == 0:
                MChessBoard[x_Checker][y_Checker] = 0


    # 将背景图画在(0,0)的坐标处
    screen.blit(background, (0,0))

    # 画出棋子
    GamePaint()

    # 获得鼠标位置
    x, y = pygame.mouse.get_pos()
    # 计算光标的左上角位置
    x-= mouse_cursor.get_width() / 2
    y-= mouse_cursor.get_height() / 2
    # 把光标画上去
    screen.blit(mouse_cursor, (x, y))

    # 刷新一下画面
    pygame.display.update()