#include "cstring"
#include "def.h"
#define max(a,b) (a>=b?a:b)

int num_create=0;
void menu()
{
    printf("\n\n");
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. CreateBiTree        2. DestroyBiTree  \n");
    printf("    	  3. BiTreeDepth       4. LocateNode\n");
    printf("    	  5. Assign      6. GetSibling   \n");
    printf("    	  7. InsertNode      8. DeleteNode\n");
    printf("    	  9. PreOrderTraverse        10. InOrderTraverse\n");
    printf("    	  11. PostOrderTraverse     12. LevelOrderTraverse\n");
    printf("    	  13. SaveBiTree       14. LoadBiTree\n");
    printf("          15. BiTreeExist    16. ClearBiTree\n");
    printf("          17. Add_to_TreeList     18. show_tree_list\n");
    printf("    	  19. switch_to_tree       20. remove_tree    \n");
    printf("          21.locate_tree        22. BiTreeEmpty     0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~22]:");
}
status test(TElemType definition[])
{
    int i=0;
    KeyType key;
    while (definition[i].key!=-1){
        if(definition[i].key == 0) {i++; continue;}
        key = definition[i].key;
        int j=i;
        int num=0;
        while (definition[j].key!=-1){
            if (key == definition[j].key) num++;
            j++;
        }
        if (num>1) return ERROR;
        i++;
    }
    return OK;
}

status CreateBiTree(BiTree &T,TElemType definition[])
{
    /**
     * 根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，如果有相同的关键字，返回ERROR
     * 函数首先检测给定的先序遍历的序列中有没有重复的关键字，接着检测T是否已经存在，最后利用递归以先序遍历的顺序创建二叉树。
     * 检测利用两层循环遍历逐一匹配并计数，若当前要匹配的数有重复则检测失败，若无重复则检测成功
     * 检测T的指针是否为空来判断T是否存在
     * 递归利用num_create全局变量来记录当前读取到的数据的位置，每次传入数据所在的数组名，递归结束的条件为出现为null的数据
     */
     //1 a 2 b 0 null 0 null 3 c 4 d 0 null 0 null 5 e 0 null 0 null -1 null
     //1 a 2 b 0 null 0 null 3 c 4 d 0 null 0 null 3 e 0 null 0 null -1 null
     //101 陈道明 102 王刚 103 张嘉译 0 null 0 null 104 赵本山 0 null 0 null 105 李冰冰 106 牛莉 0 null 0 null 107 郭德纲 0 null 0 null -1 null
     //1 a 2 b 0 null 3 c 4 d 0 null 5 e 0 null 0 null 0 null 0 null -1 null
    /********** Begin *********/
    if (test(definition)==ERROR) return ERROR;  // exam the key has overlap
    if (BiTreeExist(T)==OK) return ERROR;
    if (strcmp(definition[num_create].others, "null")==0) {num_create++;return OK;}
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data = definition[num_create];
    T->lchild = nullptr;
    T->rchild = nullptr;
    num_create++;
    CreateBiTree(T->lchild, definition); // recursively apply
    CreateBiTree(T->rchild, definition);
    return OK;
    /********** End **********/
}

status DestroyBiTree(BiTree &T)
{
    // 请在这里补充代码，完成本关任务
    /**
     * 将二叉树设置成空，并删除所有结点，释放结点空间
     * 函数首先利用先序遍历将指向每个结点的指针值存入到一个数组中，再遍历这个数组，释放指针所指向的空间并将其置为空
     */
    /********** Begin *********/
    BiTree p, st[100], rm[100];
    p = (BiTree)malloc(sizeof(BiTNode));
    p = T;
    if (p == nullptr) return INFEASIBLE;
    int top1=0, top2=0;
    st[top1++] = p;
    while (top1) {  //preordertraverse to get the node entered the stack
        p = st[--top1];
        rm[top2++] = p;
        if (p->rchild != nullptr) {
            st[top1++] = p->rchild;
        }
        if (p->lchild != nullptr) {
            st[top1++] = p->lchild;
        }
    }
    for(int i=0;i<top2;i++){  // remove the node in the stack
        free(rm[i]);
        rm[i] = nullptr;
    }
    T = nullptr;
    return 1;
    /********** End **********/
}

