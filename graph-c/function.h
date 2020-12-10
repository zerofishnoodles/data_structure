#include "def.h"
#include "cstring"

void menu()
{
    printf("\n\n");
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. CreateGraph        2. DestroyGraph  \n");
    printf("    	  3. LocateVex       4. PutVex\n");
    printf("    	  5. FirstAdjVex      6. NextAdjVex   \n");
    printf("    	  7. InsertVex      8. DeleteVex\n");
    printf("    	  9. InsertArc        10. DeleteArc\n");
    printf("    	  11. DFSTraverse     12. BFSTraverse\n");
    printf("    	  13. SaveGraph       14. LoadGraph\n");
    printf("          15. Graph_Exist    16. Show_Adj\n");
    printf("          17. Add_to_GraphList     18. Show_GraphList\n");
    printf("    	  19. switch_to_graph       20. Remove_Graph    \n");
    printf("          21.Locate_Graph        0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    请输入操作[0~21]:");
}

status match(VertexType V[], int key)
{
    int i=0;
    while (V[i].key != -1){
        if (key == V[i].key)  return OK;
        i++;
    }
    return  ERROR;
}
status test_V(VertexType V[]){
    int i=0;
    int keys[100]={0};
    while(V[i].key != -1){
        keys[V[i].key]++;
        if(keys[V[i].key]>1) return ERROR;
        i++;
        if (i>20) return ERROR;
    }
    return OK;
}

status test_VR(KeyType VR[][2], VertexType V[])
{
    int i=0;
    int keys[100][100]={0};
    while(VR[i][0] != -1 && VR[i][1] != -1){
        if(VR[i][0]==VR[i][1]) return ERROR;
        if (match(V, VR[i][0]) == ERROR) return ERROR;
        if (match(V, VR[i][1]) == ERROR) return ERROR;
        keys[VR[i][0]][VR[i][1]]++;
        keys[VR[i][1]][VR[i][0]]++;
        if(keys[VR[i][0]][VR[i][1]] > 1 || keys[VR[i][1]][VR[i][0]]>1) return ERROR;
        i++;
    }
    return OK;
}



