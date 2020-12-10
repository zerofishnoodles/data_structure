#include <cstdio>
#include <cstdlib>
#include "function.h"


int main(){
    BiTree Tree= nullptr,result= nullptr;
    int op=1; int flag;
    int LR;
    int depth=0;
    KeyType e;
    TElemType value;
    TElemType definition[100];
    char FileName[100],TreeName[100]={0}, locate_name[100]={0};
    TreeList Trees;
    int i=0;
    setbuf(stdout, nullptr);
    while(op){
//        system("cls");
        menu();
        scanf("%d",&op);
        switch(op){
            case 1:
                i=0;
                num_create = 0;
                printf("��������������(key,others)��");
                do {
                    scanf("%d%s",&definition[i].key,definition[i].others);
                } while (definition[i++].key!=-1);
                flag = CreateBiTree(Tree, definition);
                if(flag==1) printf("�����ɹ���");
                else printf("����ʧ�ܣ�");
                getchar();getchar();
                break;
            case 2:
                int pos;
                if ((pos = locate_tree(Trees, TreeName))==0) flag = DestroyBiTree(Tree);
                else{
                    flag = remove_tree(Trees, pos);
                    Tree = nullptr;
                }
                if (flag==OK) printf("���ٳɹ���\n");
                else printf("����ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 3:
                printf("\n----BiTreeDepth��\n");
                depth = BiTreeDepth(Tree);
                if (depth) printf("���Ϊ��%d\n",depth);
                else printf("�������ڣ�\n");
                getchar();getchar();
                break;
            case 4:
                printf("\n----LocateNode��\n");
                printf("please input the key:");
                scanf("%d",&e);
                result = LocateNode(Tree,e);
                if (result!= nullptr) printf("%s",result->data.others);
                else printf("this node does not exist!");
                getchar();getchar();
                break;
            case 5:
                printf("\n----Assign��\n");
                printf("please input the key:");
                scanf("%d",&e);
                printf("please input the value:");
                scanf("%d%s",&value.key,value.others);
                flag = Assign(Tree,e,value);
                if (flag==ERROR || flag == INFEASIBLE) printf("Assign fail!");
                else {
                    change_root(Trees, Tree, locate_tree(Trees, TreeName));
                    printf("Assign success!");
                }
                getchar();getchar();
                break;
            case 6:
                printf("\n----GetSibling��\n");
                printf("please enter the key:");
                scanf("%d",&e);
                result = GetSibling(Tree,e);
                if (result!= nullptr) printf("%d %s",result->data.key,result->data.others);
                else printf("the sibling does not exist!");
                getchar();getchar();
                break;
            case 7:
                printf("\n----InsertNode��\n");
                printf("please enter the key,right(1)/left(0)/root(-1):");
                scanf("%d%d",&e,&LR);
                printf("please enter the value��");
                scanf("%d%s",&value.key,value.others);
                flag = InsertNode(Tree,e,LR,value);
                if (flag==ERROR || flag == INFEASIBLE) printf("insert fail!");
                else {
                    change_root(Trees, Tree, locate_tree(Trees, TreeName));
                    printf("insert success!");
                }
                getchar();getchar();getchar();
                break;
            case 8:
                printf("\n----DeleteNode��\n");
                printf("please enter the key:");
                scanf("%d",&e);
                flag = DeleteNode(Tree,e);
                if (flag==ERROR || flag == INFEASIBLE) printf("DeleteNode fail!");
                else{
                    change_root(Trees, Tree, locate_tree(Trees, TreeName));
                    printf("DeleteNode success!");
                }
                getchar();getchar();
                break;
            case 9:
                printf("\n----PreOrderTraverse��\n");
                flag = PreOrderTraverse(Tree,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 10:
                printf("\n----InOrderTraverse��\n");
                flag = InOrderTraverse(Tree,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 11:
                printf("\n----PostOrderTraverse��\n");
//                printf("\n----InOrderTraverse��\n");
                flag = PostOrderTraverse(Tree,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 12:
                printf("\n----LevelOrderTraverse��\n");
                flag = LevelOrderTraverse(Tree,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 13:
                printf("\n----SaveList���ܴ�ʵ�֣�\n");
                printf("�������ļ��洢·����");
                scanf("%s", FileName);
                if((flag = SaveBiTree(Tree, FileName))== OK ) printf("�洢�ɹ���\n");
                else printf("wrong!");
                getchar();getchar();
                break;
            case 14:
                printf("\n----LoadList���ܴ�ʵ�֣�\n");
                printf("�������ļ�·����");
                scanf("%s", FileName);
                num_create = 0;
                if((flag = LoadBiTree(Tree, FileName)) == OK ) printf("���سɹ���\n");
                else printf("wrong��");
                getchar();getchar();
                break;
            case 15:
                printf("\n----BiTreeExist��\n");
                flag = BiTreeExist(Tree);
                if (flag==INFEASIBLE) printf("Tree doesn't exist!");
                else printf("Tree exist!");
                getchar();getchar();
                break;
            case 16:
                printf("\n----ClearBiTree��\n");
                flag = ClearBiTree(Tree);
                if (flag==INFEASIBLE) printf("Clear fail!");
                else {
                    change_root(Trees, Tree, locate_tree(Trees, TreeName));
                    printf("Clear Succeed!");
                }
                getchar();getchar();
                break;
            case 17:
                printf("\n----Add_to_TreeList��\n");
                printf("please input the name��");
                scanf("%s", TreeName);
                flag=Add_to_TreeList(TreeName, Tree, Trees);
                if (flag==INFEASIBLE) printf("�����������ڣ�");
                if (flag==1) printf("��ӳɹ���\n");
                else if (flag == ERROR)printf("�ö����������Ѵ��ڣ�");
                getchar();getchar();
//                getchar();getchar();
                break;
            case 18:
                printf("----show list\n");
                show_tree_list(Trees);
                getchar();getchar();
                break;
            case 19:
                printf("switch_to_tree!");
                printf("������Ҫ�л���Tree������");
                scanf("%s", TreeName);
                flag = switch_to_tree(Trees, TreeName, Tree);
                if (flag) printf("���سɹ�");
                else
                    printf("û���������");
                getchar();getchar();
                break;
            case 20:
//                printf("\n----RemoveList���ܴ�ʵ�֣�\n");
                printf("������Ҫɾ����tree���֣�");
                scanf("%s", TreeName);
                flag = remove_tree(Trees, locate_tree(Trees, TreeName));
                if (flag) printf("ɾ���ɹ���");
                else printf("ɾ��ʧ�ܣ�");
                getchar();getchar();
                break;
            case 21:
                printf("������Ҫ��λ��tree������");
                scanf("%s", locate_name);
                if ((flag = locate_tree(Trees, locate_name))) printf("λ��Ϊ%d\n", flag);
                else if (flag == 0) printf("��Tree������\n");
                getchar();getchar();
                break;
            case 22:
                flag = BiTreeEmpty(Tree);
                if (flag == ERROR) printf("tree is not empty");
                else if (flag == OK) printf("tree is empty");
                else if (flag == INFEASIBLE) printf("tree does not exist");
                getchar();getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()