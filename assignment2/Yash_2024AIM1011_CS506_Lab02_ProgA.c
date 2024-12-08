#include <stdio.h>
#include <stdlib.h>

//defining node gor singly linked list
struct Node{
    int data;
    struct Node* next;
    
};

//making linked list from given array
struct Node* make_LL(int* nums,int n){

    struct Node* head = (struct Node*)malloc(sizeof(struct Node));

    head->data = nums[0];
    head->next = NULL;

    struct Node* current_node = head;

    for(int i=1;i<n;i++){

        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = nums[i];
        new_node->next = NULL;
        current_node->next = new_node;
        current_node = new_node;
    }
    return head;
}

//not using this function anywhere added this function because assignment doc says to add it
//I am using make LL function to make linked list since we are not adding new element after the linked list is made i am not using add_element_to_end()
//For this function to work i am assuming head exists
void add_element_to_end(struct Node* head,int n){

    struct Node* temp = head;

    while (temp->next != NULL){
        temp = temp->next;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = n;
    new_node->next = NULL;

    temp->next = new_node;

}

//function to print the linked list elements
void printLL(struct Node* head,int n){

    struct Node* temp = head;

    for(int i=0;i<n;i++){
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to merge two sorted linked lists
//selecting minimum node and setting its next node the next minimum recursively. 
struct Node* mergeLL(struct Node* LL1, struct Node* LL2) {
  
    if(LL1 == NULL){
        return LL2;
    }
    if(LL2 == NULL){
        return LL1;
    }

    if (LL1->data <= LL2->data) {
      
        if (LL1->next){
            LL1->next = mergeLL(LL1->next, LL2);
        } else{
            LL1->next = LL2;
        }  
        return LL1;
    } else {
      
        if (LL2->next){
            LL2->next = mergeLL(LL1, LL2->next);
        } else{
            LL2->next = LL1;
        } 
      
        return LL2;
    }
}



struct Node* mergesortLL(struct Node* head,int n){

    if(head == NULL || head->next == NULL){
        return head;
    }

    int middle = (n-1)/2;

    struct Node* cur_node = head;

    for(int i=0;i<middle;i++){
        cur_node = cur_node->next;
    }

    struct Node* lefthead = head;
    struct Node* righthead = cur_node->next;

    cur_node->next = NULL;

    lefthead = mergesortLL(lefthead,middle+1);
    righthead = mergesortLL(righthead,n-(middle+1));

    return mergeLL(lefthead,righthead);
}

void main()
{

    // printf("\nHow many testcases you want to input?: ");

    int no_of_test_cases;
    scanf("%d",&no_of_test_cases);

    int **arrays = (int **)malloc(no_of_test_cases * sizeof(int *));
    int sizes[no_of_test_cases];

    for(int i=0;i<no_of_test_cases;i++){
        
        // printf("\nEnter the size of array %d: ",i+1);
        int size1;
        scanf("%d",&size1);

        sizes[i] = size1;
        arrays[i] = (int *)malloc(size1 * sizeof(int));

        // printf("\nEnter %d elements for array %d, separated by spaces: ", size1, i + 1);
        
        for(int j=0;j<size1;j++){
            scanf("%d",&arrays[i][j]);
        }
    }

    printf("\n");

    for(int i=0;i<no_of_test_cases;i++){

                struct Node* LL_head = make_LL(arrays[i],sizes[i]);
                // printLL(LL_head,sizes[i]);
                LL_head = mergesortLL(LL_head,sizes[i]);
                printLL(LL_head,sizes[i]);
                free(LL_head);       
    }

    free(arrays);
}