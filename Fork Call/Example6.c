#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    if (fork() && fork() || fork()) {
        printf("A");
    } else {
        printf("B");
    }
    return 0;
}

// AABB
