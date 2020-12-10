#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //数据元素类型定义
#define LISTS_INIT_SIZE 100
#define LISTSINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
typedef struct{  //线性表的管理表定义
    struct List{
        char name[30];
        LinkList L;
    }elem[100];
    int length=0;
    int listsize=100;
}LISTS;