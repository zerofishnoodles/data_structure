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
    printf("    ���������[0~21]:");
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
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
//5 ���Ա� 8 ���� 7 ������ 6 ����ͼ -1 nil 5 6 5 7 6 7 7 8 -1 -1
//5 ���Ա� 7 ���� 7 ������ 6 ����ͼ -1 nil 5 6 5 7 6 7 10 8 -1 -1
//5 ���Ա� 8 ���� 7 ������ 6 ����ͼ -1 nil 5 6 5 7 6 7 10 8 -1 -1
//1 G 2 G2 3 G3 4 G4 5 G5 6 G6 7 G7 8 G8 9 G9 10 G10 11 G11 12 G12 13 G13 14 G14 15 G15 16 G16 17 G17 18 G18 19 G19 20 G20 21 G21 -1 nil -1 -1
//1 G 2 G2 3 G3 4 G4 5 G5 6 G6 7 G7 8 G8 9 G9 10 G10 11 G11 12 G12 13 G13 14 G14 15 G15 16 G16 17 G17 18 G18 19 G19 20 G20 -1 nil -1 -1
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * �������ȼ��ͼ�Ľ��Ĺؼ����Ƿ����ظ�����������ż������ı������Ƿ���ȷ����ȷ��Ҫ�����¼�����Ҫ��
     * 1. �߲����ظ�����
     * 2. �ñߵ������˵�����ڽ��������
     * ������֮��������ӽ�㣬����ӱߣ���Ҫע����ǣ���ӱߵ�ʱ������������ͼ��������ñ���ص������ڵ㶼Ҫ�������������ķ�ʽҲ�ܼ򵥣�ֱ�ӶԵ��������ͷ�弴��
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
/*��������ͼG*/
{
    /**
     * ����ͨ�����ν��뵱ǰ�ڵ����ӵı���浽��������ͳһ�ͷſռ����ﵽ����ͼ��Ŀ��
     */
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * ͨ��ѭ������ƥ���ҵ�Ҫ���ҵĽ��λ��
     */
    for (int i =0 ;i<G.vexnum;i++){
        if (u == G.vertices[i].data.key) return i;
    }
    return -1;

    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * ��ͨ��ѭ����¼���ֵ�keyֵ����ͨ��ѭ������ƥ����ң����ҳɹ�������Ϊ��1. ���ҳɹ���keys���ظ� 2. ���ҳɹ���Ҫ�滻�ĺͱ��滻�����
     */
    KeyType keys[100]={0};
    for (int i=0;i<G.vexnum;i++){  // record keys
        keys[G.vertices[i].data.key] = 1;
    }
    for (int i=0;i<G.vexnum;i++){ // 1. ���ҳɹ���keys���ظ� 2. ���ҳɹ���Ҫ�滻�ĺͱ��滻�����
        if (u == G.vertices[i].data.key && (keys[value.key] == 0 || u == value.key)){
            G.vertices[i].data = value;
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}

int FirstAdjVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * ͨ��ѭ������Ҫ���ҵĶ������ƥ�䣬ƥ��ɹ����ص�һ�ڽӵ��λ��
     */
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].firstarc != nullptr && u == G.vertices[i].data.key) return G.vertices[i].firstarc->adjvex;
    }
    return -1;

    /********** End **********/
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * ����ͨ��һ��ѭ���ҵ���ǰ���㣬��ͨ��һ��ѭ��������ǰ�����ڽӽ�㣬�ҵ����ҵ����λ�á�
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
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * ����ͨ��һ��ѭ����¼���ֵ�keyֵ�����Ŵ�β��������������Ķ��㣬��������ز���
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
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * ����ͨ��һ��ѭ��ɾ����Ӧ�Ķ��㲢���²���
     * ����ɾ����֮�����ıߣ���Ҫ����Ϊ����ѭ���������ڽӱ���б������������жϣ��ܹ���Ϊ���������
     * 1. ɾ���ı���Ϊ��ǰ���ĵ�һ���ڽӽ��
     * 2. ɾ���ı���Ϊ��ǰ��������ڽӵ�
     * ��һ�������Ҫ��Ϊ��һ���ڽӽ�㻹�Ƕ���ڽӽ�㣬����������Ӧ���������
     * ���Ҫ�Ա������ǵ�λ��������±��
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
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * �������ȶ�ҪѰ�ҵĵ�keyֵ��λ�����ƥ�䣬ƥ��������λ������жϣ���ǰ����pos1��pos2�������Ҳ���ͬʱƥ��ɹ�
     * �����жϵ�ǰ���Ƿ��Ѿ��������ڽӱ���
     * ��󽫻���ӵ���������Ӧ���ڽ�������
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
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * �������ȶ�ҪѰ�ҵĵ�keyֵ��λ�����ƥ�䣬ƥ��������λ������жϣ���ǰ����pos1��pos2�������Ҳ���ͬʱƥ��ɹ�
     * �����жϵ�ǰ���Ƿ�������ڽӱ���
     * ���ɾ������������ڽ������ж�Ӧ�ı��㣬ͬ������ҲҪ�������������
     * 1. ɾ���ı���Ϊ��ǰ���ĵ�һ���ڽӽ��
     * 2. ɾ���ı���Ϊ��ǰ��������ڽӵ�
     * ��һ�������Ҫ��Ϊ��һ���ڽӽ�㻹�Ƕ���ڽӽ�㣬����������Ӧ���������
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