status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
//5 线性表 8 集合 7 二叉树 6 无向图 -1 nil 5 6 5 7 6 7 7 8 -1 -1
//5 线性表 7 集合 7 二叉树 6 无向图 -1 nil 5 6 5 7 6 7 10 8 -1 -1
//5 线性表 8 集合 7 二叉树 6 无向图 -1 nil 5 6 5 7 6 7 10 8 -1 -1
//1 G 2 G2 3 G3 4 G4 5 G5 6 G6 7 G7 8 G8 9 G9 10 G10 11 G11 12 G12 13 G13 14 G14 15 G15 16 G16 17 G17 18 G18 19 G19 20 G20 21 G21 -1 nil -1 -1
//1 G 2 G2 3 G3 4 G4 5 G5 6 G6 7 G7 8 G8 9 G9 10 G10 11 G11 12 G12 13 G13 14 G14 15 G15 16 G16 17 G17 18 G18 19 G19 20 G20 -1 nil -1 -1
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 函数首先检测图的结点的关键字是否有重复和溢出，接着检测输入的边序列是否正确，正确需要有以下几方面要求：
     * 1. 边不能重复出现
     * 2. 该边的两个端点存在于结点序列中
     * 检测完毕之后首先添加结点，再添加边，需要注意的是，添加边的时候由于是无向图，所以与该边相关的两个节点都要建立弧，建立的方式也很简单，直接对单链表进行头插即可
     */
    if(test_V(V)==ERROR) return ERROR;
    if(test_VR(VR, V)==ERROR) return ERROR;
    int i=0;
    G.vexnum = 0;  // init
    G.arcnum = 0;
    int keys[100]={0};  // record the position of the key
    while(V[i].key!=-1){  // add nodes
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = nullptr;
        G.vexnum++;
        keys[V[i].key]= i;
        i++;
    }
    i=0;
    while(VR[i][0] != -1 && VR[i][1] != -1){  //add edges
        ArcNode *temp;
        temp = (ArcNode *)malloc(sizeof(ArcNode));
        temp->adjvex = keys[VR[i][1]];
        temp->nextarc = nullptr;
        if (G.vertices[keys[VR[i][0]]].firstarc != nullptr){
            ArcNode *temp1;
            temp1 = G.vertices[keys[VR[i][0]]].firstarc;
            G.vertices[keys[VR[i][0]]].firstarc = temp;
            temp->nextarc = temp1;
        }
        else G.vertices[keys[VR[i][0]]].firstarc = temp;

        temp = (ArcNode *)malloc(sizeof(ArcNode));  // undirected graph, two edges
        temp->adjvex = keys[VR[i][0]];
        temp->nextarc = nullptr;
        if (G.vertices[keys[VR[i][1]]].firstarc != nullptr){
            ArcNode *temp1;
            temp1 = G.vertices[keys[VR[i][1]]].firstarc;
            G.vertices[keys[VR[i][1]]].firstarc = temp;
            temp->nextarc = temp1;
        }
        else G.vertices[keys[VR[i][1]]].firstarc = temp;

        G.arcnum++;
        i++;
    }
    return OK;

    /********** End **********/
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G*/
{
    /**
     * 函数通过依次将与当前节点连接的表结点存到数组中再统一释放空间来达到销毁图的目的
     */
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i=0;i<G.vexnum;i++){
        ArcNode *temp;
        ArcNode *st[100];
        int top = 0;
        temp = G.vertices[i].firstarc;
        while (temp != nullptr){
            st[top++] = temp;  // enter the stack
            temp = temp->nextarc;
        }
        for (int j = 0; j < top; ++j) {  // free the space
            free(st[j]);
        }
        G.vertices[i].firstarc = nullptr;
    }
    G.vexnum = 0;  // renumber the vex and arc
    G.arcnum = 0;
    return OK;
    /********** End **********/
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 通过循环进行匹配找到要查找的结点位序
     */
    for (int i =0 ;i<G.vexnum;i++){
        if (u == G.vertices[i].data.key) return i;
    }
    return -1;

    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 先通过循环记录出现的key值，再通过循环进行匹配查找，查找成功的条件为：1. 查找成功，keys不重复 2. 查找成功，要替换的和被替换的相等
     */
    KeyType keys[100]={0};
    for (int i=0;i<G.vexnum;i++){  // record keys
        keys[G.vertices[i].data.key] = 1;
    }
    for (int i=0;i<G.vexnum;i++){ // 1. 查找成功，keys不重复 2. 查找成功，要替换的和被替换的相等
        if (u == G.vertices[i].data.key && (keys[value.key] == 0 || u == value.key)){
            G.vertices[i].data = value;
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 通过循环对所要查找的顶点进行匹配，匹配成功返回第一邻接点的位序。
     */
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].firstarc != nullptr && u == G.vertices[i].data.key) return G.vertices[i].firstarc->adjvex;
    }
    return -1;

    /********** End **********/
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 首先通过一层循环找到当前顶点，再通过一层循环遍历当前结点的邻接结点，找到查找的相对位置。
     */
    for (int i = 0; i < G.vexnum; ++i) {
        if (v == G.vertices[i].data.key){  //match vertex
            ArcNode *temp;
            temp = G.vertices[i].firstarc;
            while (temp != nullptr){
                if (G.vertices[temp->adjvex].data.key == w){  // match neighbour
                    if (temp->nextarc!= nullptr) return temp->nextarc->adjvex;
                    return -1;
                }
                temp = temp->nextarc;
            }
        }
    }
    return -1;

    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 首先通过一层循环记录出现的key值，接着从尾部加入符合条件的顶点，并更改相关参数
     */
    KeyType keys[100]={0};
    for (int i=0;i<G.vexnum;i++){  // record keys
        keys[G.vertices[i].data.key] = 1;
    }
    if (keys[v.key] == 0){
        if (G.vexnum+1>MAX_VERTEX_NUM) return ERROR;
        G.vertices[G.vexnum].data = v;
        G.vertices[G.vexnum].firstarc = nullptr;
        G.vexnum++;
        return OK;
    }
    return ERROR;


    /********** End **********/
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 首先通过一层循环删除对应的顶点并更新参数
     * 接着删除与之相连的边，主要操作为利用循环对整个邻接表进行遍历，并进行判断，总共分为两种情况：
     * 1. 删除的表结点为当前结点的第一个邻接结点
     * 2. 删除的表结点为当前结点其他邻接点
     * 第一种情况又要分为有一个邻接结点还是多个邻接结点，这样才能适应各种情况。
     * 最后要对表结点所记的位序进行重新编号
     */
    int pos=0;
    int flag=0;
    for (pos = 0; pos < G.vexnum; ++pos) {
        if (v == G.vertices[pos].data.key){  // remove the vertex
            if (G.vertices[pos].firstarc == nullptr) flag = 1;
            for (int j = pos; j < G.vexnum-1; ++j) {
                G.vertices[j] = G.vertices[j+1];
            }
            G.vexnum--;
            break;
        }
    }

    int edge_num = 0;
    for (int i=0;i<G.vexnum;i++){  //remove the edge
        ArcNode *del, *pre;
        pre = G.vertices[i].firstarc;
        del = pre;
        if (G.vertices[i].firstarc!= nullptr && G.vertices[i].firstarc->adjvex == pos){  // remove the first arc
            if (del->nextarc != nullptr){  // if the next arc does exist
                G.vertices[i].firstarc = del->nextarc;
                free(del);
                del = nullptr;
                flag = 1;
                edge_num++;
            }
            else{  // if the next arc doesn't exist
                free(del);
                del = nullptr;
                G.vertices[i].firstarc = nullptr;
                flag = 1;
                edge_num++;
            }
        }
        else{  // remove the other arc
            while (del != nullptr){
                del = pre->nextarc;
                if (del != nullptr && del->adjvex == pos){
                    pre->nextarc = del->nextarc;
                    free(del);
                    del = nullptr;
                    flag = 1;
                    edge_num++;
                }
                pre = pre->nextarc;
            }
        }
    }

    for (int i=0;i<G.vexnum;i++) // renumber the arc
    {
        ArcNode *temp;
        temp = G.vertices[i].firstarc;
        while (temp!= nullptr){
            if (temp->adjvex > pos) temp->adjvex--;
            temp = temp->nextarc;
        }
    }
    G.arcnum = G.arcnum - edge_num;
    if (flag) return OK;
    else return  ERROR;
    /********** End **********/
}


