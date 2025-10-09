#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sort_ascending(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sort_descending(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] < arr[j + 1]) { 
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[10];
    int n = 10;
    pid_t pid;

    // Taking 10 integers as input
    printf("Enter 10 integers:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
    } 
    else if (pid == 0) {
        // Child process: Sort in descending order
        printf("\nChild Process....\n");
        sort_descending(arr, n);
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } 
    else {
        // Parent process: wait for child, then sort in ascending order
        wait(NULL);
        printf("\nParent Process....\n");
        sort_ascending(arr, n);
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}


// Enter 10 integers:
// 8 1 2 6 9 0 2 3 5 11

// Child Process....
// 11 9 8 6 5 3 2 2 1 0 

// Parent Process....
// 0 1 2 2 3 5 6 8 9 11
