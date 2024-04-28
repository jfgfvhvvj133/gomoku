#ifndef __FILELIST_H__
#define __FILELIST_H__

typedef char ElemType;
typedef struct binode
{
    ElemType data[512];         // 数据域
    struct binode* next;        // 指针域
    struct binode* prev;
}BiNode;
typedef struct bilist           // 头结点
{
    BiNode* first;

}BiList;

/*
    creat_cyclelist ：创建一个双向链表的头结点
    返回值 ：
        返回 头结点
*/
BiList* creat_cyclelist(void);

/*
    Insert ：插入数据结点
    @l : 头结点
    @p : 数据结点
    返回值 ：
        无返回值
*/
void  Insert(BiList* l,BiNode* p);

/*
    creat_list ：创建链表
    返回值 ：
        返回 链表的头结点
*/
BiList* creat_list(void);

/*
    traverse_list ：遍历链表
    @l : 遍历链表
    @way : 操作行为
    返回值 ：
        无返回值
*/
void traverse_list(BiList* l,int way);


#endif