#include <iostream>
#include <stdlib.h>
using namespace std;

//双链表，有头结点，不循环，index从0开始

typedef struct node{
    int value;
    node* prior;
    node* next;
} node, *linked_list;

void linked_list_init(linked_list &l){
    l = (node*)malloc(sizeof(node));
    l->next = NULL;
    l->prior = NULL;
    l->value = 0;
}

void insert_next_node(node* &p, node* &s){
    s->next = p->next;
    if(p->next != NULL){
        p->next->prior = s;
    }
    s->prior = p;
    p->next = s;
}

bool linked_list_insert(linked_list &l, int index, int value){
    int current_index = -1;
    node* p = l;
    while(p != NULL){
        if(current_index + 1 == index){
            node* s = (node*)malloc(sizeof(node));
            s->value = value;
            //插入到下一个节点
            insert_next_node(p, s);
            return true;  
        }
        p = p->next;
        current_index += 1;
    }
    throw invalid_argument("Index Erro");
}

int linked_list_read_value(linked_list l, int index){
    int current_index = 0;
    node* d = l->next;
    while(d != NULL){
        if(current_index == index){
            return d->value;
        }
        current_index += 1;
        d = d->next;
    }
    throw invalid_argument("Index Erro");
}

void del_next_node(node* &p){
    node* d = p->next;

    p->next = d->next;
    if(d->next != NULL){
        d->next->prior = p;
    }
    free(d);
}

bool linked_list_pop(linked_list &l, int index){
    int current_index = -1;
    node* p = l;
    while(p != NULL){
        if(current_index + 1 ==index){
            //删除后一个节点
            del_next_node(p);
            return true;
        }
        current_index += 1;
        p = p->next;
    }
    throw invalid_argument("Index Erro");
}

int linked_list_index(linked_list l, int value){
    int current_index = 0;
    node* d = l->next;
    while(d != NULL){
        if(d->value == value){
            return current_index;
        }
        current_index += 1;
        d = d->next;
    }
    throw invalid_argument("Value Erro");
}

int main(){
    linked_list a;
    linked_list_init(a);
    for(int i = 100; i < 2000; i += 100){
        linked_list_insert(a, 0, i);
    }
    
    linked_list_pop(a, 0);
    cout << linked_list_read_value(a, 0) << endl;

    cout << linked_list_index(a, 100) << endl;
    

    return 0;
}