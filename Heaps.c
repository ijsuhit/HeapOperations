#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<limits.h>


void createHeap(int *a, int n);
void maxHeapify(int *a, int i, int n);
void heapUtils(int *a, int n);
int getMax(int *a, int n);
void deleteMax(int *a, int n);
void updateElement(int *a, int n);
int increaseHeapElement(int *a, int key, int position, int n);
int decreaseHeapElement(int *a, int key, int position, int n);
void heapInsert(int *a, int heapSize, int n);
void printHeap(int *a, int n);
void printArray(int *a, int n);
void printSpaces(int n);


int main() {
    int *a;
    int n;
    int i;

    printf("Enter number of elements(n) : ");
    scanf("%d", &n);

    a = (int *) malloc(n * sizeof(int)); // Assuming value of n is proper and greater than 0
    for(i = 0; i < n;i++) {
        printf("Enter a[%d]: ", i);
        scanf("%d", &a[i]);
    }

    printf("\nArray before constructing the heap:\n");
    printArray(a, n);
    createHeap(a, n);

    printf("\nArray after constructing heap:\n");
    printArray(a, n);

    heapUtils(a, n);
    return 0;
}



// Creates the heap
void createHeap(int *a, int n) {
    int i;
    if(n < 1) {
        printf("\nError : Value of n is invalid");
        return;
    }
    for(i = n / 2 ;i >= 0;i--) { // leaf nodes start from (n / 2) + 1 where n is the number of elements
        maxHeapify(a, i, n);
    }
}



// Provided the child nodes are heaps, this method rearranges the structure so that the root fits in the heap
void maxHeapify(int *a, int i, int n) {
    int left = 2 * i + 1;
    int right = left + 1;
    int largest = i;

    if(left < n && a[left] > a[largest]) {
        largest = left;
    }
    if(right < n && a[right] > a[largest]) {
        largest = right;
    }

    if(largest != i) {
        a[largest] ^= a[i];
        a[i] ^= a[largest];
        a[largest] ^= a[i];
        maxHeapify(a, largest, n);
    }
}



// All the utility methods that can be performed are present here in the form of a menu
void heapUtils(int *a, int n) {
    int choice;
    int currentHeapSize = n;

    do {
        printf("\n\n*********************************");
        printf("\n*\t   Heap Utils Menu      *\n");
        printf("*********************************\n");

        printf("\n1. Get Max Element");
        printf("\n2. Update Element");
        printf("\n3. Insert New Element");
        printf("\n4. Delete Max Element");
        printf("\n5. Print Heap in Array Mode");
        printf("\n6. Print Heap in Tree Mode");
        printf("\n7. Clear Screen");
        printf("\n8. Exit");

        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\n\n************   Heap Max   *************************");
                printf("\n\n\tMax in the heap = %d", getMax(a, currentHeapSize));
                printf("\n\n************   End Heap Max   *********************");
                break;
            case 2:
                printf("\n\n************   Heap Update   *********************");
                updateElement(a, currentHeapSize);
                printf("\n\n************   End Heap Update   *********************");
                break;
            case 3:
                printf("\n\n************   Heap Insert   *********************");
                // heapSize ranges from 1 to n. So if heapSize >= n, the heap is already full and cannot accept a new element
                if(currentHeapSize >= n){
                    printf("\n\nError : Heap Overflow, could not perform heapInsert operation");
                } else {
                    heapInsert(a, currentHeapSize, n);
                    currentHeapSize++;
                }
                printf("\n\n************   End Heap Insert   *********************");
                break;
            case 4:
                printf("\n\n************   Heap Delete Max   *********************");
                // heapSize ranges from 1 to n. So if heapSize < 1, the heap is already empty and do not have any elements to delete
                if(currentHeapSize < 1) {
                    printf("\n\nError : Heap Underflow, could not perform deleteMax operation");
                } else {
                    deleteMax(a, currentHeapSize);
                    currentHeapSize--;
                }
                printf("\n\n************   End Heap Delete Max   *********************");
                break;
            case 5:
                printf("\n\n************   Print Heap - Array Mode   *********************");
                printArray(a, currentHeapSize);
                printf("\n************   End Print Heap - Array Mode   *********************");
                break;
            case 6:
                printf("\n\n************   Print Heap - Tree Mode   *********************");
                printHeap(a, currentHeapSize);
                printf("\n\n*************   End Print Heap - Tree Mode   ********************");
                break;
            case 7:
                system("cls");
                break;
            case 8:
                break;
            default:
                printf("\nError : Invalid choice");
        }
        if(choice != 7 && choice != 8) {
            printf("\n\n\tPress Enter to Continue...\t");
            fflush(stdin);
            getchar();
        }
    } while(choice != 8);
}



// Returns the max element in the heap
// If n value is less than 1, then INT_MIN is returned
int getMax(int *a, int n) {
    if(n < 1) {
        printf("\nError : Invalid n value");
        return INT_MIN;
    }
    return a[0];
}



