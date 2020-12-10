#include <cstdio>
#include <cstdlib>
#include "function.h"


int main(){
    ALGraph *G = nullptr;
    GraphList GList;
    VertexType value;
    int op=1; int flag;
    int LR;
    KeyType key_u,key_w;
    int pos_vex;
    int depth=0;
    VertexType V[100];
    KeyType VR[100][2];
    int i=0;
    char FileName[100],GraphName[100]={0}, locate_name[100]={0};
    setbuf(stdout, nullptr);
    while(op){
//        system("cls");
        menu();
        scanf("%d",&op);
        switch(op){
            case 1:
                if (Graph_Exist(G) == OK){
                    printf("this graph does exist\n");
                    getchar();getchar();
                    continue;
                }
                i = 0;
                printf("please input the data:");
                do {
                    scanf("%d%s",&V[i].key,V[i].others);
                } while(V[i++].key!=-1);
                i=0;
                do {
                    scanf("%d%d",&VR[i][0],&VR[i][1]);
                } while(VR[i++][0]!=-1);
                G = (ALGraph *)malloc(sizeof(ALGraph));
                flag = CreateGraph(*G,V,VR);
                if(flag==1) printf("construct succeeded!");
                else {
                    G = nullptr;
                    printf("construct failed");
                }
                getchar();getchar();
                break;
            case 2:
                int pos;
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    getchar();getchar();
                    continue;
                }
                else if ((pos = Locate_Graph(GList, GraphName))==0){
                    flag = DestroyGraph(*G);
                    G = nullptr;
                }
                else{
                    flag = Remove_Graph(GList, pos);
                    G = nullptr;
                }
                if (flag==OK) printf("destroy succeeded!\n");
                else printf("destroy failed!\n");
                getchar();getchar();
                break;
            case 3:
//                printf("\n----BiTreeDepth??\n");
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    getchar();getchar();
                    continue;
                }
                printf("please input the key:");
                scanf("%d", &key_u);
                pos_vex = LocateVex(*G, key_u);
                if (pos_vex != -1) printf("the position is : %d\n",pos_vex);
                else printf("this vex does not exist\n");
                getchar();getchar();
                break;
            case 4:
                printf("\n----putvex\n");
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    getchar();getchar();
                    continue;
                }
                printf("please input the key:");
                scanf("%d",&key_u);
                printf("please input the value(key,others):");
                scanf("%d%s",&value.key, value.others);
                flag = PutVex(*G,key_u,value);
                if (flag == OK) {
                    printf("put vex succeeded!");
                    change_root(GList, G, Locate_Graph(GList, GraphName));
                }
                else printf("put vex failed!");
                getchar();getchar();
                break;
            case 5:
                printf("\n----FirstAdjVex\n");
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    getchar();getchar();
                    continue;
                }
                printf("please input the key:");
                scanf("%d",&key_u);
                pos_vex = FirstAdjVex(*G,key_u);
                if (pos_vex == -1) printf("find fail!");
                else printf("the first adjacent vex's position is %d!", pos_vex);
                getchar();getchar();
                break;
            case 6:
                printf("\n----NextAdjVex??\n");
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    continue;
                }
                printf("please enter the key:");
                scanf("%d",&key_u);
                printf("please enter the vex you want to find the next vex's position:");
                scanf("%d", &key_w);
                pos_vex = NextAdjVex(*G, key_u, key_w);
                if (pos_vex == -1) printf("find fail!");
                else printf("the next adjacent vex's position is %d!", pos_vex);
                getchar();getchar();
                break;
            case 7:
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    continue;
                }
                printf("please enter the value:");
                scanf("%d%s",&value.key,value.others);
                flag = InsertVex(*G, value);
                if (flag==ERROR || flag == INFEASIBLE) printf("insert fail!");
                else printf("insert succeed!");
                getchar();getchar();
                break;
            case 8:
