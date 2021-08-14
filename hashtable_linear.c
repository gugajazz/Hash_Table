#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define size 100000000
           //100,000,000

struct node{
    int key;
    char value[10];
};
typedef struct node node;

int hash(int key){
    return (key % size);
}

void find_linear_search(int key, node *hashtable){
    clock_t begin = clock();

    for(int i=0; i<size; i++){
        if(hashtable[i].key==key){
            printf("Key/Value pair in index %d\n",i); 
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
            printf("Time-> %f\n",time_spent);
            return;
        }
    }
    
    printf("Key %d not in hashtable\n", key);
    return;
    
}

void find(int key, node *hashtable){
    clock_t begin = clock();

    int index = hash(key);
    if(hashtable[index].key == key){ // se tiver sido guardado sem colision
        printf("Key/Value pair in index %d\n",index); 
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
        printf("Time-> %f\n",time_spent);
    }
    else{
        for(int i=index, k=0; i<size; i++){ // se tiver sido guardado com colision
            if(hashtable[i].key == key){
                printf("Key/Value pair in index %d\n",i); 
            
                clock_t end = clock();
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
                printf("Time-> %f\n",time_spent);

                return;
            }
            else if(i==size-1){
                i=-1; //after loop it will end up as 0 and so it can check from the begining of the table
            }
            else{
                k++;
            }
            if(k==size-1){
                printf("Key %d not in hashtable\n", key);
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
    printf("\nIndex | Key | Value\n");
    for(int i=0; i<size; i++){
        printf("  %d   |%5.1d   |   %s\n",i,hashtable[i].key, hashtable[i].value);
    }
}

void main(){
    
    static node hashtable[size];
    char input[50]; 
    int key, loop=1, checking_input=1;

    initialize_hashtable(hashtable);

    while(loop){
        printf("\nAdd key/value(1)\nRemove key/value(2)\nSee hashtable(3)\nSearch by key(4)\nexit(5)\nLinear search(6)\n-> ");
        fgets(input, 2, stdin);
        while ((getchar()) != '\n'); //clear stdin buffer
        switch (input[0]){
            default:
                printf("Incorrect input.\n");
                break;

            case '1':
                checking_input=1;
                while(checking_input){
                    printf("\nInsert key (MAX 49 CHARS): ");
                    fgets(input,50,stdin);
                    key = atoi(input); //convert str to int         
                    if(key==0 && input[0] != '0'){
                        printf("Invalid key\n");
                        checking_input = 1;
                    }
                    else{
                        printf("\nInsert value (MAX 9 CHARS): ");
                        fgets(input,10,stdin);
                        input[strcspn(input, "\n")] = 0; //remove trailing \n
                        insert(key, input, hashtable);
                        checking_input = 0;
                    }
                } 
                break;

            case '2':
                break;
    
            case '3':
                show(hashtable);
                break;
            
            case '4':
                checking_input=1;
                while(checking_input){
                    printf("\nInsert key (MAX 49 CHARS): ");
                    fgets(input,50,stdin);                    
                    key = atoi(input); //convert str to int         
                    if(key==0 && input[0] != '0'){
                        printf("Invalid key\n");
                        checking_input = 1;
                    }
                    else{
                        checking_input=0;
                    }
                }
                find(key, hashtable);
                break;

            case '5':
                exit(1);
                break;

            case '6':
                checking_input=1;
                while(checking_input){
                    printf("\nInsert key (MAX 49 CHARS): ");
                    fgets(input,50,stdin);                    
                    key = atoi(input); //convert str to int         
                    if(key==0 && input[0] != '0'){
                        printf("Invalid key\n");
                        checking_input = 1;
                    }
                    else{
                        checking_input=0;
                    }
                }
                find_linear_search(key,hashtable);
                break;
        }   
    }
}  