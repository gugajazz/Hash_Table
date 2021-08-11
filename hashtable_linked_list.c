#include <stdio.h>

struct node{
    int key;
    char value[50];
    struct node *next;
};
typedef struct node node;

void add_node_to_end(int key, char value[50], node head){

}

int hash(int key, int size){
    return (key % size);
}

void main(){
    node *hashtable[50];
    
}  