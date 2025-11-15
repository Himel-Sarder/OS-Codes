#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    }
    else if(pid == 0){
    	printf("Cild Process PID = %d\n", getpid());
    	printf("Child sleeping...\n");
    	sleep(10);
    	printf("Child process turns into Ophan Process. New PID = %d\n", getppid());
    	printf("Child Killed.\n");
    }
    else{
    	printf("Parent Process PID = %d\n", getpid());
    	printf("Parent Exiting...\n");
    	printf("Parent Killed.\n");
    	exit(0);
    }
}
