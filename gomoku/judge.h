#ifndef __JUDGE_H__
#define __JUDGE_H__

/*
    judge_win : 判断输赢
    @x ： 所下点的横坐标
    @y :  所下点的纵坐标
    @flag[][440] : 标志位  
    返回值 ：
        1   白胜
        2   黑胜

*/
int judge_win(int x,int y,int p[500][500]);

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
int move_chess();

#endif