bool visited[MAX_VERTEX_NUM]; //ȫ�ֱ���

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
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * ��������һ�������¼��ǰ����Ƿ��Ѿ������ʹ�
     * �������õݹ��ͼ����������ȱ�����ÿ����һ����㶼�øı������ֵ���ⱻ�ٶȱ���
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
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /**
     * ���ö���ÿ����һ����㶼����֮���ڽӵĽ����������У������������¼���ʹ��Ľ������ٶȷ���
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
//��ͼ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
    /**
     * Ϊ�����ȡ����ȡ�����Ʒ�ʽ��ȡ������д�붥����Ϣ�������-1��β������д��ߵ���Ϣ�������ȡÿһ��Ϊһ��������ڽӽ���λ��
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
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    /**
     * ����֮ǰ����õ��ļ�����Ϣ�����Ƚ�������Ϣ���뵽һ�������У������ٽ��ߵ���Ϣ���뵽��һ�������У����Դ˽�ͼ��
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
         * �������Ϊȷ����ΪGraphName��graph�ڱ��е�λ�ã��������ֵ�ͼ�������򷵻�0��
         * ������ͼ�����ֽ���ƥ�䣬��ƥ��ɹ��򷵻���Ӧ��λ��ֵ��ƥ��ʧ���򷵻�0
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
     * �������Ϊ��λ��Ϊpos�����Ӷ�������б���ɾ����������ERROR���λ�õ����������ڶ�������б�TL�У�������OK��ɾ���ɹ�
     * �������ȵ������ٶ������ĺ����Զ�����T�������٣���������ѭ����ɾ��λ��֮�������λ����ǰ�ƶ�
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
     * �ж϶������Ƿ���ڣ��������򷵻�OK���������򷵻�INFEASIBLE��
     * �������ж϶�����T��ͷָ���Ƿ�Ϊ��
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
     * ��ʼ����Ϊ������T���ڣ��������Ϊ��������T�浽��������б�TL�У�������INFEASIBLE������������ڣ�������ERROR��������б������и����֣�������OK����ӳɹ�
     * ���������ж�T�Ƿ�Ϊ�գ����Ž����������֣��ַ�����ƥ�䣬���ƥ��ɹ��򽫵�ǰ���ĸ��ڵ��ֵ���뵽���Ĺ������
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
     * �������������ʽ��ӡ��������б�
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
     * �������Ϊ���ݶ������������л�Ҫ�����Ķ�������������OK������ֵ������ڣ��л��ɹ���������ERROR������ֵ��������ڣ��л�ʧ�ܡ�
     *  �������������ֽ���ƥ�䣬��ƥ��ɹ�����Ĺ�����е���Ӧָ��ֵ������ǰ��ָ��
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