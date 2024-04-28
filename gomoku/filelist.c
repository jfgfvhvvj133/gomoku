#include <stdio.h>
#include <stdlib.h>
#include "filelist.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "bmp.h"
#include <unistd.h>
#include "touch.h"



/*
    creat_cyclelist ：创建一个双向链表的头结点
    返回值 ：
        返回 头结点
*/
BiList* creat_cyclelist(void)                   // 创建一个带头结点的循环双向链表
{
    BiList* l = malloc(sizeof(*l));     
    l->first = NULL;                            // 初始化

    return l;                                   // 返回 头结点
}


/*
    Insert ：插入数据结点
    @l : 头结点
    @p : 数据结点
    返回值 ：
        无返回值
*/
void  Insert(BiList* l,BiNode* p)               // 往带头结点的双向链表上插入一个结点
{
    if(l == NULL)                               // 头结点不存在
    {
        return ;
    }

    if(l->first == NULL)                        // 没有数据结点
    {
        if(p)
        {
            p->next = p;                        
            p->prev = p;
            l->first = p;                       // 头结点指向第一各数据结点
        }
        return ;
    }

    // p->next = l->first;
    // p->prev = l->first->prev;
    // p->prev->next = p;
    // l->first->prev = p;
    p->next = l->first;                         // 连接链表
    p->prev = l->first->prev;
    l->first->prev->next = p;
    l->first->prev = p;

    return ;
}


/*
    creat_list ：创建链表
    返回值 ：
        返回 链表的头结点
*/
BiList* creat_list(void)
{
    BiList* l = creat_cyclelist();      // 头结点

    DIR* dir = NULL;
    struct dirent* dirp = NULL;                 // 初始化

    BiNode* p = NULL;                           // 定义指针

    dir = opendir("./pic");    // 打开目录
    if(dir == NULL)
    {
        perror("opendir error");                // 打印错误信息
        return NULL;
    }

    // 2.读目录
    while(dirp = readdir(dir))                  // 是否读完目录
    {
        //文件是 . 和 .. 直接跳过
        if(strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0)
        {
            continue;
        }

        p = malloc(sizeof(*p));                 // 数据结点
        sprintf(p->data,"%s/%s","./pic",dirp->d_name);  // 保存文件地址
        p->next = NULL;                         // 数据结点初始化
        p->prev = NULL;
        

        Insert(l,p);                // 插入链表
    }

    closedir(dir);      // 关闭目录

    return l;
}


/*
    traverse_list ：遍历链表
    @l : 遍历链表
    @way : 操作行为
    返回值 ：
        无返回值
*/
// 遍历链表
void traverse_list(BiList* l,int way)
{
    if(l == NULL)                   // 无头结点
    {
        return ;
    }

    BiNode* p = l->first;           // 指向第一个数据结点
    
    while(1)         // 循环遍历
    {
        printf("%s\n",p->data);     // 打印数据域
        display_bmp(0,0,p->data);   // 上色
        sleep(3);                   // 延时
        p = p->next;                // 下一个数据结点
    }

/*     if(way == DOWN)
    {
        p = p->next;
        display_bmp(0,0,p->data);
    }
    else
    {
        p = p->prev;
        display_bmp(0,0,p->data);
    } */
}