status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 函数首先对要寻找的的key值的位序进行匹配，匹配后对两个位序进行判断，当前仅当pos1和pos2都存在且不相同时匹配成功
     * 接着判断当前弧是否已经存在于邻接表中
     * 最后将弧添加到两个结点对应的邻接链表中
     */
    int pos1 = -1;
    int pos2 = -1;
    ArcNode *temp;
    for (int i = 0; i < G.vexnum; i++) // match the position
    {
        if (G.vertices[i].data.key == v) pos1 = i;
        if (G.vertices[i].data.key == w) pos2 = i;
    }

    if (pos2 == pos1 || pos1 == -1 || pos2 == -1) return ERROR;  // 1. the key does not exist 2. v==w

    // test if the arc has already existed
    temp = G.vertices[pos1].firstarc;
    while (temp != nullptr){
        if (temp->adjvex == pos2) return  ERROR;
        temp = temp->nextarc;
    }

    // add the arc
    temp = (ArcNode *)malloc(sizeof(ArcNode));
    temp->adjvex = pos2;
    temp->nextarc = G.vertices[pos1].firstarc;
    G.vertices[pos1].firstarc = temp;

    temp = (ArcNode *)malloc(sizeof(ArcNode));
    temp->adjvex = pos1;
    temp->nextarc = G.vertices[pos2].firstarc;
    G.vertices[pos2].firstarc = temp;

    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 函数首先对要寻找的的key值的位序进行匹配，匹配后对两个位序进行判断，当前仅当pos1和pos2都存在且不相同时匹配成功
     * 接着判断当前弧是否存在于邻接表中
     * 最后删除两个顶点的邻接链表中对应的表结点，同样这里也要考虑两种情况：
     * 1. 删除的表结点为当前结点的第一个邻接结点
     * 2. 删除的表结点为当前结点其他邻接点
     * 第一种情况又要分为有一个邻接结点还是多个邻接结点，这样才能适应各种情况。
     */
    int pos1 = -1;
    int pos2 = -1;
    ArcNode *temp;
    int flag = 0;
    for (int i = 0; i < G.vexnum; i++) // match the position
    {
        if (G.vertices[i].data.key == v) pos1 = i;
        if (G.vertices[i].data.key == w) pos2 = i;
    }

    if (pos2 == pos1 || pos1 == -1 || pos2 == -1) return ERROR;  // 1. the key does not exist 2. v==w

    // test if the arc has already existed
    temp = G.vertices[pos1].firstarc;
    while (temp!= nullptr){
        if (temp->adjvex == pos2) flag = 1;
        temp = temp->nextarc;
    }

    if (flag==0) return ERROR;// the arc doesn't exist

    int flag_v = 0;
    int flag_w = 0;

    //delete the arc
    ArcNode * del;
    ArcNode * pre;
    del = G.vertices[pos1].firstarc;
    pre = del;
    if (del->adjvex == pos2) // delete the first arc
    {
        // the second arc exists
        if (del->nextarc != nullptr){
            G.vertices[pos1].firstarc = del->nextarc;
        }
        //the second arc doesn't exist
        else {
            G.vertices[pos1].firstarc = nullptr;
        }
        free(del);
        del = nullptr;
        flag_v = 1;
    }
    else{
        // delete the other arc
        del = pre->nextarc;
        while (del != nullptr){
            if (del->adjvex == pos2){
                pre->nextarc = del->nextarc;
                free(del);
                del = nullptr;
                flag_v = 1;
                break;
            }
            pre = pre->nextarc;
            del = pre->nextarc;
        }
    }

    del = G.vertices[pos2].firstarc;
    pre = del;
    if (del->adjvex == pos1) // delete the first arc
    {
        // the second arc exists
        if (del->nextarc != nullptr){
            G.vertices[pos2].firstarc = del->nextarc;
        }
            //the second arc doesn't exist
        else {
            G.vertices[pos2].firstarc = nullptr;
        }
        free(del);
        del = nullptr;
        flag_w = 1;
    }
    else{
        // delete the other arc
        del = pre->nextarc;
        while (del != nullptr){
            if (del->adjvex == pos1){
                pre->nextarc = del->nextarc;
                free(del);
                del = nullptr;
                flag_w = 1;
                break;
            }
            pre = pre->nextarc;
            del = pre->nextarc;
        }
    }

    if (flag_w && flag_v) return OK;
    return ERROR;
    /********** End **********/
}

