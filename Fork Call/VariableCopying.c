#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int x = 5;
    pid_t pid = fork();
    if (pid < 0) { 
    	printf("Error"); 
    	exit(1); 
    }
    if (pid == 0) {
        x += 5; // child modifies x
        printf("Child: x = %d\n", x);
        exit(0);
    } else {
        sleep(1); // allow child to print
        x += 10; // parent modifies x
        printf("Parent: x = %d\n", x);
    }
    return 0;
}

// Output : 
// Child: x = 10
// Parent: x = 15
