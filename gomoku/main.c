#include <stdio.h>
#include <unistd.h>
#include "lcd.h"
#include "bmp.h"
#include "touch.h"
#include "filelist.h"
#include "pthread.h"
#include <pthread.h>
#include "judge.h"

int main()
{
    //1.屏幕初始化
    lcd_init();

    //2.操作屏幕
DESKTOP:                            
    display_bmp(0,0,"gomokustart");        // 首页显示

    // BiList* l = creat_list();           // 创建一个头结点
    // BiNode* p = l->first;               // p指向
    

    // get_button();          //  进入五子棋游戏
    int x,y;
    while(1)
    {
        get_user_touch(&x,&y);              // 获取坐标

        if(x >= 300 && x <= 480 && y >= 340 && y <= 420)
        {
CONTINUE:            
            clear_lcd(0xee7621);            // 棋盘背景
            lcd_draw_chessboard();
            break;
        }
    }
    
    display_bmp(500,0,"gomoku.bmp");
    // create_pth();           //  建立一个播放背景音乐的线程

    int ret = move_chess();               // 落子

    if(ret == 1)
    {
        display_bmp(500,0,"WhiteWin.bmp");      // 白方胜利
        display_bmp(500,-430,"back.bmp");       // 退出
        display_bmp(500,-126,"continue.bmp");   // 再来一局
        while(1)
        {
            // int x = 0,y = 0;
            get_user_touch(&x,&y);

            if(x >= 500 && x <= 580 && y >= 430 && y <= 480)    // 点击退出键
            {
                goto DESKTOP;
            }

            if(x >= 500 && x <= 650 && y >= 125 && y <= 185)
            {
                goto CONTINUE;
            }
        }
    }
    else if(ret == 2)
    {
        display_bmp(500,0,"BlackWin.bmp");      // 黑方胜利
        display_bmp(500,-430,"back.bmp");       // 退出
        display_bmp(500,-126,"continue.bmp");   // 再来一局
        while(1)
        {
            int x = 0,y = 0;
            get_user_touch(&x,&y);

            if(x >= 500 && x <= 580 && y >= 430 && y <= 480)    // 点击退出键
            {
                goto DESKTOP;
            }

            if(x >= 500 && x <= 650 && y >= 125 && y <= 185)
            {
                goto CONTINUE;
            }
        }
    }
    
    

    
    //3.关闭映射和文件
    lcd_uinit();

    return 0;
}