bool visited[MAX_VERTEX_NUM]; //全局变量

int get_next_pos(ALGraph G, int pos_v, int pos_w)
{
    ArcNode *temp;
    temp = G.vertices[pos_v].firstarc;
    while (temp!= nullptr){
        if (temp->adjvex == pos_w){
            if (temp->nextarc != nullptr) return temp->nextarc->adjvex;
            else return -1;
        }
        temp = temp->nextarc;
    }
    return -1;
}

int get_first_pos(ALGraph G, int pos_v){
    if (G.vertices[pos_v].firstarc != nullptr) return G.vertices[pos_v].firstarc->adjvex;
    else return -1;
}

void DFS(ALGraph G, int pos_v, void (*visit)(VertexType))
{
    visited[pos_v]= TRUE;
    visit(G.vertices[pos_v].data);
    for (int pos_w = get_first_pos(G, pos_v); pos_w != -1 ; pos_w =get_next_pos(G, pos_v, pos_w)){
        if (visited[pos_w] == FALSE) DFS(G, pos_w, visit);
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 首先利用一个数组记录当前结点是否已经被访问过
     * 接着利用递归对图进行深度优先遍历，每遍历一个结点都用改变数组的值以免被再度遍历
     */
    for (int i=0;i<MAX_VERTEX_NUM;i++){
        visited[i] = FALSE;
    }
    for (int i=0;i<G.vexnum; i++){
        if (!visited[i]) DFS(G, i, visit);
    }
    return OK;
    /********** End **********/
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /**
     * 利用队列每访问一个结点都将与之相邻接的结点送入队列中，并利用数组记录访问过的结点避免再度访问
     */
    int queue[100];
    int front = 0;
    int rear = 0;
    for (int i=0;i<MAX_VERTEX_NUM;i++) visited[i] = FALSE;
    int i=0;
    while (i<G.vexnum){
        if (!visited[i]) queue[rear++] = i;
        while (front!=rear){
            if (!visited[queue[front]]){
                visited[queue[front]] = TRUE;
                visit(G.vertices[queue[front]].data);
                ArcNode *temp;
                temp = G.vertices[queue[front]].firstarc;
                while (temp!= nullptr){
                    queue[rear++] = temp->adjvex;
                    temp = temp->nextarc;
                }
            }
            front++;
        }
        i++;
    }
    return OK;
    /********** End **********/
}

status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
    int i=0;
    KeyType keys[100];
    while (V[i].key!=-1){ //add nodes
        G.vertices[i].data = V[i];
        keys[V[i].key] = i;
        G.vertices[i].firstarc = nullptr; //init
        i++;
    }
    G.vexnum = i;

    i=0;
    while (VR[i][0] != -1 && VR[i][1] != -1){
        // add arc
        ArcNode *temp;
        temp = (ArcNode*)malloc(sizeof(ArcNode));
        temp->adjvex = keys[VR[i][1]];
        temp->nextarc = nullptr;
        if (G.vertices[keys[VR[i][0]]].firstarc == nullptr) G.vertices[keys[VR[i][0]]].firstarc = temp;
        else{
            ArcNode *p;
            p = G.vertices[keys[VR[i][0]]].firstarc;
            while (p->nextarc != nullptr) p = p->nextarc;
            p->nextarc = temp;
        }
        i++;
    }
    G.arcnum = i;
    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    /**
     * 为方便读取，采取二进制方式存取，首先写入顶点信息，最后以-1结尾，接着写入边的信息，这里采取每一行为一个顶点的邻接结点的位序
     */
    FILE *fp;
    fp = fopen(FileName, "wb");
    if (fp == nullptr){
        printf("open file failed!");
        return ERROR;
    }

    // write the vertex information
    for (int i=0;i<G.vexnum;i++){
        fwrite(&G.vertices[i].data, sizeof(G.vertices[i].data), 1, fp);
    }
    VertexType *temp1;
    temp1 = (VertexType*)malloc(sizeof(VertexType));
    temp1->key = -1;
    strcpy(temp1->others, "nils");
    fwrite(temp1, sizeof(VertexType),1, fp);


    //record the keys
    KeyType keys[100]={0};
    for(int i=0;i<G.vexnum;i++){
        keys[i] = G.vertices[i].data.key;
    }

    //write the arc
//    KeyType adj[100][100]={0};
    for (int i=0;i<G.vexnum;i++){
        ArcNode *temp;
        temp = G.vertices[i].firstarc;
        while (temp!= nullptr){
            putc(keys[i], fp);
            putc(keys[temp->adjvex], fp);
            temp = temp->nextarc;
        }
    }
//    KeyType adj[100][100]={0};
//    for (int i=0;i<G.vexnum;i++){
//        ArcNode *temp;
//        temp = G.vertices[i].firstarc;
//        while (temp!= nullptr){
//            if (adj[keys[i]][keys[temp->adjvex]]==0){
//                adj[keys[i]][keys[temp->adjvex]] = 1;
//                adj[keys[temp->adjvex]][keys[i]] = 1;
//                putc(keys[i], fp);
//                putc(keys[temp->adjvex], fp);
//            }
//            temp = temp->nextarc;
//        }
//    }
    fclose(fp);
    return OK;

    /********** End 1 **********/
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    /**
     * 根据之前定义好的文件的信息，首先将顶点信息读入到一个数组中，接着再将边的信息读入到另一个数组中，并以此建图。
     */
    FILE *fp;
    fp = fopen(FileName, "rb");
    if (fp == nullptr){
        printf("open file failed!");
        return ERROR;
    }

    //load the vertex information
    VertexType V[100];
    int vexnum=0;
    VertexType *temp;
    temp = (VertexType*)malloc(sizeof(VertexType));
    while (true){
        fread(temp, sizeof(VertexType), 1, fp);
        V[vexnum++] = *temp;
        if (temp->key==-1) break;
    }

    //load the arc information
    KeyType VR[100][2];
    int arcnum=0;
    while (true){
        KeyType v_key = getc(fp);
        KeyType w_key = getc(fp);
        VR[arcnum][0] = v_key;
        VR[arcnum][1] = w_key;
        arcnum++;
        if (v_key == -1 || w_key == -1) break;
    }

    CreateCraph(G, V, VR);
    return OK;

    /********** End 2 **********/
}

