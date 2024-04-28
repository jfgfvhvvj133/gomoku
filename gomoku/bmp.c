#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "lcd.h"
#include "bmp.h"
#include <stdlib.h>


/*
    display_bmp :显示bmp图片
    @x0 : 图片的初始横坐标
    @y0 : 图片的初始纵坐标
    @bmpfile : 要显示哪个图片
    返回值 :
        返回 -1 文件打开失败
        返回 -2 不是BMP文件
        返回 -3 无色深
*/
int display_bmp(int x0,int y0,char* bmpfile)
{
    int fd = open(bmpfile,O_RDWR);  //打开文件
    if(fd == -1)
    {
        perror("open bmpfile error");   // 打印错误信息
        return -1;
    }
    unsigned char buf[4];      //保存读取的信息
    read(fd,buf,2);         // BITMAP文件头
    if(buf[0] != 0x42 || buf[1] != 0x4d)    // 判断是否为BMP文件
    {
        printf("NOt Bmp!\n");
        return -2;
    }

    // DIB头
    int width;      // 位图宽度
    lseek(fd,0x12,SEEK_SET);
    read(fd,buf,4);

    width = (buf[3] << 24)|(buf[2] << 16)|(buf[1] << 8)|(buf[0]);   // 宽度

    int height;     // 位图高度
    lseek(fd,0x16,SEEK_SET);
    read(fd,buf,4);

    height = (buf[3] << 24)|(buf[2] << 16)|(buf[1] << 8)|(buf[0]);  // 高度

    short depth;      // 色深
    lseek(fd,0x1c,SEEK_SET);
    read(fd,buf,2);

    depth = (buf[1] << 8)|(buf[0]);
    if(!(depth == 24 || depth == 32))   // 判断是否有色深
    {
        printf("Not depth\n");
        return -3;
    }

    // printf("%s: width = %d height = %d depth = %d",bmpfile,width,height,depth);

    int line_vaild_bytes = width*depth/8;   // 一行的有效字节数
    int line_bytes; // 一行的总字节数 = 有效的字节数 + 填充字节
    int fill_bytes = 0; // 填充字节

    if(line_vaild_bytes%4)
    {
        fill_bytes = 4 - line_vaild_bytes%4;
    }
    line_bytes = line_vaild_bytes + fill_bytes; // 为了保证每一行数据的字节是4的倍数,
                                                // 可能会在每一行的数据的末尾填充几个字节.

    int total_bytes = line_bytes*abs(height); // 整个像素数组的大小 

    unsigned char color_buf[total_bytes];   // 存像素数组
    lseek(fd,0x36,SEEK_SET);                // 将光标移动到像素数组初始位置
    read(fd,color_buf,total_bytes);         // 从文件读取像素数组

    // 在屏幕上显示
    int color;                              // 储存颜色值
    int i = 0;
    unsigned char a,b,g,r;                  // 保存各颜色值的变量
    for(int y = 0;y < abs(height);y++)      // 从像素数组中读取颜色值
    {
        
        for(int x = 0;x < width;x++)
        {
            b = color_buf[i++];             // 蓝色的颜色值
            g = color_buf[i++];             // 绿色的颜色值
            r = color_buf[i++];             // 红色的颜色值

            if(depth == 32)                 // 颜色值占32bits,标准色ARGB8888
            {
                a = color_buf[i++];
            }
            else                            //  24 颜色值占24bits,标准色RGB888
            {
                a = 0;
            }
            color = ((a << 24)|(r << 16)|(g << 8)|b);   // 颜色值
            lcd_draw_point(x+x0,height-(y+y0),color);   // 上色
        }
        // 每一行的末尾,如果字节数不是4的倍数,需要填充几个字节
        i = i + fill_bytes;
    }
    // 关闭文件
    close(fd);   

    return 0;

}



