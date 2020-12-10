#include "dev.h"
#include <cstdio>
#include "malloc.h"
#include <cstring>

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name, ListName)==0){
            for(int j=i;j<Lists.length-1;j++){
                strcpy(Lists.elem[j].name, Lists.elem[j+1].name);
                Lists.elem[j].L = Lists.elem[j+1].L;
            }
            Lists.length--;
            return 1;
        }
    }
    return 0;

    /********** End **********/
}

status InitList(LinkList &L)
{
    /*
     * input:
     * L: 链表头指针
     * lists: 多链表
     * ListName: 链表名字
     * return:
     * OK: create succeed
     *
     */
    /********** Begin *********/
    if(L == NULL){
        L = (LinkList)malloc(sizeof(LNode));
        L->next = NULL;
//        lists.length = 0;
//        strcpy(lists.elem[lists.length].name, ListName);
//        lists.elem[lists.length].L = L;
        return OK;
    }
    else return INFEASIBLE;

    /********** End **********/
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    else{
        free(L);
        L = NULL;
        return OK;
    }

    /********** End **********/
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    else{
        free(L->next);
        L->next = NULL;
        return OK;
    }

    /********** End **********/
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    else{
        if(L->next == NULL) return TRUE;
        else return NULL;
    }

    /********** End **********/
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    else{
        LNode *p;
        int length=0;
        p = (LinkList)malloc(sizeof(LNode));
        p = L;
        while(p->next != NULL){
            length++;
            p = p->next;
        }
        return length;
    }

    /********** End **********/
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    else{
        LNode *p;
        int cur=0;
        p = (LinkList)malloc(sizeof(LNode));
        p = L;
        while(p->next != NULL){
            p = p->next;
            cur++;
            if(cur==i){
                e = p->data;
                return OK;
            }
        }
        return ERROR;
    }

    /********** End **********/
}


status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    else{
        LNode *p;
        int cur=0;
        p = (LinkList)malloc(sizeof(LNode));
        p = L;
        while(p->next != NULL){
            p = p->next;
            cur++;
            if(e==p->data) return cur;
        }
        return ERROR;
    }

    /********** End **********/
}


status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL) return INFEASIBLE;
    else{
        LNode *p;
        int cur=0;
        p = (LinkList)malloc(sizeof(LNode));
        p=L;
        while(p->next != NULL){
            p = p->next;
            if(p->next == NULL) return ERROR;
            if(p->next->data == e){
                pre = p->data;
                return OK;
            }
        }
        return ERROR;
    }

    /********** End **********/
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else{
        LNode *p;
        int cur=0;
        p = (LinkList)malloc(sizeof(LNode));
        p=L;
        while(p->next != NULL){
            p = p->next;
            if(p->next==NULL) return ERROR;
            if(p->data == e){
                next = p->next->data;
                return OK;
            }
        }
        return ERROR;
    }

    /********** End **********/
}


