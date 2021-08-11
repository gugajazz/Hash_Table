#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int key;
    char value[10];
};
typedef struct node node;

int size = 3;

void clear_buffer(){
    int i;
    do{
        i = getchar();
    }while ( i != '\n' && i != EOF );
    return;
}

int hash(int key){
    return (key % size);
}

void find(int key, node *hashtable){
    int index = hash(key);
    if(hashtable[index].key == key){
        printf("Key/Value pair in index %d\n",index); 
    }
    else{
        for(int i=index, k=0; i<size; i++){ 
            if(hashtable[i].key == key){
                printf("Key/Value pair in index %d\n",i); 
                break;
            }
            else if(i==size-1){
                i=-1; //after loop it will end up as 0 and so it can check from the begining of the table
            }
            else{
                k++;
            }
            if(k==size-1){
                printf("Key not in hashtable\n");
                return;
            }
        }
    }
}

int insert(int key, char *value, node *hashtable){
    int index;
    index = hash(key);
    printf("\nindex->%d\n",index);
    if(hashtable[index].value[0] == '\0'){ //no colision
        printf("No Colision\n");
        hashtable[index].key = key;
        strcpy(hashtable[index].value, value);
    }
    else{ //colision
        printf("Colision\n");
        for(int i=index, k=0; i<size; i++){ 
            if(hashtable[i].value[0] == '\0'){
                hashtable[i].key = key;
                strcpy(hashtable[i].value, value);
                break;
            }
            else if(i==size-1){
                i=-1; //after loop it will end up as 0 and so it can check from the begining of the table
            }
            else{
                k++;
            }
            if(k==size-1){
                printf("Hastable is full\n");
                return 0;
            }
        }
    }
    
}

void initialize_hashtable(node *hashtable){
    for(int i=0; i<size; i++){
        hashtable[i].key = 0;
        hashtable[i].value[0] = '\0';
    }
}

void show(node *hashtable){
    printf("Index | Key | Value\n");
    for(int i=0; i<size; i++){
        printf("  %d   |%5.1d   |   %s\n",i,hashtable[i].key, hashtable[i].value);
    }
}

void main(){
    node hashtable[50];
    char value[10];
    char key_str[10]; 
    int key, loop=1, checking_input=1;

    initialize_hashtable(hashtable);
    show(hashtable);

    while(loop){
        checking_input=1;
        while(checking_input){
            printf("\nInsert key: ");
            fgets(key_str,10,stdin);
            key = atoi(key_str); //convert str to int         
            if(key==0 && key_str[0] != '0'){
                printf("Invalid key\n");
                checking_input = 1;
            }
            else{
                printf("\nInsert value: ");
                fgets(value,10,stdin);
                value[strcspn(value, "\n")] = 0; //remove trailing \n
                loop = insert(key, value, hashtable);
                show(hashtable);
                checking_input = 0;
            }
        } 
    }

    find(69, hashtable);
}  