#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define size 10
           //10,000,000

struct node{
    int key;
    char value[10];
    struct node *next;
};
typedef struct node node;

static node hashtable[size];

int hash(int key){
    return (key % size);
}

void find_linear_search(int key, node *hashtable, int verbose){
    int node_number=0;
    clock_t begin = clock();

    for(int i=0; i<size; i++){
        node *on = &hashtable[i];
        while(1){
            if(on->key == key){
                if(verbose==1){
                    printf("Key/Value pair in index %d, node number %d\n",i, node_number); 
                    clock_t end = clock();
                    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
                    printf("Time spent-> %f\n",time_spent);
                }
                return;
            }
            
            if(on->next == NULL){
                break;
            }
            
            else{
                on = on->next;
                node_number++;
            }
        }
    }
    
    printf("Key %d not in hashtable\n", key);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
    printf("Time Spent-> %f\n",time_spent);
    return;
    
}

int find(int key, int verbose){ // returns 1 if found & zero if not in table
    clock_t begin = clock();
    int node_number=0;
    int index = hash(key);
    
    node *on = &hashtable[index];
    while(1){
        if(on->key == key){
            if(verbose==1){
                printf("Key/Value pair in index %d, node number %d\n",index, node_number); 
                clock_t end = clock();
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
                printf("Time spent-> %f\n",time_spent);
            }
            return 1;
        }
        else if(on->next != NULL){
            on = on->next;
            node_number++;
        }
        else{
            if(verbose==1){
                printf("Key %d not in hashtable\n", key);
                clock_t end = clock();
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
                printf("Time spent-> %f\n",time_spent);
            }
            return 0;
        }
    }
}

void fill_table(node *hashtable){
    char filled[10] = "FILLED";
    for(int i=99000000; i<99999995; i++){
        strcpy(hashtable[i].value, filled);
    }
}

void insert(int key, char *value){ //double pointer to change values
    clock_t begin = clock();
    int index;
    index = hash(key);
    if(hashtable[index].value[0] == '\0'){ //no colision
        printf("No Colision\n");
        hashtable[index].key = key;
        strcpy(hashtable[index].value, value);
        hashtable[index].next = NULL;
        printf("\nSaved at index->%d Node->0\n",index);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
        printf("Time spent-> %f\n",time_spent);
    }
    else{ //colision
        int node_index = 1;
        node *on = &hashtable[index]; // on only starts at the on and then walks trough the LL
                                            // (points to the next node after the first)
        node *head = &hashtable[index];
        node *new = malloc(sizeof(node));

        new->key = key;
        strcpy(new->value, value);
        new->next = NULL;

        if(on->next == NULL){
            on->next = new;
            printf("Colision\n");
            printf("\nSaved at index->%d Node->1\n",index);
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
            printf("Time spent-> %f\n",time_spent);
            return;
        }
        
        while(on->next != NULL){
            on = on->next;
            node_index++;
        }
        
        on->next = new;

        printf("Colision\n");
        printf("\nSaved at index->%d Node->%d\n",index,node_index);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
        printf("Time spent-> %f\n",time_spent);
    }
}

void initialize_hashtable(){
    for(int i=0; i<size; i++){
        hashtable[i].key = 0;
        hashtable[i].value[0] = '\0';
        hashtable[i].next = NULL;
    }
}

void show(){
    for(int i=0; i<size; i++){
        node *on = hashtable[i].next; // on only starts as the on and then walks trough the LL

        if(on == NULL){
            printf("\n|I:%d|K:%d|V:%s| --> NULL\n",i,hashtable[i].key, hashtable[i].value);

        }
        else{
            printf("\n|I:%d|K:%d|V:%s| --> ",i,hashtable[i].key, hashtable[i].value);
            while(on != NULL){
                printf("|I:%d|K:%d|V:%s| --> ",i,on->key, on->value);
                on = on->next;
            }
            printf("NULL\n");
        }
    }
}

void main(){
    
    char input[10]; 
    int key, loop=1, checking_input=1;

    initialize_hashtable(hashtable);

    while(loop){
        printf("\nAdd key/value(1)\nRemove key/value(2)\nSee hashtable(3)\nSearch by key(4)\nLinear search(5)\nExit(6)\n-> ");
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
                    else if(find(key, 0) == 1){
                        printf("Key already in hashtable\n");
                    }
                    else{
                        printf("\nInsert value (MAX 9 CHARS): ");
                        fgets(input,10,stdin);
                        input[strcspn(input, "\n")] = 0; //remove trailing \n
                        insert(key, input);
                        checking_input = 0;
                    }
                } 
                break;

            case '2':
                break;
    
            case '3':
                show();
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
                find(key, 1);
                break;

            case '5':
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
                find_linear_search(key,hashtable,1);
                break;

            case '6':
                printf("Bye");
                exit(1);
                break;
        }   
    }
}  