// Updates element at the given position with the given key
void updateElement(int *a, int n) {
    int key;
    int position;
    int element;
    printf("\nEnter the position of the element you want to update (Index starts from 0): ");
    scanf("%d", &position);
    if(position >= n || position < 0) {
        printf("\nError : Position to update is invalid");
        return;
    }
    printf("\nEnter the value to which the element has to be updated : ");
    scanf("%d", &key);
    element = a[position];
    if(a[position] < key) {
        if(increaseHeapElement(a, key, position, n)) {
            printf("\nIncreased the element at position %d from %d to %d successfully\n", position, element, key);
        } else {
            printf("\nUpdation of element at position %d failed", position);
        }
    } else if(a[position] > key) {
        if(decreaseHeapElement(a, key, position, n)) {
            printf("\nDecreased the element at position %d from %d to %d successfully\n", position, element, key);
        } else {
            printf("\nUpdation of element at position %d failed", position);
        }
    } else {
        printf("Warning : The key and the element to be updated are equal");
    }
}



// Increases the heap element at the given position with given key
// Pre-condition : 'position' should be greater than or equal to zero and less than n
int increaseHeapElement(int *a, int key, int position, int n) {
    int parentIndex = (position - 1) / 2;

    if(a[position] > key) {
        printf("\nError : The key is less than the element at the given position");
        return 0;
    }
    a[position] = key;

    // Compare the element with its parent
    // For element at index i, its parent sits at (i - 1) / 2
    // This is because the index starts from 0
    // If the index starts from 1, parent for element at index i would be at index i / 2
    while(position >= 0 && a[position] > a[parentIndex]) {
        // Swap a[position] and a[parentIndex]
        a[position] ^= a[parentIndex];
        a[parentIndex] ^= a[position];
        a[position] ^= a[parentIndex];

        position = parentIndex;
        parentIndex = (parentIndex - 1) / 2;
    }
    return 1;
}



// Decreases the heap element at the given position with given key
// Pre-condition : 'position' should be greater than or equal to zero and less than n
int decreaseHeapElement(int *a, int key, int position, int n) {
    if(a[position] < key) {
        printf("\nError : The key is greater than the element at the given position");
        return 0;
    }
    a[position] = key;
    maxHeapify(a, position, n);
    return 1;
}



// Inserts a new element into the heap and organizes the elements again to heap
// If heapSize >= n, Heap Overflow error is printed
// Post-condition : The caller of this method should note that the size of the heap increases by 1 after this operation
void heapInsert(int *a, int heapSize, int n) {
    int key;
    printf("\nEnter an element to be inserted into the heap : ");
    scanf("%d", &key);

    a[heapSize - 1] = INT_MIN; // heapSize - 1 because heapSize ranges from 1 to n
    increaseHeapElement(a, key, heapSize - 1, n);
    printf("\nSuccessfully inserted %d into the heap", key);
}



// This method deletes the max element from the given heap and reorganizes the remaining elements again to heap
// If n value is less than 1, Heap Underflow error is printed
// Post-condition : The caller of this method should note that the size of the heap is reduced by 1
void deleteMax(int *a, int n) {
    int max;
    if(n < 1) {
        printf("\nError : Heap underflow, could not perform deleteMax operation");
        return;
    }

    max = a[0];
    a[0] = a[n - 1];
    maxHeapify(a, 0, n - 1);
    printf("\n\nAfter deleting max (%d), the array is : ", max);
    printArray(a, n - 1);
    printf("\nNote : The size of the heap is reduced by 1 after deleting the max");
}



// Method to show few properties of the given heap and print all the elements in the heap structure
void printHeap(int *a, int n) {
    int i;
    int limitIndex;                                 // Tells when to start a new line in the heap
    int heapNodes = n;
    int heapHeight = log2(n);                       // Height of the heap. It is zero when only one node is present
    int leafNodesStart = n / 2 + 1;                 // Gives the index where the leaf nodes start in the given heap
    int maxNodes = pow(2, heapHeight + 1) - 1;      // Maximum number of nodes possible with the given height
    int gap = maxNodes;                             // gap : this tells how much gap is to be given before starting a new level
                                                    //       Also gap * 2 + 1 is the gap between any two nodes of the same level
    if(n < 1) {
        printf("\nNo elements in the heap");
        return;
    }

    printf("\n\n*********************************");
    printf("\n*\t   Heap Details         *\n");
    printf("*********************************\n\n");
    printf("Number of nodes = %d\n", heapNodes);
    printf("Height of the heap = %d\n", heapHeight);
    printf("Leaf nodes start from %d (when counted from 1)\n", leafNodesStart);

    printf("\n\n*********************************");
    printf("\n*\t   Heap Structure       *\n");
    printf("*********************************\n\n");
    for(i = 0, limitIndex = 0;i < n;i++) {
        if(i == limitIndex) {
            // New level starts when i == limitIndex
            gap /= 2;
            printf("\n");
            printSpaces(gap);
            limitIndex = limitIndex * 2 + 1;
        }
        printf("%3d", a[i]);
        printSpaces(gap * 2 + 1);
    }
}



// Method to print any given array
void printArray(int *a, int n) {
    int i;
    if(n < 1) {
        printf("\nNo elements in the array");
        return;
    }
    printf("\n\nArray : ");
    for(i = 0; i < n;i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


// Utility method to print 3-spaces format n times
void printSpaces(int n) {
    int i;
    for(i = 0;i < n;i++) {
        printf("   ");
    }
}