int BiTreeDepth(BiTree T)
{
    /**
     * 求二叉树T的深度
     * 利用递归求函数的深度；递归的结束条件为T为空
     */
    /********** Begin *********/
    if (T==NULL){
        return 0;
    }
    return max(BiTreeDepth(T->lchild),BiTreeDepth(T->rchild))+1;
    /********** End **********/
}

BiTNode* LocateNode(BiTree T,KeyType e)
//find the node with key e
{
    /**
     * 函数首先判断T是否为空，接着利用先序遍历逐一匹配key值，若匹配到则返回相应的指针
     */
    /********** Begin *********/
    int top=0;
    BiTree p,st[100],result=nullptr;
    p = T;
    if (p == nullptr) return result;
    if(p!=nullptr){ //pre order traverse to find the result
        st[top++] = p;
        while(top){
            p = st[--top];
            if(p->data.key == e) result = p;
            if(p->rchild!=nullptr){
                st[top++] = p->rchild;
            }
            if(p->lchild!=nullptr){
                st[top++] = p->lchild;
            }
        }
    }
    return result; //if find failed, return null

    /********** End **********/
}
status Assign(BiTree &T,KeyType e,TElemType value)
{
    /**
     * 函数首先判断T是否为空，接着利用先序遍历记录key值是否出现，最后再用一次先序遍历进行匹配，匹配成功进行相应赋值，匹配成功有两种情况
     * 1. 匹配成功且要添加重新赋值的key没有出现过 2. 要重新赋值的key刚好等于匹配的key
     */
    /********** Begin *********/
    int top=0;
    KeyType keys[1000]={0};  //set a array to record the key in case there is an overlap
    BiTree p,st[100];
//    p = (BiTree)malloc(sizeof(BiTNode));
    p = T;
    if (T == nullptr) return INFEASIBLE;
    if(p!=nullptr){  //pre order traverse
        st[top++] = p;
        while(top){
            p = st[--top];
            keys[p->data.key] = 1;  // this key exist
            if(p->rchild!=nullptr){
                st[top++] = p->rchild;
            }
            if(p->lchild!=nullptr){
                st[top++] = p->lchild;
            }
        }
    }
    p = T; top=0;
    if(p!=nullptr){  //pre order traverse
        st[top++] = p;
        while(top){
            p = st[--top];
            // 1. search succeed && the key is not exist
            // 2. the replace key is the same as the given key
            if((p->data.key == e && keys[value.key]==0 )||(e==value.key && keys[e]==1)) {p->data = value; return OK;}
            if(p->rchild!=nullptr){
                st[top++] = p->rchild;
            }
            if(p->lchild!=nullptr){
                st[top++] = p->lchild;
            }
        }
    }
    return ERROR;

    /********** End **********/
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    /**
     * 函数首先判断数是否为空，接着判断要获取的兄弟节点是否为根节点，然后利用先序遍历逐一匹配，匹配成功则返回相应指针值。
     * 匹配成功的条件为当前节点存在两个孩子且某个孩子的key值和给定key值相等，若和左孩子相等则返回右孩子，若和右孩子相等则返回左孩子
     */
    /********** Begin *********/
    int top=0;
    BiTree p,st[100],result=nullptr, left_child=nullptr, right_child=nullptr, pre = nullptr;
//    p = (BiTree)malloc(sizeof(BiTNode));
    p = T;
    if (p == nullptr) return result;
    if (e == p->data.key) return result;
    if(p!=nullptr){
        st[top++] = p;
        while(top){
            p = st[--top];
            if((p->rchild!= nullptr && p->lchild!= nullptr) && (e == p->lchild->data.key||e == p->rchild->data.key)){
                if (e == p->lchild->data.key){
                    result = p->rchild;
                } else result = p->lchild;
                return result;
            }
            right_child = p->rchild;
            if(p->rchild!=nullptr){
                st[top++] = p->rchild;
            }
            left_child = p->lchild;
            if(p->lchild!=nullptr){
                st[top++] = p->lchild;
            }
        }
    }
    return result;

    /********** End **********/
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
{
    /**
     * 插入节点
     * 函数首先判断T是否为空，接着判断是否是在空树中插入根节点，然后利用先序遍历记录key值，最后再利用一次先序遍历进行匹配，匹配成功判断是左叉还是右插再进行相应的插入操作
     * 匹配成功的条件有2个：1.key值不重复且插入到根节点 2.key值不重复、当前节点的key值和给定key值匹配
     *
     */
    /********** Begin *********/
    int top=0;
    KeyType keys[1000]={0};
    BiTree p,st[100];
    p = (BiTree)malloc(sizeof(BiTNode));
    p = T;
    if (T == nullptr) return INFEASIBLE;
    if (T->data.key == 0 && LR == -1){
        T->data = c;
        T->rchild = nullptr;
        T->lchild = nullptr;
        return OK;
    }
    if(p!=nullptr){  // first traverse for keys[]
        st[top++] = p;
        while(top){
            p = st[--top];
            keys[p->data.key] = 1;
            if(p->rchild!=nullptr){
                st[top++] = p->rchild;
            }
            if(p->lchild!=nullptr){
                st[top++] = p->lchild;
            }
        }
    }
    p = T;
    if(p!=nullptr){  //second traverse for insert
        st[top++] = p;
        while(top){
            p = st[--top];
            if (keys[c.key]==0 && LR==-1){          //if on root
                    BiTree new_node;           //contruct new node
                    new_node = (BiTree)malloc(sizeof(BiTNode));
                    new_node->data = c;
                    new_node->lchild = nullptr;
                    new_node->rchild = T;
                    T = new_node;
                    return OK;
            }
            if(p->data.key == e && keys[c.key]==0){
                if(LR == 0){     //if on left
                    BiTree new_node;        //contruct new node
                    new_node = (BiTree)malloc(sizeof(BiTNode));
                    new_node->data = c;
                    new_node->lchild = nullptr;
                    new_node->rchild = p->lchild;
                    p->lchild = new_node;
                    return OK;
                }
                if(LR == 1){  //if on right
                    BiTree new_node; //contruct new node
                    new_node = (BiTree)malloc(sizeof(BiTNode));
                    new_node->data = c;
                    new_node->lchild = nullptr;
                    new_node->rchild = p->rchild;
                    p->rchild = new_node;
                    return OK;
                }
            }
            if(p->rchild!=nullptr){
                st[top++] = p->rchild;
            }
            if(p->lchild!=nullptr){
                st[top++] = p->lchild;
            }
        }
    }

    return ERROR;
    /********** End **********/
}

void delete_node(BiTree &parent, BiTree p, int LR)
{
    if(p->rchild==nullptr&&p->lchild==nullptr){  //without child
        free(p);
        if(LR==0) parent->lchild=nullptr;
        if(LR==1) parent->rchild=nullptr;
        return;
    }
    if((p->rchild!=nullptr&&p->lchild== nullptr)||(p->lchild!=nullptr&&p->rchild== nullptr)){  //have one child
        if(LR==0){
            if(p->rchild!=nullptr){
                parent->lchild = p->rchild;
                free(p);
                p = nullptr;
                return;
            }
            if(p->lchild!=nullptr){
                parent->lchild = p->lchild;
                free(p);
                p = nullptr;
                return;
            }
        }
        if(LR==1){
            if(p->rchild!=nullptr){
                parent->rchild = p->rchild;
                free(p);
                p=nullptr;
                return;
            }
            if(p->lchild!=nullptr){
                parent->rchild = p->lchild;
                free(p);
                p=nullptr;
                return;
            }
        }
    }
    if(p->lchild!=nullptr&&p->rchild!=nullptr){  //have both child
        BiTree temp, new_root;
        temp = p->rchild;
        // concanate the left tree
        if(LR==0){
            parent->lchild = p->lchild;
            free(p);
            new_root = parent->lchild;
        }
        else{
            parent->rchild = p->lchild;
            free(p);
            new_root = parent->rchild;
        }
        // find the rightest child
        while(new_root->rchild!=nullptr) new_root = new_root->rchild;
        new_root->rchild = temp;
        return;
    }
}

status DeleteNode(BiTree &T,KeyType e)
{
    /**
     * 删除结点
     * 函数首先判断二叉树T是否为空，接着判断是否删除的是头结点，若删除头节点则按照头节点的孩子个数进行删除结点，
     * 接着利用先序遍历进行匹配，若匹配成功则进行相应的结点删除操作
     * 匹配成功的条件为当前结点的某个孩子结点的key值和给定的key值相等
     * 结点删除的函数需要传入当前结点和匹配成功的孩子结点以及其孩子结点是当前结点的左孩子还是右孩子，然后判断当前结点的孩子个数，再根据当前结点和孩子个数进行与之对应的操作
     */
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int top=0;
    // KeyType keys[100]={0};
    BiTree p,st[100],head;
    p = (BiTree)malloc(sizeof(BiTNode));
    p = T;
    if (T == nullptr) return INFEASIBLE;
    if (T->data.key == e){
        head = T->lchild;
        p = head;
        while (p->rchild!=nullptr) p=p->rchild;
        p->rchild = T->rchild;
        free(T);
        T = head;
        return 1;
    }
    if(p!=nullptr){  // traverse
        st[top++] = p;
        while(top){
            p = st[--top];
            if((p->lchild!=nullptr&&p->lchild->data.key == e)||(p->rchild!=nullptr&&p->rchild->data.key == e)){ //save parent
                if((p->lchild!= nullptr)&&(p->lchild->data.key == e)){
                    delete_node(p, p->lchild, 0);
                    return OK;
                }
                if((p->rchild!= nullptr)&&(p->rchild->data.key == e)){
                    delete_node(p, p->rchild, 1);
                    return OK;
                }
            }
            if(p->rchild!=nullptr){
                st[top++] = p->rchild;
            }
            if(p->lchild!=nullptr){
                st[top++] = p->lchild;
            }
        }
    }
    return ERROR;
    /********** End **********/
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    /**
     * 利用栈的思想，首先将头结点入栈，接着每弹出一个结点并进行visit后，都将其右孩子和左孩子按顺序入栈（先右后左才能保证先弹出左孩子），如此循环便能能遍历，
     * 循环结束的条件为栈为空
     */
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == nullptr) return INFEASIBLE;
    if (T->data.key==0) return ERROR;
    BiTree p,st[100];
    int top=0;
    if(T!=nullptr){
        st[top++] = T;
        while(top){
            p = st[--top];
            visit(p);
            if(p->rchild!=nullptr){
                st[top++] = p->rchild;
            }
            if(p->lchild!=nullptr){
                st[top++] = p->lchild;
            }
        }
    }
    return OK;
    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    /**
     * 中序遍历二叉树
     * 函数利用栈的思想，首先判断二叉树T是否存在，接着判断二叉树T是否为空。每一次循环都首先向左走到底并入栈，接着判断栈是否为空，若非空则弹出并访问，
     * 并将指针移向右子树。循环结束的条件为栈为空且当前指向的结点为空。
     */
    /********** Begin *********/
    if (T == nullptr) return INFEASIBLE;
    if (T->data.key==0) return ERROR;
    BiTree st[100],p;
    p = T;
    int top=0;
    do{
        while(p){
            st[top++] = p;
            p = p->lchild;
        }
        if(top){
            p = st[--top];
            visit(p);
            p = p->rchild;
        }
    }while(top||p);
    return 1;
    /********** End **********/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    /**
     * 后序遍历二叉树
     * 函数首先判断二叉树是否存在和是否为空，接着利用栈首先先向左走到底，即将根结点和左子树的根节点入栈，并用flag记录当前指针所指向的是左孩子还是右孩子，
     * 接着利用循环访问栈中的指针,并将指针移向当前结点的右子树，改变flag值，循环进行
     *
     */
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == nullptr) return INFEASIBLE;
    if (T->data.key==0) return ERROR;
    BiTree st[100],p,pre;
    p = T;
    int top=0,flag;
    do{
        while(p){
            st[top++] = p;
            p = p->lchild;
        }
        pre = nullptr;  // the rchild is NULL
        flag = 1;  //on the left of the root
        while(flag&&top){
            p = st[top-1];
            if(p->rchild==pre)  //treverse through the right tree
            {
                visit(p);
                top--;
                pre = p;
            }
            else{
                p = p->rchild;flag=0;  //on the right of the root
            }
        }
    }while(top);
    return 1;
    /********** End **********/
}

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    /**
     * 按层遍历二叉树T
     * 利用队列的思想，首先将头结点入队，接着循环出队，每出队一个结点，都将该结点的左右孩子按顺序入队
     * 循环结束条件为队列为空
     */
    /********** Begin *********/
    if (T == nullptr) return INFEASIBLE;
    if (T->data.key==0) return ERROR;
    BiTree st[100];
    BiTree p;
    p = T;
    int front=0,rear=0;
    st[rear++] = p;
    while(front!=rear){
        p = st[front++];
        visit(p);
        if (p->lchild!=nullptr) st[rear++] = p->lchild;
        if (p->rchild!=nullptr) st[rear++] = p->rchild;
    }
    return 1;

    /********** End **********/
}
status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    /**
     * 初始条件为二叉树T存在；操作结果为将树以先序遍历的方式存到文件FileName中；若返回INFEASIBLE则二叉树不存在，若返回OK则存储成功。
     * 利用先序遍历逐一将结点信息输出到文件中，每一行一个结点，信息格式为：key others
     * 若当前结点某个孩子为空，则构建新的结点，并将结点的key值赋为0，送入栈中
     *
     */
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (T == nullptr) return INFEASIBLE;
    int top=0;
    KeyType a[100];
    BiTree p,st[100],TreeArray[100];
    int num_node = 0;
    p = T;
    FILE *fp;
    fp = fopen(FileName,"w");
    if(fp==nullptr) {printf("open failed!");exit(-1);}
    if(p!=nullptr){
        st[top++] = p;
        while(top){
            p = st[--top];
            // printf("%d",p->data.key);
            fputc(char(p->data.key),fp);
            fputc('\t',fp);
            fputs(p->data.others,fp);
            fputc('\n',fp);
            if(p->rchild!=nullptr&&p->data.key!=0){
                st[top++] = p->rchild;
            }
            else if(p->data.key!=0){  // right child is null
                BiTree temp;
                temp = (BiTree)malloc(sizeof(BiTNode));
                temp->data.key = 0;
                strcpy(temp->data.others,"#");
                temp->lchild = nullptr;
                temp->rchild = nullptr;
                st[top++] = temp;
            }
            if(p->lchild!=nullptr&&p->data.key!=0){
                st[top++] = p->lchild;
            }
            else if(p->data.key!=0){  // left child is null
                BiTree temp;
                temp = (BiTree)malloc(sizeof(BiTNode));
                temp->data.key = 0;
                strcpy(temp->data.others,"#");
                temp->lchild = nullptr;
                temp->rchild = nullptr;
                st[top++] = temp;
            }
        }
    }
    fclose(fp);
    return 1;
    /********** End 1 **********/
}
status LoadBiTree(BiTree &T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    /**
     * 操作结果为将文件FileName中以先序遍历存储的二叉树读取出来；若返回ERROR则二叉树T已存在，若返回OK则存储成功
     * 函数首先判断当前树是否为空，接着逐行读取文件中的信息进入到一个数组，微调数组中数据的格式使符合给定给是，即在末尾加上null，
     * 再根据这个数组调用create——bitree函数进行树的生成。
     */
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
//    DestroyBiTree(T);
    FILE *fp;
    TElemType def[100];
    int def_length=0;
    fp = fopen(FileName, "r");
    if (T != nullptr) return ERROR;
    if(fp==nullptr){
        printf("file open failed!");
        exit(-1);
    }
    TElemType p;
    while (!feof(fp)){
        p.key = fgetc(fp);
        fgetc(fp);
        fgets(p.others,20,fp);
        int len = strlen(p.others);
        p.others[len-1] = '\0';  // replace the \n
        if (p.key==0){
            strcpy(p.others, "null");
        }
        def[def_length++] = p;
    }
    TElemType temp;
    temp.key=0;
    strcpy(temp.others,"null");
    def[def_length] = temp;
    CreateBiTree(T,def);
    return 1;

    /********** End 2 **********/
}

