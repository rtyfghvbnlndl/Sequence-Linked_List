#include <iostream>
#include <stdlib.h>
using namespace std;

#define INIT_SIZE 6

typedef struct{
    int max;
    int len;
    int* block;
} seq_list;

void seq_list_init(seq_list &l){
    l.block = (int*)malloc(sizeof(int) * INIT_SIZE);
    for(int i = 0; i < INIT_SIZE; i++){
        l.block[i] = 0;
    }
    l.len = 0;
    l.max = 6;
}

void seq_list_test(seq_list &l){
    for(int i =0; i < l.max; i++){
        cout << l.block[i] <<endl;
    }
     cout <<"len:"<< l.len <<"\nmax:"<<l.max<<endl;
}

void seq_list_extension(seq_list &l){
    int *last_block = l.block;
    l.block = (int*)malloc(sizeof(int) * (l.max+INIT_SIZE));
    for(int i = 0; i < l.len; i++){
        l.block[i] = last_block[i];
    }
    for(int i = l.max-1; i < l.max + INIT_SIZE; i++){
        l.block[i] = 0;
    }
    l.max = l.max + INIT_SIZE;
    free(last_block);
}

void seq_list_short(seq_list &l){
    int* last_block = l.block;
    
    l.block = (int*)malloc(sizeof(int) * (l.max - INIT_SIZE));
    for(int i = 0; i < l.max - INIT_SIZE; i++){
        l.block[i] = last_block[i];
    }
    l.max -= INIT_SIZE;
    free(last_block);
}

void seq_list_insert(seq_list &l, int index, int value){
   
    if(index <= l.len && index >= 0){
        if(l.len+1 >= l.max){
        seq_list_extension(l);
        }
        for(int i = l.len; i >= index; i--){
            l.block[i+1] = l.block[i];
        }
        l.block[index] = value;
        l.len = l.len+1;
    }
    else{
        throw invalid_argument("Index Erro");
    }
}

void seq_list_pop(seq_list &l, int index){
    for(int i = index; i < l.len; i++){
        l.block[i] = l.block[i+1];
    }
    l.len = l.len-1;
    if(l.len < (l.max - INIT_SIZE)){ 
        //缩短
        seq_list_short(l);
    }
}

int seq_list_index(seq_list l, int value){
    for(int i = 0; i < l.len; i++){
        if(l.block[i] == value){
            return i;
        }
    }
    throw invalid_argument("Value Erro");
}

int seq_get_value(seq_list l, int index){
    if(index >= 0 && index < l.len){
        return l.block[index];
    }
    else{
       throw invalid_argument("Index Erro");
    }
}
int main(){
    //init
    seq_list list;
    seq_list_init(list);
    seq_list_test(list);
    //insert
    for(int i = 0; i < 7; i++){
        seq_list_insert(list, 0, i);
    };
    seq_list_test(list);
    //get value by index
    cout << "value" << seq_get_value(list, 0) << endl;
    seq_list_test(list);
    //get index by value
    cout << "index" << seq_list_index(list, 3) << endl;
    seq_list_test(list);
    //delate a value
    seq_list_pop(list, 0);
    seq_list_pop(list, 0);
    seq_list_test(list);

    return 0;
}