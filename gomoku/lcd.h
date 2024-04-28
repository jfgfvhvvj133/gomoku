#ifndef __LCD_H__
#define __LCD_H__

/*
    lcd_init ：屏幕初始化
    返回值 ：
        无返回值
*/
void lcd_init(void);

/*
    lcd_dsrw_point : 显示一个像素点的颜色
    @x : 像素点横坐标
    @y : 像素点纵坐标
    @color ： 像素点颜色值
    返回值 ：
        无返回值
*/
void lcd_draw_point(int x,int y,int color);

/*
    lcd_uinit ：解除映射和关闭文件
    返回值 ：
        无返回值
*/
void lcd_uinit();

/*
    clear_lcd ：背景
    @color : 背景后的颜色值
    返回值 ：
        无返回值
*/
void clear_lcd(int color);

/*
    lcd_draw_chessboard : 在屏幕上显示棋盘
    返回值 ：
        无返回值
*/
void lcd_draw_chessboard(void);

/*
    lcd_draw_piece : 在屏幕上显示棋子
    @x0 : 棋子的圆心横坐标
    @y0 : 棋子的圆心纵坐标
    @color : 棋子颜色（黑/白）
    返回值 ： 
        成功 返回 1
        失败 返回 0
*/
int lcd_draw_piece(int x0,int y0,int color);

#endif