void visit(BiTree p)
{
    printf("(%d,%s)",p->data.key,p->data.others);
}

status BiTreeExist(BiTree T){
    /**
     * 判断二叉树是否存在；若存在则返回OK，不存在则返回INFEASIBLE；
     * 函数即判断二叉树T的头指针是否为空
     */
    if (T == nullptr) return INFEASIBLE;
    else return OK;
}

status ClearBiTree(BiTree &T){
    /**
     * 函数首先直接将该树销毁，接着新建一个根节点，以key=0标志当前为空树
     */
    if (T == nullptr) return INFEASIBLE;
    DestroyBiTree(T);  // first destroy
    BiTree temp;
    temp = (BiTree)malloc(sizeof(BiTNode));
    temp->data.key=0;  // symbolize the emptiness
    temp->lchild = nullptr;
    temp->rchild = nullptr;
    T = temp;
    return OK;
}

status Add_to_TreeList(char TreeName[], BiTree &T, TreeList &TL)
{
    /**
     * 初始条件为二叉树T存在；操作结果为将二叉树T存到多二叉树列表TL中；若返回INFEASIBLE则二叉树不存在，若返回ERROR则二叉树列表中已有该名字，若返回OK则添加成功
     * 函数首先判断T是否为空，接着进行树的名字（字符串）匹配，如果匹配成功则将当前树的根节点的值存入到树的管理表中
     */
    if (T == nullptr) return INFEASIBLE;
    for (int i = 0; i<TL.length;i++){
        if (strcmp(TreeName, TL.elem[i].name)==0){  // tree exists
            return ERROR;
        }
    }
    strcpy(TL.elem[TL.length].name, TreeName);
    TL.elem[TL.length].T = T;
    TL.length++;
    T = nullptr;
    return OK;
}

