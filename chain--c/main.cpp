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
typedef int ElemType; //����Ԫ�����Ͷ���

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
//status LocateElem(SqListL,ElemType e); //�򻯹�
//status PriorElem(SqListL,ElemTypecur,ElemType&pre_e);
//status NextElem(SqListL,ElemTypecur,ElemType&next_e);
//status ListInsert(SqList&L,inti,ElemType e);
//status ListDelete(SqList&L,int i,ElemType& e);
//status ListTraverse(SqList L);  //�򻯹�
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
        printf("    ��ѡ����Ĳ���[0~20]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("\n----IntiList���ܴ�ʵ�֣�\n");
                if(InitList(L)==OK) printf("���Ա����ɹ���\n");
                else printf("���Ա���ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 2:
                printf("\n----DestroyList���ܴ�ʵ�֣�\n");
                if (LocateList(lists, ListName)==0) flag = DestroyList(L);
                else{
                    flag = DestroyList(L);
                    RemoveList(lists, ListName);
                }
                if (flag) printf("���Ա����ٳɹ���\n");
                else printf("���Ա�����ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 3:
                printf("\n----ClearList���ܴ�ʵ�֣�\n");
                if (ClearList(L)==OK) printf("���Ա���ճɹ���\n");
                else printf("���Ա����ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 4:
                printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
                if (ListEmpty(L)==INFEASIBLE) printf("���Ա����ڣ�\n");
                else if (ListEmpty(L) == FALSE)printf("���Ա�Ϊ�գ�\n");
                else printf("���Ա�Ϊ�գ�\n");
                getchar();getchar();
                break;
            case 5:
                printf("\n----ListLength���ܴ�ʵ�֣�\n");
                if (ListLength(L)==INFEASIBLE) printf("���Ա����ڣ�\n");
                else printf("���Ա���Ϊ%d\n", ListLength(L));
                getchar();getchar();
                break;
            case 6:
                printf("\n----GetElem���ܴ�ʵ�֣�\n");
                int i;
                printf("������Ҫ��ȡ��Ԫ��λ�ã�");
                scanf("%d", &i);
                ElemType e;
                if ((flag = GetElem(L, i ,e))==OK) printf("Ԫ��ֵΪ��%d\n", e);
                else if (flag == ERROR) printf("��λ�ò��Ϸ���\n");
                else printf("�����Ա����ڣ�\n");
                getchar();getchar();
                break;
            case 7:
                printf("\n----LocateElem���ܴ�ʵ�֣�\n");
                printf("������Ҫȷ��λ�õ�Ԫ�أ�");
                scanf("%d",&e);
                flag = LocateElem(L, e);
                if (flag>0) printf("Ԫ��λ��Ϊ��%d\n", flag);
                else if (flag == ERROR) printf("��Ԫ�ز����ڣ�\n");
                else printf("�����Ա����ڣ�\n");
                getchar();getchar();
                break;
            case 8:
                printf("\n----PriorElem���ܴ�ʵ�֣�\n");
                printf("��������Ҫ�ҵ�ǰ����Ԫ�أ�");
                scanf("%d", &e);
                if ((flag = PriorElem(L, e ,pre))==OK) printf("Ԫ��ǰ��Ϊ��%d\n", pre);
                else if (flag == ERROR) printf("��Ԫ��û��ǰ����\n");
                else printf("�����Ա����ڣ�\n");
                getchar();getchar();
                break;
            case 9:
                printf("\n----NextElem���ܴ�ʵ�֣�\n");
                printf("��������Ҫ�ҵ���̵�Ԫ�أ�");
                scanf("%d", &e);
                if ((flag = NextElem(L, e ,pre))==OK) printf("Ԫ�غ��Ϊ��%d\n", pre);
                else if (flag == ERROR) printf("��Ԫ��û�к�̣�\n");
                else printf("�����Ա����ڣ�\n");
                getchar();getchar();
                break;
            case 10:
                printf("\n----ListInsert���ܴ�ʵ�֣�\n");
                printf("������Ҫ��ӵ�λ�ú�Ԫ�أ���һ���ո��������");
                scanf("%d%d", &i, &e);
                if ((flag = ListInsert(L, i ,e))==OK) printf("Ԫ�ز���ɹ�\n");
                else if (flag == ERROR) printf("��λ�ò���ȷ\n");
                else printf("�����Ա����ڣ�\n");
                getchar();getchar();
                break;
            case 11:
                printf("\n----ListDelete���ܴ�ʵ�֣�\n");
                printf("������Ҫɾ����λ�ã�");
                scanf("%d", &i);
                if ((flag = ListDelete(L, i ,e))==OK) printf("��Ԫ��Ϊ��%d\n", e);
                else if (flag == ERROR) printf("ɾ��λ�ò���ȷ��\n");
                else printf("�����Ա����ڣ�\n");
                getchar();getchar();
                break;
            case 12:
                //printf("\n----ListTraverse���ܴ�ʵ�֣�\n");
                if(ListTraverse(L)==INFEASIBLE) printf("���Ա����ڣ�\n");

                getchar();getchar();
                break;
            case 13:
                printf("\n----SaveList���ܴ�ʵ�֣�\n");
                printf("�������ļ��洢·����");
                scanf("%s", FileName);
                if((flag = SaveList(L, FileName))== OK ) printf("�洢�ɹ���\n");
                else printf("���Ա�����");
                getchar();getchar();
                break;
            case 14:
                printf("\n----LoadList���ܴ�ʵ�֣�\n");
                printf("�������ļ�·����");
                scanf("%s", FileName);
                if((flag = LoadList(L, FileName)) == OK ) printf("���سɹ���\n");
                else printf("���Ա��Ѵ���");
                getchar();getchar();
                break;
            case 15:
                printf("\n----Add_to_List���ܴ�ʵ�֣�\n");
                printf("�������б����֣�");
                scanf("%s", ListName);
                flag=Add_to_Lists(lists, ListName, L);
                if (flag==INFEASIBLE) printf("���Ա����ڣ�");
                if (flag==1) printf("��ӳɹ���\n");
                else if (flag == 0)printf("�����Ա������Ѵ��ڣ�");
                getchar();getchar();
                break;
            case 16:
                printf("\n----RemoveList���ܴ�ʵ�֣�\n");
                printf("������Ҫɾ�������Ա����֣�");
                scanf("%s", ListName);
                flag = RemoveList(lists, ListName);
                if (flag) printf("ɾ���ɹ���");
                else printf("ɾ��ʧ�ܣ�");
                getchar();getchar();
                break;
            case 17:
                printf("\n----LocateList���ܴ�ʵ�֣�\n");
                printf("������Ҫ��λ��List������");
                scanf("%s", ListName);
                if ((flag = LocateList(lists, ListName))) printf("λ��Ϊ%d\n", flag);
                else if (flag == 0) printf("��List������\n");
                getchar();getchar();
                break;
            case 18:
                printf("----show list\n");
                showlist(lists);
                getchar();getchar();
                break;
            case 19:
                printf("------switch to list");
                printf("������Ҫ�л���List������");
                scanf("%s", ListName);
                flag = Switch_to_List(lists, ListName, L);
                if (flag) printf("���سɹ�");
                else
                    printf("û��������Ա�");
                getchar();getchar();
                break;
            case 20:
                printf("get_greatest");
                flag = Get_Greatest(L);
                printf("���ֵΪ��%d", flag);
                getchar();getchar();
                break;
            case 21:
                printf("bucket sort");
                flag = Bucket_Sort(L);
                if (flag) printf("����ɹ���");
                getchar();getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
/*--------page 23 on textbook --------------------*/





