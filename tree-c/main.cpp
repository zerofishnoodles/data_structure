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
                printf("请输入先序序列(key,others)：");
                do {
                    scanf("%d%s",&definition[i].key,definition[i].others);
                } while (definition[i++].key!=-1);
                flag = CreateBiTree(Tree, definition);
                if(flag==1) printf("创建成功！");
                else printf("创建失败！");
                getchar();getchar();
                break;
            case 2:
                int pos;
                if ((pos = locate_tree(Trees, TreeName))==0) flag = DestroyBiTree(Tree);
                else{
                    flag = remove_tree(Trees, pos);
                    Tree = nullptr;
                }
                if (flag==OK) printf("销毁成功！\n");
                else printf("销毁失败！\n");
                getchar();getchar();
                break;
            case 3:
                printf("\n----BiTreeDepth！\n");
                depth = BiTreeDepth(Tree);
                if (depth) printf("深度为：%d\n",depth);
                else printf("树不存在！\n");
                getchar();getchar();
                break;
            case 4:
                printf("\n----LocateNode！\n");
                printf("please input the key:");
                scanf("%d",&e);
                result = LocateNode(Tree,e);
                if (result!= nullptr) printf("%s",result->data.others);
                else printf("this node does not exist!");
                getchar();getchar();
                break;
            case 5:
                printf("\n----Assign！\n");
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
                printf("\n----GetSibling！\n");
                printf("please enter the key:");
                scanf("%d",&e);
                result = GetSibling(Tree,e);
                if (result!= nullptr) printf("%d %s",result->data.key,result->data.others);
                else printf("the sibling does not exist!");
                getchar();getchar();
                break;
            case 7:
                printf("\n----InsertNode！\n");
                printf("please enter the key,right(1)/left(0)/root(-1):");
                scanf("%d%d",&e,&LR);
                printf("please enter the value：");
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
                printf("\n----DeleteNode！\n");
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
                printf("\n----PreOrderTraverse！\n");
                flag = PreOrderTraverse(Tree,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 10:
                printf("\n----InOrderTraverse！\n");
                flag = InOrderTraverse(Tree,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 11:
                printf("\n----PostOrderTraverse！\n");
//                printf("\n----InOrderTraverse！\n");
                flag = PostOrderTraverse(Tree,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 12:
                printf("\n----LevelOrderTraverse！\n");
                flag = LevelOrderTraverse(Tree,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 13:
                printf("\n----SaveList功能待实现！\n");
                printf("请输入文件存储路径：");
                scanf("%s", FileName);
                if((flag = SaveBiTree(Tree, FileName))== OK ) printf("存储成功！\n");
                else printf("wrong!");
                getchar();getchar();
                break;
            case 14:
                printf("\n----LoadList功能待实现！\n");
                printf("请输入文件路径：");
                scanf("%s", FileName);
                num_create = 0;
                if((flag = LoadBiTree(Tree, FileName)) == OK ) printf("加载成功！\n");
                else printf("wrong！");
                getchar();getchar();
                break;
            case 15:
                printf("\n----BiTreeExist！\n");
                flag = BiTreeExist(Tree);
                if (flag==INFEASIBLE) printf("Tree doesn't exist!");
                else printf("Tree exist!");
                getchar();getchar();
                break;
            case 16:
                printf("\n----ClearBiTree！\n");
                flag = ClearBiTree(Tree);
                if (flag==INFEASIBLE) printf("Clear fail!");
                else {
                    change_root(Trees, Tree, locate_tree(Trees, TreeName));
                    printf("Clear Succeed!");
                }
                getchar();getchar();
                break;
            case 17:
                printf("\n----Add_to_TreeList！\n");
                printf("please input the name：");
                scanf("%s", TreeName);
                flag=Add_to_TreeList(TreeName, Tree, Trees);
                if (flag==INFEASIBLE) printf("二叉树不存在！");
                if (flag==1) printf("添加成功！\n");
                else if (flag == ERROR)printf("该二叉树名字已存在！");
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
                printf("请输入要切换的Tree的名字");
                scanf("%s", TreeName);
                flag = switch_to_tree(Trees, TreeName, Tree);
                if (flag) printf("加载成功");
                else
                    printf("没有这个树！");
                getchar();getchar();
                break;
            case 20:
//                printf("\n----RemoveList功能待实现！\n");
                printf("请输入要删除的tree名字：");
                scanf("%s", TreeName);
                flag = remove_tree(Trees, locate_tree(Trees, TreeName));
                if (flag) printf("删除成功！");
                else printf("删除失败！");
                getchar();getchar();
                break;
            case 21:
                printf("请输入要定位的tree的名字");
                scanf("%s", locate_name);
                if ((flag = locate_tree(Trees, locate_name))) printf("位置为%d\n", flag);
                else if (flag == 0) printf("该Tree不存在\n");
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
    printf("欢迎下次再使用本系统！\n");
}//end of main()