#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define size 10
           //100,000,000

struct node{
    int key;
    char value[10];
    struct node *next;
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

void fill_table(node *hashtable){
    char filled[10] = "FILLED";
    for(int i=99000000; i<99999995; i++){
        strcpy(hashtable[i].value, filled);
    }
}

int insert(int key, char *value, node *hashtable){
    int index;
    index = hash(key);
    if(hashtable[index].value[0] == '\0'){ //no colision
        printf("No Colision\n");
        hashtable[index].key = key;
        strcpy(hashtable[index].value, value);
        hashtable[index].next = NULL;
        printf("\nSaved at index->%d\n",index);
    }
    else{ //colision
        printf("Colision\n");

        node *head = hashtable[index].next; // head only starts at the head and then walks trough the LL
                                            // (points to the next node after the first)
        if(head==NULL){ // if this node is the last
            hashtable[index].next=malloc(sizeof(node)); // point to the new last node
            head = hashtable[index].next;

            head->key=key; // assign the values to the newly created node
            strcpy(head->value, value);
            head->next=NULL;
        }
        else{
            if(head->next == NULL){ // 
                
            }
            else{
                head = head->next; //move to the next node
            }
        }    
    }
}

void initialize_hashtable(node *hashtable){
    for(int i=0; i<size; i++){
        hashtable[i].key = 0;
        hashtable[i].value[0] = '\0';
        hashtable[i].next = NULL;
    }
}

void show(node *hashtable){
    printf("\nIndex | Key | Value\n");
    for(int i=0; i<size; i++){
        node *head = hashtable[i].next; // head only starts as the head and then walks trough the LL

        if(head == NULL){
            printf("||  %d   |%5.1d   |   %s || --> ",i,hashtable[i].key, hashtable[i].value);

        }
        else{
            
            printf("||  %d   |%5.1d   |   %s || --> ",i,hashtable[i].key, hashtable[i].value);
            while(head != NULL){
                printf("||  %d   |%5.1d   |   %s || --> ",i,head->key, head->value);
                head = head->next;
            }
            printf("NULL\n");
        }
    }
}

void main(){
    
    static node hashtable[size];
    char input[10]; 
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
            case '7': // just to test the time it takes
                fill_table(hashtable);
                printf("DONE\n");
        }   
    }
}  