void show_tree_list(TreeList TL)
{
    /**
     * 以先序遍历的形式打印多二叉树列表
     */
    printf("there are %d trees in the list!\n", TL.length);
    for (int i=0;i<TL.length;i++){
        printf("%s\t",TL.elem[i].name);
        PreOrderTraverse(TL.elem[i].T, visit);
        printf("\n");
    }
}

status switch_to_tree(TreeList TL, char TreeName[], BiTree &T)
{
    /**
     * 操作结果为根据二叉树的名字切换要操作的二叉树；若返回OK则该名字的树存在，切换成功，若返回ERROR则该名字的树不存在，切换失败。
     *  函数对树的名字进行匹配，若匹配成功则将书的管理表中的相应指针值赋给当前根指针
     */
    for (int i = 0; i<TL.length;i++){
        if (strcmp(TreeName, TL.elem[i].name)==0){  // tree exists
            T = TL.elem[i].T;
            return OK;
        }
    }
    return ERROR;
}

status remove_tree(TreeList &TL, int pos){
    /**
     * 操作结果为将位置为pos的树从多二叉树列表中删除；若返回ERROR则该位置的树不存在于多二叉树列表TL中，若返回OK则删除成功
     * 函数首先调用销毁二叉树的函数对二叉树T进行销毁，接着利用循环将删除位置之后的树的位置往前移动
     */
    if (pos == 0) return ERROR;
    DestroyBiTree(TL.elem[pos-1].T);
    for (int i=pos-1; i<TL.length-1;i++){
        TL.elem[i] = TL.elem[i+1];
    }
    TL.length--;
    return OK;
}

int locate_tree(TreeList TL, char TreeName[])
{
    /**
     * 操作结果为确定名为TreeName的树在二叉树中的位置；若该名字的树不存在则返回0；
     * 函数对书的名字进行匹配，若匹配成功则返回相应的位置值，匹配失败则返回0
     */
    for (int i = 0; i<TL.length;i++){
        if (strcmp(TreeName, TL.elem[i].name)==0){  // tree exists
            return i+1;
        }
    }
    return 0;
}

status BiTreeEmpty(BiTree T)
{
    /**
     * 判断函数是否为空
     * 函数首先判断二叉树T是否存在，接着根据前面清空二叉树函数对空树的定义，直接判断根节点的key值是否为0即可
     */
    if (T == nullptr) return INFEASIBLE;
    else if (T->data.key == 0) return OK;
    else return ERROR;
}

void change_root(TreeList &TL, BiTree T, int pos)
{
    if (pos!=0) TL.elem[pos-1].T = T;
}