status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else{
        LNode *p;
        int cur=0;
        p = (LinkList)malloc(sizeof(LNode));
        p=L;
        if(cur == i-1){
            LNode *temp;
            temp = (LinkList)malloc(sizeof(LNode));
            temp->data = e;
            temp->next = p->next;
            p->next = temp;
            return OK;
        }
        while(p->next != NULL){
            p = p->next;
            cur++;
            if(cur == i-1){
                LNode *temp;
                temp = (LinkList)malloc(sizeof(LNode));
                temp->data = e;
                temp->next = p->next;
                p->next = temp;
                return OK;
            }
        }
        return ERROR;
    }

    /********** End **********/
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else{
        LNode *p;
        int cur=0;
        p = (LinkList)malloc(sizeof(LNode));
        p=L;
        while(p->next!=NULL){
            p = p->next;
            cur++;
            if (i==1){
                e = L->next->data;
                L->next = L->next->next;
                return OK;
            }
            if(cur==i-1){
                LNode *temp;
                temp = (LinkList)malloc(sizeof(LNode));
                temp = p->next;
                e = temp->data;
                p->next = temp->next;
                free(temp);
                temp=NULL;
                return OK;
            }
        }
        return ERROR;

    }

    /********** End **********/
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L==NULL) return INFEASIBLE;
    else{
        LNode *p;
        int cur=0;
        p = (LinkList)malloc(sizeof(LNode));
        p=L;
        while(p->next!=NULL){
            p = p->next;
            printf("%d ", p->data);
        }
        return OK;
    }

    /********** End **********/
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if(L==NULL) return INFEASIBLE;
    else{
        FILE *fp;
        fp = fopen(FileName, "w");
        if(fp==NULL) printf("file open failed!");
        LNode *p;
        // int cur=0;
        p = (LinkList)malloc(sizeof(LNode));
        p=L;
        int c;
        while(p->next!=NULL){
            p = p->next;
            c = p->data;
            fputc(c, fp);
        }
        fclose(fp);
        return OK;
    }

    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if(L!=NULL) return INFEASIBLE;
    else{
        FILE *fp;
        int i;
        fp = fopen(FileName, "r");
        if(fp==NULL) printf("file open failed!");
        LNode *tail;
        L = (LinkList)malloc(sizeof(LNode));
        tail = (LinkList)malloc(sizeof(LNode));
        tail = L;
        while(!feof(fp)){
            i = fgetc(fp);
            if(feof(fp)) break;
            LNode *p;
            p = (LinkList)malloc(sizeof(LNode));
            p->data = i;
            tail->next = p;
            tail = tail->next;
        }
        tail->next = NULL;
        fclose(fp);
        return OK;
    }

    /********** End 2 **********/
}

status Add_to_Lists(LISTS &lists, char ListName[], LinkList &L)
{
    /*
     * input:
     * lists: 多线性表
     * ListName: 线性表名字
     * L: 要加入多线性表的线性表的头指针
     * RETURN:
     * 1: 添加成功
     */
    if(L == NULL) return INFEASIBLE;
    for(int i=0;i<lists.length;i++){
        if(strcmp(lists.elem[i].name, ListName)==0){
            return 0;
        }
    }
    strcpy(lists.elem[lists.length].name, ListName);
    lists.elem[lists.length].L = L;
    lists.length++;
    L = NULL;
    return 1;
}



int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name, ListName)==0){
            return i+1;
        }
    }
    return 0;

    /********** End **********/
}

void showlist(LISTS LISTS){
    /*
     * function: 打印多线性表中的元素
     *
     */
    printf("there are %d lists\n", LISTS.length);
    for(int i=0;i<LISTS.length;i++){
        printf("%s:", LISTS.elem[i].name);
        LinkList p;
        p = (LinkList)malloc(sizeof(LNode));
        p = LISTS.elem[i].L->next;
        while (p != nullptr){
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");

    }
}

status Switch_to_List(LISTS &Lists, char ListName[], LinkList &L){
    /*
     * function：切换操作的线性表
     * input:
     * Lists: 多线性表对象
     * ListName: 指定的线性表名字
     * L：线性表
     */
    for(int i=0;i<Lists.length;i++){
        if(strcmp(Lists.elem[i].name, ListName)==0){
            L = Lists.elem[i].L;
            return 1;
        }
    }
    return 0;
}

ElemType Get_Greatest(LinkList L){
    /*
     * function: 获得最大元素
     * input：线性表
     * return 最大元素
     */
    ElemType max;
    LinkList p;
    p = (LinkList)malloc(sizeof(LNode));
    p = L->next;
    max = p->data;
    while (p!=NULL){
        if (p->data>=max){
            max = p->data;
        }
        p = p->next;
    }
    return max;

}

status Bucket_Sort(LinkList &L)
{
    /*
     * function: 桶排序
     * input：链表头节点
     */
    ElemType *bucket;
    LinkList p;
    p = (LinkList)malloc(sizeof(LNode));
    p = L->next;
    int length  = Get_Greatest(L);
    bucket = (ElemType *)malloc(sizeof(ElemType)*length);
    for(int i=0;i<length;i++){  //bucket 初始化
        bucket[i] = 0;
    }
    p = L->next;
    while (p!=NULL){   //bucket赋值
        bucket[p->data] = p->data;
        p = p->next;
    }
    p = L->next;
    for(int i=0; i<=length;i++){
        if (bucket[i]!=0){  //重构线性表
            p->data = bucket[i];
            p = p->next;
        }
    }
    return 1;
}