status Locate_Graph(GraphList GList, char GraphName[])
{
    /**
         * 操作结果为确定名为GraphName的graph在表中的位置；若该名字的图不存在则返回0；
         * 函数对图的名字进行匹配，若匹配成功则返回相应的位置值，匹配失败则返回0
         */
    for (int i = 0; i<GList.length;i++){
        if (strcmp(GraphName, GList.elem[i].name)==0){  // graph exists
            return i+1;
        }
    }
    return 0;
}

status Remove_Graph(GraphList &GList, int pos)
{
/**
     * 操作结果为将位置为pos的树从多二叉树列表中删除；若返回ERROR则该位置的树不存在于多二叉树列表TL中，若返回OK则删除成功
     * 函数首先调用销毁二叉树的函数对二叉树T进行销毁，接着利用循环将删除位置之后的树的位置往前移动
     */
    if (pos == 0) return ERROR;
    DestroyGraph(*GList.elem[pos-1].G);
    for (int i=pos-1; i<GList.length-1;i++){
        GList.elem[i] = GList.elem[i+1];
    }
    GList.length--;
    return OK;
}

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

status Graph_Exist(ALGraph *G)
{
    /**
     * 判断二叉树是否存在；若存在则返回OK，不存在则返回INFEASIBLE；
     * 函数即判断二叉树T的头指针是否为空
     */
    if (G == nullptr) return INFEASIBLE;
    else return OK;
}

