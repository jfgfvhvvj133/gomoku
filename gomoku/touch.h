#ifndef __TOUCH_H__
#define __TOUCH_H__

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

/*
    get_user_touch ：获取触摸屏坐标
    @x : 保存横坐标
    @y : 保存纵坐标
    返回值:
        无返回值
*/
void get_user_touch(int* x,int* y);

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
int get_fingle_move();

/*
    get_button ：进入五子棋游戏
    返回值 ：
        无返回值
*/
void get_button();

/*
    back_desktop : 返回桌面
    返回值 :
        返回 1 收到返回桌面指令
*/
int back_desktop();

#endif