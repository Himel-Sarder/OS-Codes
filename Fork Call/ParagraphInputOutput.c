#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char paragraph[500];
    printf("parent: Enter paragraph:\n");
    scanf("%[^\n]%*c", paragraph);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Fork failed! \n");
        return 1;
    }
    else if (pid == 0) {
        printf("\nchild process: printing the paragraph\n");
        printf("%s\n", paragraph);
    }
}
