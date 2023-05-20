#include <iostream>
#include <stdlib.h>
using namespace std;

// 单链，循环，有头结点，头指针指向最后一个节点，index从0开始

typedef struct snode{
    int value;
    snode* next;
} snode, *circular_linked_list;

void circular_linked_list_init(circular_linked_list &l){
    l = (snode*)malloc(sizeof(snode));
    l->next = l;
}

void insert_next_node(snode* &p, snode* &s){
    s->next = p->next;
    p->next = s;
}
//遍历时，第一个节点是尾结点，可以直接在表尾插入新节点,允许使用-1
bool circular_linked_list_insert(circular_linked_list &l, int index, int value){
    int current_index = -2;
    snode* p = l;
    while(true){
        //后插
        if(current_index + 1 == index){
            snode* s = (snode*)malloc(sizeof(snode));
            //移动表指针到尾节点
            if(p == l){
                l = s;
            }
            s->value = value;
            insert_next_node(p, s);
            return true;
        }
        //判断第二次过尾结点
        if(p == l && current_index != -2){
            break;
        }
        p = p->next;
        current_index += 1;
    }
    throw invalid_argument("Index Erro");
}

void del_next_node(snode* &p){
    snode* d = p->next;
    p->next = d->next;
    free(d);
}
//即使指针指向尾结点，也不能删掉尾节点，index>=0
bool circular_linked_list_pop(circular_linked_list &l, int index){
        //跳过头节点
    if(index <0){
        throw invalid_argument("Index Erro");
    }
    int current_index = -2;
    snode* p = l;
    while(p != l || current_index == -2){
        if(current_index + 1 == index){
            //移动表指针到尾节点
            if(p->next == l){
                l = p;
            }
            del_next_node(p);
            return true;
        }
        p = p->next;
        current_index += 1;
    }
    throw invalid_argument("Index Erro");
}

int circular_linked_read_value(circular_linked_list l, int index){
    //跳过头节点
    if(index <0){
        index -= 1;
    }
    int current_index = -2;
    snode* d = l;
    while(true){
        if(current_index == index && d->next != d){
            return d->value;
        }
        //判断第二次过尾结点
        if(d == l && current_index != -2){
            break;
        }
        d = d->next;
        current_index += 1;
    }
    throw invalid_argument("Index Erro");
}

void circular_linked_list_destroy(circular_linked_list &l){
    snode* d = l;
    snode* p;
    do{ 
        p = d;
        d = d->next;
        free(p);
        
    }while(d != l); 
    l = NULL;
}

#define TEST_LEN 2
int main(){
    circular_linked_list a;
    circular_linked_list_init(a);

    for(int i = 100; i < TEST_LEN*100; i += 100){
        circular_linked_list_insert(a, -1, i);
    }
    for(int i = 0; i < TEST_LEN-1; i += 1){
        cout << circular_linked_read_value(a, i) << endl;
    }
    for(int i = 0; i < TEST_LEN-1; i += 1){
        
        cout << circular_linked_read_value(a, 0) << endl;
        circular_linked_list_pop(a,0);
    }
    circular_linked_list_destroy(a);
    

    return 0;
}