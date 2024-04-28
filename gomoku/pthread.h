#ifndef __PTHREAD_H__
#define __PTHREAD_H__

/*
    play_music ：播放音乐
    arg : 音乐的路径
    返回值 ：
        指针
*/
void* play_music(void* arg);

/*
    create_pth : 创建线程
    返回值：
        返回 0 创建成功
        返回 -1 失败
*/
int create_pth(void);


#endif