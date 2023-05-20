#include <iostream>
#include <stdlib.h>
using namespace std;

//单链表，无头结点

typedef struct snode{
    snode* next;
    int value;
} snode, *single_linked_list;

void single_linked_list_init(single_linked_list &l){
    l = NULL;
}

void single_linked_list_insert(single_linked_list &l, int index, int value){
    int current_index = 0;
    single_linked_list* current_node;
    current_node = &l;
    //找到index对应的节点,允许进到第一个不存在的节点
    while(current_index < index && *current_node != NULL){
        current_node = &((*current_node) -> next);
        current_index += 1;
    } 
    //断言找到index
    if(index != current_index){
        throw invalid_argument("Index Erro");
    }
    //判断有无后驱
    snode* next;
    if(*current_node == NULL){
        next = NULL;
    }
    else{
        next = *current_node;
    }
    //构建新节点
    snode* new_node = (snode*)malloc(sizeof(snode));
    new_node->value=value;
    new_node->next=next;
    *current_node = new_node;
}

int single_linked_list_read_value(single_linked_list l, int index){
    int current_index = 0;
    snode* current_node = l;

    while(current_index < index && current_node -> next != NULL){
        current_node = current_node -> next;
        current_index += 1;
    }
    //过滤超出表长和负值
    if(current_index == index){
        return current_node -> value;
    }
    else{
        throw invalid_argument("Index Erro");
    }
}

void single_linked_list_pop(single_linked_list &l, int index){
    int current_index = 0;
    single_linked_list* current_node = &l;
    //不允许进入不存在的节点
    while(current_index < index && (*current_node) -> next != NULL){
        current_node = &((*current_node) -> next);
        current_index += 1;
    }
    if (index == current_index){
        snode* node_to_free;
        if((*current_node) -> next != NULL){
            node_to_free = *current_node;
            *current_node = (*current_node) -> next;
        }
        else{
            *current_node = NULL;
        }
        free(node_to_free);
    }
    else{
        throw invalid_argument("Index Erro.");
    }
}

int single_linked_list_index(single_linked_list l, int value){
    int current_index = 0;
    snode* current_node = l;
    if(current_node != NULL && value == current_node -> value){
        return current_index;
    }
    while(current_node -> next != NULL){
        current_index += 1;
        current_node = current_node -> next;
        if(value == current_node -> value){
            return current_index;
        }
    }
    throw invalid_argument("Value Erro.");
}

void single_linked_list_distroy(single_linked_list &l){
    snode* d = l;
    snode* s;
    while(d != NULL){
        s = d;
        d = d->next;
        free(s);
    }
    l = NULL;
}

int main(){
    single_linked_list a;
    single_linked_list_insert(a, 0, 100);
    single_linked_list_insert(a, 1, 200);
    cout << single_linked_list_read_value(a, 0) <<endl;
    single_linked_list_pop(a, 0);
    cout << single_linked_list_read_value(a, 0) <<endl;
    cout << single_linked_list_index(a, 200) <<endl;

    
    for(int i = 0; i < 10; i++){
        single_linked_list_insert(a, 0, i);
    }
    for(int i = 0; i < 11; i++){
       
        cout << single_linked_list_read_value(a, i) <<endl;
    }
}
