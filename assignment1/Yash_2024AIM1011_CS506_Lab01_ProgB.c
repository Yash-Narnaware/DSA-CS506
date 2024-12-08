#include <stdio.h>
#include <stdlib.h>

int ternary_search(int* p,int l,int r,int target){
    
    while (l <= r){
        int mid1 = l + ((r-l)/3);
        int mid2 = r - ((r-l)/3);
        
        if (p[mid1] == target){
            return mid1;
        }
        
        if (p[mid2] == target){
            return mid2;
        }
        
        if ((target > p[mid1]) && (target < p[mid2])){
            l = mid1 + 1;
            r = mid2 - 1;
        } else if (p[mid1] > target){
            r = mid1 - 1;
        } else {
            l = mid2 + 1;
        }    
    }
    return -1;
}


void main() {

    //printf("\nHow many testcases you want to input?: ");

    int no_of_test_cases;
    scanf("%d",&no_of_test_cases);

    int **arrays = (int **)malloc(no_of_test_cases * sizeof(int *));

    int sizes[no_of_test_cases];
    int targets[no_of_test_cases];

    for(int i=0;i<no_of_test_cases;i++){
        
        //printf("\nEnter the size of array %d: ",i+1);
        int size1;
        scanf("%d",&size1);

        sizes[i] = size1;

        arrays[i] = (int *)malloc(size1 * sizeof(int));

        //printf("\nEnter %d elements for array %d, separated by spaces: ", size1, i + 1);
        
        for(int j=0;j<size1;j++){
            scanf("%d",&arrays[i][j]);
        }

	int target;
        //printf("\nEnter the target to search in array: ");
	scanf("%d",&target);

	targets[i] = target;

    }

    for(int i=0;i<no_of_test_cases;i++){
        int res = ternary_search(arrays[i],0,sizes[i]-1,targets[i]);

	if (res != -1) {
	    printf("\nTarget %d found at index %d",targets[i],res);

	} else {

	    printf("\nTarget %d not found in array",targets[i]);

	}
                
    }
    free(arrays);
    printf("\n");

}
