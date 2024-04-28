#include <linux/input.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "touch.h"
#include "bmp.h"
#include "filelist.h"
#include "lcd.h"

/*
    get_user_touch ：获取触摸屏坐标
    @x : 保存横坐标
    @y : 保存纵坐标
    返回值:
        无返回值
*/
void get_user_touch(int* x,int* y)
{
    int fd = open("/dev/input/event0",O_RDONLY);    // 打开文件
    if(fd == -1)                                    // 判断文件是否打开成功
    {
        perror("open /dev/input/event0 error");     // 打印错误信息
        return ;
    }
    struct input_event ev;                          // 定义结构体变量

    while(1)                                        
    {
        int r = read(fd,&ev,sizeof(ev));            // 读取信息
        if(r != sizeof(struct input_event))         // 未获取进入下一循环
        {
            continue;
        }

        if(ev.type == EV_ABS && ev.code == ABS_X)   // 触摸屏横坐标
        {
            *x = ev.value/1.3;
        }

        if(ev.type == EV_ABS && ev.code == ABS_Y)   // 触摸屏纵坐标
        {
            *y = 0.8*ev.value;
        }

        if(ev.type == EV_KEY && ev.code == 330 && ev.value == 0)    // 获取成功跳出循环
        {
            break;
        }

        // if(ev.type == EV_ABS)        //write by me
        // {
        //     if(ev.code == ABS_X)
        //     {
        //         *x = ev.value/1.3;
        //     }
        //     else
        //     {
        //         *y = 0.8*ev.value;
        //         break;
        //     }
        // }
        
    }
    // 关闭文件
    close(fd);
}

// int main()
// {  
//     int x,y;
//     get_user_touch(&x,&y);
//     printf("(%d , %d)\n",x,y);
//     // while(1)
//     // {
//     //     read(fd,&ev,sizeof(ev));
//     //     printf("type: %d code: %d value: %d\n",ev.type,ev.code,ev.value);
//     // }
//     return 0;
// }

/*
    get_fingle_move : 获取手指移动方向
    返回值 ：
        返回 UP 1
        返回 DOWN 2
        返回 LEFT 3
        返回 RIGHT 4
        返回 -1   失败
        返回 0 按下退出按钮
*/
int get_fingle_move()
{
    int fd = open("/dev/input/event0",O_RDONLY);    // 打开文件
    if(fd == -1)                                    // 判断文件是否打开成功
    {
        perror("open /dev/input/event0 error");     // 打印错误信息
        return -1;
    }
    // 1.获取坐标
    int x0 = -1,y0 = -1;    // 初始坐标
    int x1,y1;              // 第二次获取坐标

    struct input_event ev;  // 定义结构体变量

    while(1)
    {
        int r = read(fd,&ev,sizeof(ev));    // 读取信息
        if(r != sizeof(struct input_event)) // 未获取进入下一循环
        {
            continue;
        }

        if(ev.type == EV_ABS && ev.code == ABS_X)   // 触摸屏横坐标
        {
            if(x0 == -1)
            {
                x0 = ev.value;                      // 初始坐标
            }
            x1 = ev.value;                          // 第二次获取坐标
        }

        if(ev.type == EV_ABS && ev.code == ABS_Y)   // 触摸屏纵坐标
        {
            if(y0 == -1)                            
            {
                y0 = ev.value;                      // 初始坐标
            }
            y1 = ev.value;                          // 第二次获取坐标
        }

        if(ev.type == EV_KEY && ev.code == 330 && ev.value == 0)    // 获取成功跳出循环
        {
            break;
        }
    }
    // 2.判断上下左右

    int way;                        // 存储操作行为
    if(abs((y1-y0)/(x1-x0)) >= 1)   // 向上或向下
    {
        if(y1 > y0)                 // 向下滑动
        {
            printf("DOWN!\n");
            way = DOWN;             
        }
        else                        // 向上滑动
        {
            printf("UP!\n");
            way = UP;
        }
    }
    else
    {
        if(x1 > x0)                 // 通过横坐标差判断左右滑动
        {
            printf("RIGHT!\n");
            way = RIGHT;            // 向右滑动
        }
        else
        {
            printf("LEFT!\n");
            way = LEFT;             // 向左滑动
        }
    }

    if(x0 >= 0 && x0 <= 82 && y0 >= 0 && y0 <= 56)  // 这个范围为退出按钮
    {
        way = 0;
    }
    // 关闭文件
    close(fd);
    // 返回操作行为
    return way;
}

/*
    get_button ：进入五子棋游戏
    返回值 ：
        无返回值
*/
void get_button()
{
    int x,y;
    
    while(1)
    {
        get_user_touch(&x,&y);              // 获取坐标

        if(x >= 300 && x <= 480 && y >= 340 && y <= 420)
        {
            clear_lcd(0xee7621);            // 棋盘背景
            lcd_draw_chessboard();
            break;
        }
    }
}


/*
    back_desktop : 返回桌面
    返回值 :
        返回 1 收到返回桌面指令
*/
int back_desktop()
{
    int x,y;
    display_bmp(0,0,"button2");     // 显示按键图标
 
    get_user_touch(&x,&y);          // 获取坐标
    if(x >= 0 && x <= 82 && y >= 0 && y <= 56)      
    {
        return 1;                   // 若在范围内则返回1
    }
    else
    {
        return 0;                   // 不在范围内返回0
    }

}