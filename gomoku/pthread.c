#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lcd.h"
#include "bmp.h"
#include "touch.h"
#include "pthread.h"

/*
    play_music ：播放音乐
    arg : 音乐的路径
    返回值 ：
        指针
*/
void* play_music(void* arg)
{
    char buf[256] = {0};                // 存储路径
    sprintf(buf,"madplay %s",(char*)arg);   // 将arg存入buf
    printf("%s\n",buf);                 // 打印路径
    system(buf);                        // 播放音乐
}

/*
    create_pth : 创建线程
    返回值：
        返回 0 创建成功
        返回 -1 失败
*/
int create_pth(void)
{
    pthread_t tid = -1;                 // 指针,用来保存线程号
    int ret = pthread_create(&tid,NULL,play_music,"./music.mp3");
    if(ret != 0)                        // 判断线程是否创建成功
    {
        printf("Create thread fail\n"); // 不成功，打印错误信息
        return -1;
    }

    pthread_detach(tid);    // 设置线程的分离属性

    return 0;
}