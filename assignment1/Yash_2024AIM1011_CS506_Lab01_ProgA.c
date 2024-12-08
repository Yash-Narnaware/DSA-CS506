#include <stdio.h>
#include <stdlib.h>


void bubble_sort(int* nums,int n) {

    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if (nums[i] >= nums[j]){
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;                
            }
        }
    }

    for(int i=0;i<n;i++){
        printf("%d ",nums[i]);
    }
    
    printf("\n");
}


void selection_sort(int* nums,int n) {

    for(int i=0;i<n;i++){
        int min = i;
        for(int j=i;j<n;j++){
            if (nums[j] < nums[min]) {
                min = j;
            }
        }
        int temp = nums[min];
        nums[min] = nums[i];
        nums[i] = temp;

    }
    for(int i=0;i<n;i++){
        printf("%d ",nums[i]);

    }
    printf("\n");

}


void merge(int *list1,int lb,int mid,int ub) {
    
    int i = lb;
    int j = mid + 1;
    int k = lb;
    int temp[ub+1];
    
    while (i <= mid && j <= ub){
        
        if (list1[i] <= list1[j]){
            temp[k] = list1[i];
            i++;
            k++;
        } else {
            temp[k] = list1[j];
            j++;
            k++;
        }
    }
    
    if (i > mid){
        while (j <= ub){
            temp[k] = list1[j];
            j++;
            k++;
        }
    } else {
        while (i <= mid){
            temp[k] = list1[i];
            i++;
            k++;
        }
    }
    
    for(int m=lb;m<ub+1;m++){
        list1[m] = temp[m];
    }
}


void mergesort(int* list1,int lb,int ub) {
    
    if (lb < ub){
        
        int mid = (lb + ub)/2;
        
        mergesort(list1,lb,mid);
        mergesort(list1,mid+1,ub);
        merge(list1,lb,mid,ub);
    }  
}

void insertion_sort(int* p,int size){
    
    for(int i=1;i<size;i++){
        int temp = p[i];
        int j = i - 1;
        
        while (j >= 0 && p[j] > temp){
            p[j+1] = p[j];
            j--;
        }
        p[j+1] = temp;
    }
    
    for(int i=0;i<size;i++){
        printf("%d ",p[i]);
    }   
    printf("\n");
    
}


int partition(int* list1,int size,int lb,int ub){
    
    int piviot = list1[lb];
    int start = lb;
    int end = ub;
    
    while (start < end){
        while ((start < size) && (list1[start] <= piviot)){
            start++;
        }
        
        while (list1[end] > piviot){
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


void quicksort(int* list1,int size,int lb,int ub){
    
    if (lb < ub){
        int loc = partition(list1,size,lb,ub);
        quicksort(list1,size,lb,loc-1);
        quicksort(list1,size,loc+1,ub);
    }
    
}



void main()
{
    int dc[] = {1,4,7,6,5,4,3};

    // printf("\n");
    // printf("1.Bubble Sort\n");
    // printf("2.Selection Sort\n");
    // printf("3.Merge Sort\n");
    // printf("4.Insertion Sort\n");
    // printf("5.Quick Sort\n");
    // printf("\n");

    // printf("Which sorting algorithm you want to use?: ");

    int algo_choice;
    scanf("%d",&algo_choice);

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
    

    // printf("\n\nSorted arrays:\n");
    printf("\n");

    switch (algo_choice) {
        
        case 1:
            for(int i=0;i<no_of_test_cases;i++){
                bubble_sort(arrays[i],sizes[i]);
                
            }
            free(arrays);
            break;
               
        case 2:
            for(int i=0;i<no_of_test_cases;i++){
                selection_sort(arrays[i],sizes[i]);
            }
            free(arrays);
            break;

        case 3:
            for(int i=0;i<no_of_test_cases;i++){
                mergesort(arrays[i],0,sizes[i]-1);
            }
            
            for(int i=0;i<no_of_test_cases;i++){
                for(int j=0;j<sizes[i];j++){
                    printf("%d ",arrays[i][j]);
                }
                printf("\n");
            } 
            free(arrays);
            break;

        case 4:
            for(int i=0;i<no_of_test_cases;i++){
                insertion_sort(arrays[i],sizes[i]);
            }
            free(arrays);
            break;

        case 5:
            for(int i=0;i<no_of_test_cases;i++){
                quicksort(arrays[i],sizes[i],0,sizes[i]-1);
            }
            
            for(int i=0;i<no_of_test_cases;i++){
                for(int j=0;j<sizes[i];j++){
                    printf("%d ",arrays[i][j]);
                }
                printf("\n");
            } 
            free(arrays);
            break;
        
    }
}
