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
    };
    l.len = 0;
    l.max = 6;
};

void seq_list_test(seq_list &l){
    for(int i =0; i < l.max; i++){
        cout << l.block[i] <<endl;
    };
     cout <<"len:"<< l.len <<"\nmax:"<<l.max<<endl;
};

bool seq_list_extension(seq_list &l){
    int *last_block = l.block;
    l.block = (int*)malloc(sizeof(int) * (l.max + INIT_SIZE));
    l.max = l.max + INIT_SIZE;
    for(int i = 0; i < l.len; i++){
        l.block[i] = last_block[i];
    };
    for(int i = l.len; i < l.max; i++){
        l.block[i] = 0;
    };
    return true;
}

bool seq_list_insert(seq_list &l, int index, int value){
   
    if(index <= l.len && index >= 0){
         if(index >= l.max){
        seq_list_extension(l);
        }
        for(int i = l.len-1; i >= index; i--){
            l.block[i+1] = l.block[i];
        };
        l.block[index] = value;
        l.len = l.len+1;
        return true;
    }
    else{
        throw "INDEX EXCEPTION";
    };
}

bool seq_list_pop(seq_list l, int index){
    for(int i = index; i < l.len-1; i++){
        l.block[i] = l.block[i+1];
    }
}

int seq_list_index(seq_list l, int value){
    for(int i = 0; i < l.len; i++){
        if(l.block[i] == value){
            return i;
        };
        return -1;
    }
}

int main(){
    seq_list list;
    seq_list_init(list);
    seq_list_test(list);
    seq_list_insert(list, 0, 999);
    seq_list_test(list);
};