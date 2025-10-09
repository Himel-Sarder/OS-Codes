#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); 

    if (pid == 0) {
        printf("I am Child process\n");
    } else if (pid > 0) {
        printf("I am Parent process\n");
    } else {
        printf("fork Error!\n");
    }

    return 0;
}

// Output : 
// I am Parent process
// I am Child process
