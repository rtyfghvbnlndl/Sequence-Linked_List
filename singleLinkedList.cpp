#include <iostream>
#include <stdlib.h>
using namespace std;

//单链表，无头结点

typedef struct node{
    node* next_node;
    int value;
} node, *linked_list;

void linked_list_init(linked_list &l){
    l = NULL;
}

void linked_list_insert(linked_list &l, int index, int value){
    int current_index = 0;
    linked_list* current_node;
    current_node = &l;
    //找到index对应的节点,允许进到第一个不存在的节点
    while(current_index < index && *current_node != NULL){
        current_node = &((*current_node) -> next_node);
        current_index += 1;
    } 
    //断言找到index
    if(index != current_index){
        throw invalid_argument("Index Erro");
    }
    //判断有无后驱
    node* next_node;
    if(*current_node == NULL){
        next_node = NULL;
    }
    else{
        next_node = *current_node;
    }
    //构建新节点
    node* new_node = (node*)malloc(sizeof(node));
    new_node->value=value;
    new_node->next_node=next_node;
    *current_node = new_node;
}

int linked_list_read_value(linked_list l, int index){
    int current_index = 0;
    node* current_node = l;

    while(current_index < index && current_node -> next_node != NULL){
        current_node = current_node -> next_node;
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

void linked_list_pop(linked_list &l, int index){
    int current_index = 0;
    linked_list* current_node = &l;
    //不允许进入不存在的节点
    while(current_index < index && (*current_node) -> next_node != NULL){
        current_node = &((*current_node) -> next_node);
        current_index += 1;
    }
    if (index == current_index){
        node* node_to_free;
        if((*current_node) -> next_node != NULL){
            node_to_free = *current_node;
            *current_node = (*current_node) -> next_node;
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

int linked_list_index(linked_list l, int value){
    int current_index = 0;
    node* current_node = l;
    if(current_node != NULL && value == current_node -> value){
        return current_index;
    }
    while(current_node -> next_node != NULL){
        current_index += 1;
        current_node = current_node -> next_node;
        if(value == current_node -> value){
            return current_index;
        }
    }
    throw invalid_argument("Value Erro.");
}

int main(){
    linked_list a;
    linked_list_insert(a, 0, 100);
    linked_list_insert(a, 1, 200);
    cout << linked_list_read_value(a, 0) <<endl;
    linked_list_pop(a, 0);
    cout << linked_list_read_value(a, 0) <<endl;
    cout << linked_list_index(a, 200) <<endl;

    
    for(int i = 0; i < 10; i++){
        linked_list_insert(a, 0, i);
    }
    for(int i = 0; i < 11; i++){
       
        cout << linked_list_read_value(a, i) <<endl;
    }
}
