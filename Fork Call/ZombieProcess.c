#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    }

    // Child Process
    else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        printf("Child exiting... (Will become zombie)\n");
        exit(0);   // child মারা গেল
    }

    // Parent Process
    else {
        printf("Parent process: PID = %d\n", getpid());
        printf("Parent sleeping for 20 seconds...\n");
        
        sleep(20);  // parent ইচ্ছা করে wait() করবে না → child zombie হবে

        printf("Parent exiting.\n");
    }

    return 0;
}
