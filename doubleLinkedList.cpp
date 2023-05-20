#include <iostream>
#include <stdlib.h>
using namespace std;

//双链表，有头结点，不循环，index从0开始

typedef struct dnode{
    int value;
    dnode* prior;
    dnode* next;
} dnode, *double_linked_list;

void double_linked_list_init(double_linked_list &l){
    l = (dnode*)malloc(sizeof(dnode));
    l->next = NULL;
    l->prior = NULL;
    l->value = 0;
}

void insert_next_dnode(dnode* &p, dnode* &s){
    s->next = p->next;
    if(p->next != NULL){
        p->next->prior = s;
    }
    s->prior = p;
    p->next = s;
}

bool double_linked_list_insert(double_linked_list &l, int index, int value){
    int current_index = -1;
    dnode* p = l;
    while(p != NULL){
        if(current_index + 1 == index){
            dnode* s = (dnode*)malloc(sizeof(dnode));
            s->value = value;
            //插入到下一个节点
            insert_next_dnode(p, s);
            return true;  
        }
        p = p->next;
        current_index += 1;
    }
    throw invalid_argument("Index Erro");
}

int double_linked_list_read_value(double_linked_list l, int index){
    int current_index = 0;
    dnode* d = l->next;
    while(d != NULL){
        if(current_index == index){
            return d->value;
        }
        current_index += 1;
        d = d->next;
    }
    throw invalid_argument("Index Erro");
}

void del_next_dnode(dnode* &p){
    dnode* d = p->next;

    p->next = d->next;
    if(d->next != NULL){
        d->next->prior = p;
    }
    free(d);
}

bool double_linked_list_pop(double_linked_list &l, int index){
    int current_index = -1;
    dnode* p = l;
    while(p != NULL){
        if(current_index + 1 ==index){
            //删除后一个节点
            del_next_dnode(p);
            return true;
        }
        current_index += 1;
        p = p->next;
    }
    throw invalid_argument("Index Erro");
}

int double_linked_list_index(double_linked_list l, int value){
    int current_index = 0;
    dnode* d = l->next;
    while(d != NULL){
        if(d->value == value){
            return current_index;
        }
        current_index += 1;
        d = d->next;
    }
    throw invalid_argument("Value Erro");
}

void double_linked_list_destroy(double_linked_list &l){
    dnode* d = l;
    dnode* s;
    while(d != NULL){
        s = d;
        d = d->next;
        free(s);
    }
    l = NULL;
}

int main(){
    double_linked_list a;
    double_linked_list_init(a);
    for(int i = 100; i < 2000; i += 100){
        double_linked_list_insert(a, 0, i);
    }
    
    double_linked_list_pop(a, 0);
    cout << double_linked_list_read_value(a, 0) << endl;

    cout << double_linked_list_index(a, 100) << endl;
    

    return 0;
}