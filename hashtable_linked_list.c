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

static node hashtable[size];

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
    int node_number=0;
    int index = hash(key);
    
    node *on = &hashtable[index];
    while(1){
        if(on->key == key){
            printf("Key/Value pair in index %d, node number %d\n",index, node_number); 
            return;
        }
        else if(on->next != NULL){
            on = on->next;
            node_number++;
        }
        else{
            printf("Key %d not in hashtable\n", key);
            return;
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
    int index;
    index = hash(key);
    if(hashtable[index].value[0] == '\0'){ //no colision
        printf("No Colision\n");
        hashtable[index].key = key;
        strcpy(hashtable[index].value, value);
        hashtable[index].next = NULL;
        printf("\nSaved at index.%d\n",index);
    }
    else{ //colision
        printf("Colision\n");

        node *on = &hashtable[index]; // on only starts at the on and then walks trough the LL
                                            // (points to the next node after the first)
        node *head = &hashtable[index];
        node *new = malloc(sizeof(node));

        new->key = key;
        strcpy(new->value, value);
        new->next = NULL;

        if(on->next == NULL){
            on->next = new;
            return;
        }
        
        while(on->next != NULL){
            on = on->next;
        }
        
        on->next = new;
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
            printf("\n|I:%d|K:%d|V:%s|-->NULL\n",i,hashtable[i].key, hashtable[i].value);

        }
        else{
            printf("|I:%d|K:%d|V:%s|-->",i,hashtable[i].key, hashtable[i].value);
            while(on != NULL){
                printf("|I:%d|K:%d|V:%s|-->",i,on->key, on->value);
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