//                printf("\n----DeleteNode??\n");
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    continue;
                }
                printf("please enter the key:");
                scanf("%d",&key_u);
                flag = DeleteVex(*G,key_u);
                if (flag==ERROR || flag == INFEASIBLE) printf("DeleteVex fail!");
                else{
                    change_root(GList, G, Locate_Graph(GList, GraphName));
                    printf("DeleteVex success!");
                }
                getchar();getchar();
                break;
            case 9:
                if (Graph_Exist(G) == ERROR){
                    printf("this graph does not exist\n");
                    getchar();getchar();
                    continue;
                }
                printf("please input the arc(v,w):");
                scanf("%d%d",&key_u,&key_w);
                flag = InsertArc(*G, key_u, key_w);
                if (flag == ERROR) printf("insert failed!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                else printf("insert succeed!");
                getchar();getchar();
                break;
            case 10:
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    getchar();getchar();
                    continue;
                }
                printf("please input the arc(v,w):");
                scanf("%d%d",&key_u,&key_w);
                flag = DeleteArc(*G, key_u, key_w);
                if (flag == ERROR) printf("delete failed!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                else printf("delete succeed!");
                getchar();getchar();
                break;
            case 11:
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    getchar();getchar();
                    continue;
                }
                printf("\n----DFSTraverse\n");
                flag = DFSTraverse(*G,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 12:
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    getchar();getchar();
                    continue;
                }
                flag = BFSTraverse(*G,visit);
                if (flag == ERROR) printf("Tree is empty!");
                else if (flag == INFEASIBLE) printf("Tree doesn't exist!");
                getchar();getchar();
                break;
            case 13:
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph does not exist\n");
                    continue;
                }
                printf("\n----SaveGraph\n");
                printf("please input the root:");
                scanf("%s", FileName);
                if((flag = SaveGraph(*G, FileName))== OK ) printf("save succeeded\n");
                else printf("wrong!");
                getchar();getchar();
                break;
            case 14:
                if (Graph_Exist(G) == OK){
                    printf("this graph exists\n");
                    getchar();getchar();
                    continue;
                }

                printf("please input the root:");
                scanf("%s",FileName);
                G = (ALGraph *)malloc(sizeof(ALGraph));
                if((flag = LoadGraph(*G, FileName)) == OK ) printf("load succeeded\n");
                else printf("wrong!");
                getchar();getchar();
                break;
            case 15:
                flag = Graph_Exist(G);
                if (flag==INFEASIBLE) printf("Graph doesn't exist!");
                else printf("Graph exist!");
                getchar();getchar();
                break;
            case 16:
                if (Graph_Exist(G) == INFEASIBLE){
                    printf("this graph doesn't exist\n");
                    getchar();getchar();
                    continue;
                }
                Show_Adj(*G);
                getchar();getchar();
                break;
            case 17:
                printf("\n----Add_to_GraphList\n");
                printf("please input the name:");
                scanf("%s", GraphName);
                flag=Add_to_GraphList(GraphName, G, GList);
                if (flag==INFEASIBLE) printf("graph doesn't exists");
                if (flag==1) printf("add succeeded\n");
                else if (flag == ERROR)printf("add failed");
                getchar();getchar();
//                getchar();getchar();
                break;
            case 18:
                printf("----show list\n");
                Show_GraphList(GList);
                getchar();getchar();
                break;
            case 19:
                printf("switch_to_graph!\n");
                printf("please input the name:");
                scanf("%s", GraphName);
                flag = switch_to_graph(GList, GraphName, G);
                if (flag) printf("switch succeed");
                else
                    printf("switch failed");
                getchar();getchar();
                break;
            case 20:
//                printf("\n----RemoveList?????????\n");
                printf("please input the name:");
                scanf("%s", GraphName);
                flag = Remove_Graph(GList, Locate_Graph(GList, GraphName));
                if (flag) printf("remove succeed");
                else printf("remove failed");
                getchar();getchar();
                break;
            case 21:
                printf("please input the name of the graph:");
                scanf("%s", locate_name);
                if ((flag = Locate_Graph(GList, locate_name))) printf("the position is %d\n", flag);
                else if (flag == 0) printf("this graph doesn't exist\n");
                getchar();getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("????????????????\n");
}//end of main()