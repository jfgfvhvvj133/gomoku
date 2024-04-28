#include <stdio.h>
#include <stdlib.h>
#include "touch.h"
#include "judge.h"
#include "lcd.h"
#include "bmp.h"

/*
    judge_win : 判断输赢
    @x ： 所下点的横坐标
    @y :  所下点的纵坐标
    @flag[][440] : 标志位  
    返回值 ：
        1   白胜
        2   黑胜

*/
int judge_win(int x,int y,int p[500][500])
{
    int count = 0;                          // 计数
     
    
    for(int i = 40;i <= 440;i += 40)    // 横遍历
    {
        if(p[i][y] == p[x][y])          // 遇到同色棋计数
        {
            count++;
        }
        else                            // 否则清零
        {       
            count = 0;
        }

        if(count >= 5)                  // 出现五子相连的情况
        {
            if(p[x][y] == 1)         // 判断相连的五子是白子还是黑子
            {
                printf("White Win\n");
                return 1;
            }
            else if(p[x][y] == 2)
            {
                printf("Black Win\n");
                return 2;
            }

        }
    }
    
    count = 0;                          // 完成横遍历进行纵遍历时对计数变量清零
    for(int j = 40;j <= 440;j += 40)    // 纵遍历
    {
        if(p[x][j] == p[x][y])           // 遇到同色棋计数
        {
            count++;
        }
        else                            // 否则清零
        {
            count = 0;
        }

        if(count >= 5)                  // 出现五子相连
        {
           if(p[x][y] == 1)
            {
                printf("White Win\n");  // 白胜
                return 1;
            }
            else if(p[x][y] == 2)
            {
                printf("Black Win\n");  // 黑胜
                return 2;
            }
        }
    }

    count = 0;                          // 对计数变量清零
    int a = x,b = y;                    // 保存横纵坐标
    while(p[a][b])           // 向左上遍历
    {
        if(p[a][b] == p[x][y])          // 同色棋计数
        {
            count++;
        }
        else
        {
            break;
        }
        
        a -= 40;
        b -= 40;
    }

    a = x,b = y;                        // 重新赋值
    while(p[a][b])         // 向右下遍历
    {
        a += 40;
        b += 40;

        if(p[a][b] == p[x][y])          // 同色棋计数
        {
            count++;
        }
        else
        {
            break;
        }         
    }

    if(count >= 5)                  // 出现五子相连
    {
        if(p[x][y] == 1)
        {
            printf("White Win\n");  // 白胜
            return 1;
        }
        else if(p[x][y] == 2)
        {
            printf("Black Win\n");  // 黑胜
            return 2;
        }
    }
    else
    {
        count = 0;                  // 没有五子相连计数清零
    }
    
    a = x,b = y;                        // 保存横纵坐标
    while(p[a][b])           // 向左上遍历
    {
        if(p[a][b] == p[x][y])          // 遇到同色棋计数
        {
            count++;
        }
        else
        {
            break;
        }
        
        a += 40;
        b -= 40;
    }

    a = x,b = y;                        // 重新赋值
    while(p[a][b])         // 向右下遍历
    {
        a -= 40;
        b += 40;

        if(p[a][b] == p[x][y])          // 遇到同色棋计数 
        {
            count++;
        }
        else
        {
            break;
        }         
    }

    if(count >= 5)                  // 出现五子相连
    {
        if(p[x][y] == 1)
        {
            printf("White Win\n");  // 白胜
            return 1;
        }
        else if(p[x][y] == 2)
        {
            printf("Black Win\n");  // 黑胜
            return 2;
        }
    }
    else
    {
        count = 0;                  // 没有五子相连计数清零
    }

}


/*
    move_chess : 落子，通过触屏坐标确定落子位置
    @flag 标志位
        0 表示 交叉点无棋子
        1 表示 交叉点有白子
        2 表示 交叉点有黑子
    返回值 ：
        1   白胜
        2   黑胜
*/
int move_chess()
{
    int flag[500][500];                         // 交叉点标志位
    for(int y = 0;y <= 400;y += 40 )             // 纵坐标范围
    {
        for(int x = 0;x <= 400;x += 40)         // 横坐标范围
        {
           flag[x + 40][y + 40] = 0;            // 置 0 表示 交叉点无棋子
        }
        
    }

    int num = 0;                              // 计算手数
    int ret = 0;                                // 1    白胜    2   黑胜
    while(1)
    {
        int a,b;                              // 保存横纵坐标
        // int* p = flag;
        get_user_touch(&a,&b);                // 获取触摸屏坐标
        
        printf("%d,%d\n",a,b);
        // if(a < 460)                          // 棋盘区域
        // {
        //     // 判断离那个交叉点最近
        //     for(int y = 0;y <= 400;y += 40 )    // 纵坐标范围
        //     {
        //         for(int x = 0;x <= 400;x += 40)     // 横坐标范围
        //         {
        //             if((abs(x + 40 - a) < 15) && (abs(y + 40 - b)< 15))
        //             {
        //                 if(num % 2 == 0 )
        //                 {
        //                     lcd_draw_piece(x + 40,y + 40,0x000000);     // 黑棋先手
        //                     flag[x + 40][y + 40] = 2;                   // 标记该点为黑子 
        //                     num++;
        //                 }
        //                 else 
        //                 {
        //                     lcd_draw_piece(x + 40,x + 40,0xffffff);     // 白棋下
        //                     flag[x + 40][y + 40] = 1;                   // 标记该点为白子
        //                     num++;
        //                 }
        //             }
        //         } 
        //     }
        // }
        if(num % 2 == 0)                        // 黑棋
        {
            for(int y = 0;y <= 400;y += 40 )             // 纵坐标范围
            {
                for(int x = 0;x <= 400;x += 40)         // 横坐标范围
                {
                    if((abs(x + 40 - a) < 15) && (abs(y + 40 - b)< 15) && flag[x + 40][y + 40] == 0)
                    {
                        lcd_draw_piece(x + 40,y + 40,0x000000); // 黑棋
                        flag[x + 40][y + 40] = 2;               // 标志位赋值

                        ret = judge_win(x + 40,y + 40,flag);          // 判断是否五子相连
                        if(ret == 1)
                        {
                            break;
                        }

                        printf("%d\n",flag[x + 40][y + 40]);
                        num++;
                    }

                }
  
                if(ret == 1)
                {
                    break;
                }
            }  
        }
        else                                    // 白棋
        {
            for(int y = 0;y <= 400;y += 40 )             // 纵坐标范围
            {
                for(int x = 0;x <= 400;x += 40)         // 横坐标范围
                {
                    if((abs(x + 40 - a) < 15) && (abs(y + 40 - b)< 15) && flag[x + 40][y + 40] == 0)
                    {
                        lcd_draw_piece(x + 40,y + 40,0xffffff); // 白棋
                        flag[x + 40][y + 40] = 1;               // 标志位赋值

                        ret = judge_win(x + 40,y + 40,flag);          // 判断是否五子相连
                        if(ret == 2)
                        {
                            break;
                        }

                        printf("%d\n",flag[x + 40][y + 40]);
                        num++;
                    }
                }

                if(ret == 2)
                {
                    break;
                }
            }
        }

        if(ret == 1 || ret == 2)
        {
            break;
        }

    }  

    if(ret == 1)
    {
        return 1;
    }
    else if(ret == 2)
    {
        return 2;
    }
}


