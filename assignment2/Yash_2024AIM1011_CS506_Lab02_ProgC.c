#include<stdio.h>
#include<stdlib.h>

void swap(int* arr, int a,int b) {

    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

//function to convert array to max heap
void heapify(int* arr,int idx, int size){

    if (idx < 0){
        return;
    }

    //if both chidren of a node is not present
    if ((2*idx+1) >= size && (2*idx+2) >= size){
        heapify(arr,idx - 1, size);
    }

    //if both children of a node exists
    if ((2*idx+1) < size && (2*idx+2) < size){
        int max_child;

        if (arr[2*idx+1] >= arr[2*idx+2]){
            max_child = 2*idx + 1;
        } else {
            max_child = 2*idx + 2;
        }

        if (arr[max_child] > arr[idx]){
            swap(arr,max_child,idx);
            heapify(arr,max_child,size);
        } else {
            heapify(arr,idx-1,size);
        }
    } else if ((2*idx+1 < size) && (2*idx+2) >= size) {  //if only left child of a node exists

        if (arr[2*idx+1] > arr[idx]){
            swap(arr,2*idx+1,idx);
            heapify(arr,2*idx+1,size);
        } else {
            heapify(arr,idx-1,size);
        }
    } 

}


void main(){

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

        //first we need max heap(can use min heap also) then swap heap top with bottom and now consider array excluding last element and arrange the swapped heap top to correct place
        heapify(arrays[i],sizes[i]-1,sizes[i]);
        swap(arrays[i],0,sizes[i]-1);

        for (int j=1;j<sizes[i];j++){
            heapify(arrays[i],0,sizes[i]-j);
            swap(arrays[i],0,sizes[i]-1-j);
        }

        for (int k=0;k<sizes[i];k++){
            printf("%d ",arrays[i][k]);
        }
        printf("\n");           
    }
    free(arrays);
}