#!/usr/bin/env python
#全局变量
BackGround_MChess = 'MChessBoard.jpg'
#指定图像文件名称

import pygame
#导入pygame库
import MChess_ArmyGroup
#导入军队类型的文件
import Function
#导入函数
from pygame.locals import *
#导入一些常用的函数和常量
from sys import exit
#向sys模块借一个exit函数用来退出程序

pygame.init()
#初始化pygame,为使用硬件做准备

screen = pygame.display.set_mode((580*2, 480*2),0, 32)
#创建了一个窗口
pygame.display.set_caption("Milltary Chess")
#设置窗口标题

background = pygame.image.load(BackGround_MChess).convert()
#加载并转换图像

#设置图像的宽和高与窗口相等
width,height = background.get_size()
background = pygame.transform.smoothscale(background,(580*2,480*2))

#初始化游戏
Function.CreatGame()

while True:
#游戏主循环

    for event in pygame.event.get():
        if event.type == QUIT:
            #接收到退出事件后退出程序
            exit()
        if event.type == MOUSEBUTTONDOWN:
            x, y = pygame.mouse.get_pos()
            # 获得鼠标位置

            #JudgeChecker(x,y)
            #判断格子内是否有棋子，并且返回三种状态：无，有朝方棋子，有韩方棋子

    screen.blit(background, (0,0))
    #将背景图画在(0,0)的坐标处

    Function.GamePaint()
    #画出棋子

   # x-= mouse_cursor.get_width() / 2
  #  y-= mouse_cursor.get_height() / 2
    #计算光标的左上角位置
   # screen.blit(mouse_cursor, (x, y))
    #把光标画上去

    pygame.display.update()
    #刷新一下画面