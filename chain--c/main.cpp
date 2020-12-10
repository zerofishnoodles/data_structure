#include "function.h"

/* Linear Table On Sequence Structure */
#include <cstdio>
#include <malloc.h>
#include <cstdlib>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

/*-----page 19 on textbook ---------*/
//status InitList(SqList& L);
//status DestroyList(SqList& L);
//status ClearList(SqList&L);
//status ListEmpty(SqList L);
//int ListLength(SqList L);
//status GetElem(SqList L,int i,ElemType& e);
//status LocateElem(SqListL,ElemType e); //简化过
//status PriorElem(SqListL,ElemTypecur,ElemType&pre_e);
//status NextElem(SqListL,ElemTypecur,ElemType&next_e);
//status ListInsert(SqList&L,inti,ElemType e);
//status ListDelete(SqList&L,int i,ElemType& e);
//status ListTraverse(SqList L);  //简化过
/*--------------------------------------------*/
int main(){
    LinkList L=NULL;  int op=1; int flag; ElemType pre;
    LISTS lists;
    setbuf(stdout, NULL);
    char FileName[200];
    char ListName[100];
    while(op){
//        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Chain Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList        2. DestroyList  \n");
        printf("    	  3. ClearList       4. ListEmpty\n");
        printf("    	  5. ListLength      6. GetElem   \n");
        printf("    	  7. LocateElem      8. PriorElem\n");
        printf("    	  9. NextElem        10. ListInsert\n");
        printf("    	  11. ListDelete     12. ListTraverse\n");
        printf("    	  13. SaveList       14. LoadList\n");
        printf("          15. Add_to_List    16. RemoveList\n");
        printf("          17. LocateList     18. ShowLists\n");
        printf("    	  19. Switch_to_List    20. Get_Greatest \n");
        printf("          21. Bucket_Sort     0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("\n----IntiList功能待实现！\n");
                if(InitList(L)==OK) printf("线性表创建成功！\n");
                else printf("线性表创建失败！\n");
                getchar();getchar();
                break;
            case 2:
                printf("\n----DestroyList功能待实现！\n");
                if (LocateList(lists, ListName)==0) flag = DestroyList(L);
                else{
                    flag = DestroyList(L);
                    RemoveList(lists, ListName);
                }
                if (flag) printf("线性表销毁成功！\n");
                else printf("线性表销毁失败！\n");
                getchar();getchar();
                break;
            case 3:
                printf("\n----ClearList功能待实现！\n");
                if (ClearList(L)==OK) printf("线性表清空成功！\n");
                else printf("线性表清空失败！\n");
                getchar();getchar();
                break;
            case 4:
                printf("\n----ListEmpty功能待实现！\n");
                if (ListEmpty(L)==INFEASIBLE) printf("线性表不存在！\n");
                else if (ListEmpty(L) == FALSE)printf("线性表不为空！\n");
                else printf("线性表为空！\n");
                getchar();getchar();
                break;
            case 5:
                printf("\n----ListLength功能待实现！\n");
                if (ListLength(L)==INFEASIBLE) printf("线性表不存在！\n");
                else printf("线性表长度为%d\n", ListLength(L));
                getchar();getchar();
                break;
            case 6:
                printf("\n----GetElem功能待实现！\n");
                int i;
                printf("请输入要获取的元素位置：");
                scanf("%d", &i);
                ElemType e;
                if ((flag = GetElem(L, i ,e))==OK) printf("元素值为：%d\n", e);
                else if (flag == ERROR) printf("该位置不合法！\n");
                else printf("该线性表不存在！\n");
                getchar();getchar();
                break;
            case 7:
                printf("\n----LocateElem功能待实现！\n");
                printf("请输入要确定位置的元素：");
                scanf("%d",&e);
                flag = LocateElem(L, e);
                if (flag>0) printf("元素位置为：%d\n", flag);
                else if (flag == ERROR) printf("该元素不存在！\n");
                else printf("该线性表不存在！\n");
                getchar();getchar();
                break;
            case 8:
                printf("\n----PriorElem功能待实现！\n");
                printf("请输入需要找到前驱的元素：");
                scanf("%d", &e);
                if ((flag = PriorElem(L, e ,pre))==OK) printf("元素前驱为：%d\n", pre);
                else if (flag == ERROR) printf("该元素没有前驱！\n");
                else printf("该线性表不存在！\n");
                getchar();getchar();
                break;
            case 9:
                printf("\n----NextElem功能待实现！\n");
                printf("请输入需要找到后继的元素：");
                scanf("%d", &e);
                if ((flag = NextElem(L, e ,pre))==OK) printf("元素后继为：%d\n", pre);
                else if (flag == ERROR) printf("该元素没有后继！\n");
                else printf("该线性表不存在！\n");
                getchar();getchar();
                break;
            case 10:
                printf("\n----ListInsert功能待实现！\n");
                printf("请输入要添加的位置和元素（以一个空格隔开）：");
                scanf("%d%d", &i, &e);
                if ((flag = ListInsert(L, i ,e))==OK) printf("元素插入成功\n");
                else if (flag == ERROR) printf("该位置不正确\n");
                else printf("该线性表不存在！\n");
                getchar();getchar();
                break;
            case 11:
                printf("\n----ListDelete功能待实现！\n");
                printf("请输入要删除的位置：");
                scanf("%d", &i);
                if ((flag = ListDelete(L, i ,e))==OK) printf("该元素为：%d\n", e);
                else if (flag == ERROR) printf("删除位置不正确！\n");
                else printf("该线性表不存在！\n");
                getchar();getchar();
                break;
            case 12:
                //printf("\n----ListTraverse功能待实现！\n");
                if(ListTraverse(L)==INFEASIBLE) printf("线性表不存在！\n");

                getchar();getchar();
                break;
            case 13:
                printf("\n----SaveList功能待实现！\n");
                printf("请输入文件存储路径：");
                scanf("%s", FileName);
                if((flag = SaveList(L, FileName))== OK ) printf("存储成功！\n");
                else printf("线性表不存在");
                getchar();getchar();
                break;
            case 14:
                printf("\n----LoadList功能待实现！\n");
                printf("请输入文件路径：");
                scanf("%s", FileName);
                if((flag = LoadList(L, FileName)) == OK ) printf("加载成功！\n");
                else printf("线性表已存在");
                getchar();getchar();
                break;
            case 15:
                printf("\n----Add_to_List功能待实现！\n");
                printf("请输入列表名字：");
                scanf("%s", ListName);
                flag=Add_to_Lists(lists, ListName, L);
                if (flag==INFEASIBLE) printf("线性表不存在！");
                if (flag==1) printf("添加成功！\n");
                else if (flag == 0)printf("该线性表名字已存在！");
                getchar();getchar();
                break;
            case 16:
                printf("\n----RemoveList功能待实现！\n");
                printf("请输入要删除的线性表名字：");
                scanf("%s", ListName);
                flag = RemoveList(lists, ListName);
                if (flag) printf("删除成功！");
                else printf("删除失败！");
                getchar();getchar();
                break;
            case 17:
                printf("\n----LocateList功能待实现！\n");
                printf("请输入要定位的List的名字");
                scanf("%s", ListName);
                if ((flag = LocateList(lists, ListName))) printf("位置为%d\n", flag);
                else if (flag == 0) printf("该List不存在\n");
                getchar();getchar();
                break;
            case 18:
                printf("----show list\n");
                showlist(lists);
                getchar();getchar();
                break;
            case 19:
                printf("------switch to list");
                printf("请输入要切换的List的名字");
                scanf("%s", ListName);
                flag = Switch_to_List(lists, ListName, L);
                if (flag) printf("加载成功");
                else
                    printf("没有这个线性表！");
                getchar();getchar();
                break;
            case 20:
                printf("get_greatest");
                flag = Get_Greatest(L);
                printf("最大值为：%d", flag);
                getchar();getchar();
                break;
            case 21:
                printf("bucket sort");
                flag = Bucket_Sort(L);
                if (flag) printf("排序成功！");
                getchar();getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/





