#include<stdio.h>
#include<stdlib.h>

//function to find the median of 3 or less number of elements 
int findmedian(int *arr,int n){

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if (arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return arr[n/2];
}



int mom7(int *arr, int arr_size1,int lb,int ub) {

    int arr_size = ub - lb + 1;

    if (arr_size <= 7){
        int arr_cpy[arr_size];
        for(int i = 0;i < arr_size; i++){
            arr_cpy[i] = arr[i+lb];
        }
        return findmedian(arr_cpy,arr_size);
    }

    //dividing array in size of 3
    int number_of_subarrays = (arr_size + 6)/7;

    int medians[number_of_subarrays];

    int i = 0;
    for (i = 0; i < arr_size/7; i++) {
        int cpy_arr2[7];

        for (int j = 0; j < 7; j++){
            cpy_arr2[j] = arr[lb + i * 7 + j];
        }
        medians[i] = findmedian(cpy_arr2,7);
    }

    if (arr_size%5 != 0){
        int cpy_arr3[arr_size%7];

        for (int j = 0; j < arr_size%7; j++){
            cpy_arr3[j] = arr[lb + i * 7 + j];
        }
        medians[i] = findmedian(cpy_arr3, arr_size%7);
        i++;
    }

    // printf("Medians: ");
    // for (int k=0;k<number_of_subarrays;k++){
    //     printf("%d ",medians[k]);
    // }

    mom7(medians,number_of_subarrays,0,number_of_subarrays-1);
  
 
}

//partition function for quicksort
int partition(int *list1,int size,int lb,int ub,int pivot){
    
    int pivot_idx = -1;
    for (int i = lb; i <= ub; i++) {
        if (list1[i] == pivot) {
            pivot_idx = i;
            break;
        }
    }

    //my partition function code is such that it takes lb to be pivot 
    // Thats the reasoon I am swapping pivot with lb
    int temp = list1[lb];
    list1[lb] = list1[pivot_idx];
    list1[pivot_idx] = temp;
    
    int start = lb;
    int end = ub;
    
    while (start < end){
        while ((start < size) && (list1[start] <= pivot)){
            start++;
        }
        while (list1[end] > pivot){
            end--;
        }
        
        if (start < end){
            int temp = list1[start];
            list1[start] = list1[end];
            list1[end] = temp;    
        }
    }
    
    int temp2 = list1[lb];
    list1[lb] = list1[end];
    list1[end] = temp2;

    return end;
}


void quicksort(int *list1,int size,int lb,int ub){
    
    if (lb < ub){
        //using median of medians only to select a good pivot element
        int piviot = mom7(list1,size,lb,ub);
        // printf("pivot: %d\n",piviot);
        // return;
        // printf("piviot element: %d\n",piviot);
        int loc = partition(list1,size,lb,ub,piviot);
        quicksort(list1,size,lb,loc-1);
        quicksort(list1,size,loc+1,ub);
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

        quicksort(arrays[i],sizes[i],0,sizes[i]-1);

        for(int j=0;j<sizes[i];j++){
            printf("%d ",arrays[i][j]);
        }
        printf("\n");
    }
    free(arrays);

    // printf("\n%d",res);

}