#include <cstdio>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct TElemType{
    KeyType  key;
    char others[20];
} TElemType; //二叉树结点类型定义


typedef struct BiTNode{  //二叉链表结点的定义
    TElemType  data;
    struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct TreeList{
    typedef struct tree{
        char name[100];
        BiTree T;
    }Treeinlist;
    Treeinlist elem[100];
    int length=0;
    int listsize = 100;
}TreeList;

status test(TElemType definition[]);
status CreateBiTree(BiTree &T,TElemType definition[]);
status ClearBiTree(BiTree &T);
status DestroyBiTree(BiTree &T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
void delete_node(BiTree &parent, BiTree p, int LR);
status DeleteNode(BiTree &T,KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);
void visit(BiTree p);
status BiTreeExist(BiTree T);
status ClearBiTree(BiTree &T);
status Add_to_TreeList(char TreeName[], BiTree &T, TreeList &TL);
void show_tree_list(TreeList TL);
status switch_to_tree(TreeList TL, char TreeName[], BiTree &T);
status remove_tree(TreeList &TL, int pos);
int locate_tree(TreeList TL, char TreeName[]);
status BiTreeEmpty(BiTree T);
void change_root(TreeList &TL, BiTree T, int pos);