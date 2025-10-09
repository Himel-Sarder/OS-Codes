#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 10

void print_array(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

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
    int arr[SIZE] = {5, 2, 9, 3, 2, 1, 4, 8, 6, 7};
    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if(pid == 0) {
        // Child process
        int temp[SIZE];
        for(int i = 0; i < SIZE; i++) 
            temp[i] = arr[i];

        printf("Child: Descending order:\n");
        sort_descending(temp, SIZE);
        print_array(temp, SIZE);
    } else {
        // Parent process
        wait(NULL);  // Wait for child to finish
        int temp[SIZE];
        for(int i = 0; i < SIZE; i++) 
            temp[i] = arr[i];

        printf("Parent: Ascending order:\n");
        sort_ascending(temp, SIZE);
        print_array(temp, SIZE);
    }

    return 0;
}


// Output
// Child: Descending order:
// 9 8 7 6 5 4 3 2 2 1 
// Parent: Ascending order:
// 1 2 2 3 4 5 6 7 8 9
