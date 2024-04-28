#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "lcd.h"

int fb = -1;
int* plcd = NULL;                       // 初始化指针
/*
    lcd_init ：屏幕初始化
    返回值 ：
        无返回值
*/
void lcd_init(void)
{
    //int fb;
    //打开设备
    fb = open("/dev/fb0",O_RDWR);       // 打开文件
    if(fb == -1)
    {
        perror("open /dev/fb0 error");  // 打印错误信息
        return ;
    }
/*
    int color = 0x66eeaa;               // 在开发板上显示颜色

    for(int i = 0;i < 480;i++)
    {
        for(int j = 0;j < 800;j++)
        {
            write(fb,&color,4);
        }
    }

    close(fb);
*/
    //(2)获取屏幕信息

    //（3）int* plcd = mmap
    plcd = mmap(NULL,
                    800*480*4,
                    PROT_WRITE | PROT_READ,
                    MAP_SHARED,
                    fb,
                    0);                 // 用来映射内核或文件中的一块内存或文件内容到应用空间
    if(plcd == MAP_FAILED)              // 映射失败
    {
        perror("map error");            // 打印错误信息
        return;
    }
}

/*
    lcd_dsrw_point : 显示一个像素点的颜色
    @x : 像素点横坐标
    @y : 像素点纵坐标
    @color ： 像素点颜色值
    返回值 ：
        无返回值
*/
void lcd_draw_point(int x,int y,int color)
{
    if(x>=0&&x<800&&y>=0&&y<480)        // 屏幕范围
    {
        *(plcd + 800*y + x) = color;    // 给像素点上色
    }
}


/*
    lcd_uinit ：解除映射和关闭文件
    返回值 ：
        无返回值
*/
//解除映射和关闭文件
void lcd_uinit()
{
    munmap(plcd,800*480*4);             // 解除映射
    close(fb);                          // 关闭文件
}

/*
    clear_lcd ：背景
    @color : 背景后的颜色值
    返回值 ：
        无返回值
*/
void clear_lcd(int color)
{
    for(int i = 0;i < 480;i++)          // 横纵坐标范围
    {
        for(int j = 0;j < 800;j++)
        {
            lcd_draw_point(j,i,color);  // 上色
        }
    }
}

/*
    lcd_draw_chessboard : 在屏幕上显示棋盘
    返回值 ：
        无返回值
*/
void lcd_draw_chessboard(void)          // 画棋盘
{
    int x0 = 40,y0 = 40;                // 画棋盘的起始顶点
    int color = 0x000000;               
    
    for(int y = 0;y <= 410;y += 40 )    // 纵坐标范围
    {
        for(int x = 0;x <= 400;x++) // 横坐标范围
        {
            lcd_draw_point(x + x0,y + y0,color);    // 上色
            lcd_draw_point(x + x0 + 1,y + y0 + 1,color);    // 上色
        }
        
    }
    
    for(int x = 0;x <= 410;x += 40 )    // 横坐标范围
    {
        for(int y = 0;y <= 400;y++) // 纵坐标范围
        {
            lcd_draw_point(x + x0,y + y0,color);    // 上色
            lcd_draw_point(x + x0 + 1,y + y0 + 1,color);    // 上色
        }
        
    }
}

/*
    lcd_draw_piece : 在屏幕上显示棋子
    @x0 : 棋子的圆心横坐标
    @y0 : 棋子的圆心纵坐标
    @color : 棋子颜色（黑/白）
    返回值 ： 
        成功 返回 1
        失败 返回 0
*/
int lcd_draw_piece(int x0,int y0,int color)
{
    for(int y = 0;y < 480;y++)
    {
        for(int x = 0;x < 480;x++)
        {
            if(((x-x0)*(x-x0)+(y-y0)*(y-y0))<18*18)
            {
                lcd_draw_point(x,y,color);
            }
        }
    }
}