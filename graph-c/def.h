#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义


typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号
    struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode{				//头结点及其数组类型定义
    VertexType data;       	//顶点信息
    ArcNode *firstarc;      	 //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;

typedef struct GraphList{
    typedef struct{
        ALGraph *G;
        char name[100];
    }GraphElem;
    GraphElem elem[100]={};
    int length = 0;
    int listsize = 100;
}GraphList;

void menu();
status match(VertexType V[], int key);
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status test_V(VertexType V[]);
status test_VR(KeyType VR[][2], VertexType V[]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
int get_next_pos(ALGraph G, int pos_v, int pos_w);
int get_first_pos(ALGraph G, int pos_v);
void DFS(ALGraph G, int pos_v, void (*visit)(VertexType));
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status Locate_Graph(GraphList GList, char GraphName[]);
status Remove_Graph(GraphList &GList, int pos);
void visit(VertexType v);
status Graph_Exist(ALGraph *G);
void change_root(GraphList &GList, ALGraph *G, int pos);
status Add_to_GraphList(char GraphName[], ALGraph* &G, GraphList &GList);
void Show_GraphList(GraphList GList);
status switch_to_graph(GraphList TL, char GraphName[], ALGraph* &G);
status Show_Adj(ALGraph G);