void change_root(GraphList &GList, ALGraph *G, int pos)
{
    if (pos!=0) GList.elem[pos-1].G = G;
}

status Add_to_GraphList(char GraphName[], ALGraph* &G, GraphList &GList)
{
    /**
     * 初始条件为二叉树T存在；操作结果为将二叉树T存到多二叉树列表TL中；若返回INFEASIBLE则二叉树不存在，若返回ERROR则二叉树列表中已有该名字，若返回OK则添加成功
     * 函数首先判断T是否为空，接着进行树的名字（字符串）匹配，如果匹配成功则将当前树的根节点的值存入到树的管理表中
     */
    if (G == nullptr) return INFEASIBLE;
    for (int i = 0; i<GList.length;i++){
        if (strcmp(GraphName, GList.elem[i].name)==0){  // tree exists
            return ERROR;
        }
    }
    strcpy(GList.elem[GList.length].name, GraphName);
    GList.elem[GList.length].G = G;
    GList.length++;
    G = nullptr;
    return OK;
}

void Show_GraphList(GraphList GList)
{
    /**
     * 以先序遍历的形式打印多二叉树列表
     */
    printf("there are %d graphs in the list!\n", GList.length);
    for (int i=0;i<GList.length;i++){
        printf("%s\n",GList.elem[i].name);
        Show_Adj(*GList.elem[i].G);
        printf("-------------------------\n");
    }
}

status switch_to_graph(GraphList TL, char GraphName[], ALGraph* &G)
{
    /**
     * 操作结果为根据二叉树的名字切换要操作的二叉树；若返回OK则该名字的树存在，切换成功，若返回ERROR则该名字的树不存在，切换失败。
     *  函数对树的名字进行匹配，若匹配成功则将书的管理表中的相应指针值赋给当前根指针
     */
    for (int i = 0; i<TL.length;i++){
        if (strcmp(GraphName, TL.elem[i].name)==0){  // tree exists
            G = TL.elem[i].G;
            return OK;
        }
    }
    return ERROR;
}

status Show_Adj(ALGraph G)
{
    for(int i=0;i<G.vexnum;i++)
    {
        ArcNode *p=G.vertices[i].firstarc;
        printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
        while (p)
        {
            printf(" %d",p->adjvex);
            p=p->nextarc;
        }
        printf("\n");
    }
    return OK;
}