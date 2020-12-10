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
    printf("    ��ѡ����Ĳ���[0~22]:");
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
     * ���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK���������ͬ�Ĺؼ��֣�����ERROR
     * �������ȼ������������������������û���ظ��Ĺؼ��֣����ż��T�Ƿ��Ѿ����ڣ�������õݹ������������˳�򴴽���������
     * �����������ѭ��������һƥ�䲢����������ǰҪƥ��������ظ�����ʧ�ܣ������ظ�����ɹ�
     * ���T��ָ���Ƿ�Ϊ�����ж�T�Ƿ����
     * �ݹ�����num_createȫ�ֱ�������¼��ǰ��ȡ�������ݵ�λ�ã�ÿ�δ����������ڵ����������ݹ����������Ϊ����Ϊnull������
     */
     //1 a 2 b 0 null 0 null 3 c 4 d 0 null 0 null 5 e 0 null 0 null -1 null
     //1 a 2 b 0 null 0 null 3 c 4 d 0 null 0 null 3 e 0 null 0 null -1 null
     //101 �µ��� 102 ���� 103 �ż��� 0 null 0 null 104 �Ա�ɽ 0 null 0 null 105 ����� 106 ţ�� 0 null 0 null 107 ���¸� 0 null 0 null -1 null
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
    // �������ﲹ����룬��ɱ�������
    /**
     * �����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
     * ���������������������ָ��ÿ������ָ��ֵ���뵽һ�������У��ٱ���������飬�ͷ�ָ����ָ��Ŀռ䲢������Ϊ��
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
     * �������T�����
     * ���õݹ���������ȣ��ݹ�Ľ�������ΪTΪ��
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
     * ���������ж�T�Ƿ�Ϊ�գ������������������һƥ��keyֵ����ƥ�䵽�򷵻���Ӧ��ָ��
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
     * ���������ж�T�Ƿ�Ϊ�գ������������������¼keyֵ�Ƿ���֣��������һ�������������ƥ�䣬ƥ��ɹ�������Ӧ��ֵ��ƥ��ɹ����������
     * 1. ƥ��ɹ���Ҫ������¸�ֵ��keyû�г��ֹ� 2. Ҫ���¸�ֵ��key�պõ���ƥ���key
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
//ʵ�ֻ���ֵܽ��
{
    /**
     * ���������ж����Ƿ�Ϊ�գ������ж�Ҫ��ȡ���ֵܽڵ��Ƿ�Ϊ���ڵ㣬Ȼ���������������һƥ�䣬ƥ��ɹ��򷵻���Ӧָ��ֵ��
     * ƥ��ɹ�������Ϊ��ǰ�ڵ��������������ĳ�����ӵ�keyֵ�͸���keyֵ��ȣ�������������򷵻��Һ��ӣ������Һ�������򷵻�����
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
     * ����ڵ�
     * ���������ж�T�Ƿ�Ϊ�գ������ж��Ƿ����ڿ����в�����ڵ㣬Ȼ���������������¼keyֵ�����������һ�������������ƥ�䣬ƥ��ɹ��ж�����滹���Ҳ��ٽ�����Ӧ�Ĳ������
     * ƥ��ɹ���������2����1.keyֵ���ظ��Ҳ��뵽���ڵ� 2.keyֵ���ظ�����ǰ�ڵ��keyֵ�͸���keyֵƥ��
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
     * ɾ�����
     * ���������ж϶�����T�Ƿ�Ϊ�գ������ж��Ƿ�ɾ������ͷ��㣬��ɾ��ͷ�ڵ�����ͷ�ڵ�ĺ��Ӹ�������ɾ����㣬
     * �������������������ƥ�䣬��ƥ��ɹ��������Ӧ�Ľ��ɾ������
     * ƥ��ɹ�������Ϊ��ǰ����ĳ�����ӽ���keyֵ�͸�����keyֵ���
     * ���ɾ���ĺ�����Ҫ���뵱ǰ����ƥ��ɹ��ĺ��ӽ���Լ��亢�ӽ���ǵ�ǰ�������ӻ����Һ��ӣ�Ȼ���жϵ�ǰ���ĺ��Ӹ������ٸ��ݵ�ǰ���ͺ��Ӹ���������֮��Ӧ�Ĳ���
     */
    // �������ﲹ����룬��ɱ�������
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
//�������������T
{
    /**
     * ����ջ��˼�룬���Ƚ�ͷ�����ջ������ÿ����һ����㲢����visit�󣬶������Һ��Ӻ����Ӱ�˳����ջ�����Һ�����ܱ�֤�ȵ������ӣ������ѭ�������ܱ�����
     * ѭ������������ΪջΪ��
     */
    // �������ﲹ����룬��ɱ�������
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
//�������������T
{
    /**
     * �������������
     * ��������ջ��˼�룬�����ж϶�����T�Ƿ���ڣ������ж϶�����T�Ƿ�Ϊ�ա�ÿһ��ѭ�������������ߵ��ײ���ջ�������ж�ջ�Ƿ�Ϊ�գ����ǿ��򵯳������ʣ�
     * ����ָ��������������ѭ������������ΪջΪ���ҵ�ǰָ��Ľ��Ϊ�ա�
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
//�������������T
{
    /**
     * �������������
     * ���������ж϶������Ƿ���ں��Ƿ�Ϊ�գ���������ջ�����������ߵ��ף������������������ĸ��ڵ���ջ������flag��¼��ǰָ����ָ��������ӻ����Һ��ӣ�
     * ��������ѭ������ջ�е�ָ��,����ָ������ǰ�������������ı�flagֵ��ѭ������
     *
     */
    // �������ﲹ����룬��ɱ�������
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
//�������������T
{
    /**
     * �������������T
     * ���ö��е�˼�룬���Ƚ�ͷ�����ӣ�����ѭ�����ӣ�ÿ����һ����㣬�����ý������Һ��Ӱ�˳�����
     * ѭ����������Ϊ����Ϊ��
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
//���������Ľ������д�뵽�ļ�FileName��
{
    /**
     * ��ʼ����Ϊ������T���ڣ��������Ϊ��������������ķ�ʽ�浽�ļ�FileName�У�������INFEASIBLE������������ڣ�������OK��洢�ɹ���
     * �������������һ�������Ϣ������ļ��У�ÿһ��һ����㣬��Ϣ��ʽΪ��key others
     * ����ǰ���ĳ������Ϊ�գ��򹹽��µĽ�㣬��������keyֵ��Ϊ0������ջ��
     *
     */
    // �������ﲹ����룬��ɱ�������
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
//�����ļ�FileName�Ľ�����ݣ�����������
{
    /**
     * �������Ϊ���ļ�FileName������������洢�Ķ�������ȡ������������ERROR�������T�Ѵ��ڣ�������OK��洢�ɹ�
     * ���������жϵ�ǰ���Ƿ�Ϊ�գ��������ж�ȡ�ļ��е���Ϣ���뵽һ�����飬΢�����������ݵĸ�ʽʹ���ϸ������ǣ�����ĩβ����null��
     * �ٸ�������������create����bitree���������������ɡ�
     */
    // �������ﲹ����룬��ɱ�������
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
     * �ж϶������Ƿ���ڣ��������򷵻�OK���������򷵻�INFEASIBLE��
     * �������ж϶�����T��ͷָ���Ƿ�Ϊ��
     */
    if (T == nullptr) return INFEASIBLE;
    else return OK;
}

status ClearBiTree(BiTree &T){
    /**
     * ��������ֱ�ӽ��������٣������½�һ�����ڵ㣬��key=0��־��ǰΪ����
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
     * ��ʼ����Ϊ������T���ڣ��������Ϊ��������T�浽��������б�TL�У�������INFEASIBLE������������ڣ�������ERROR��������б������и����֣�������OK����ӳɹ�
     * ���������ж�T�Ƿ�Ϊ�գ����Ž����������֣��ַ�����ƥ�䣬���ƥ��ɹ��򽫵�ǰ���ĸ��ڵ��ֵ���뵽���Ĺ������
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
     * �������������ʽ��ӡ��������б�
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
     * �������Ϊ���ݶ������������л�Ҫ�����Ķ�������������OK������ֵ������ڣ��л��ɹ���������ERROR������ֵ��������ڣ��л�ʧ�ܡ�
     *  �������������ֽ���ƥ�䣬��ƥ��ɹ�����Ĺ�����е���Ӧָ��ֵ������ǰ��ָ��
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
     * �������Ϊ��λ��Ϊpos�����Ӷ�������б���ɾ����������ERROR���λ�õ����������ڶ�������б�TL�У�������OK��ɾ���ɹ�
     * �������ȵ������ٶ������ĺ����Զ�����T�������٣���������ѭ����ɾ��λ��֮�������λ����ǰ�ƶ�
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
     * �������Ϊȷ����ΪTreeName�����ڶ������е�λ�ã��������ֵ����������򷵻�0��
     * ������������ֽ���ƥ�䣬��ƥ��ɹ��򷵻���Ӧ��λ��ֵ��ƥ��ʧ���򷵻�0
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
     * �жϺ����Ƿ�Ϊ��
     * ���������ж϶�����T�Ƿ���ڣ����Ÿ���ǰ����ն����������Կ����Ķ��壬ֱ���жϸ��ڵ��keyֵ�Ƿ�Ϊ0����
     */
    if (T == nullptr) return INFEASIBLE;
    else if (T->data.key == 0) return OK;
    else return ERROR;
}

void change_root(TreeList &TL, BiTree T, int pos)
{
    if (pos!=0) TL.elem[pos-1].T = T;
}