#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>

void collatz(int n){
   printf("%d ", n);
   if(n == 1 || n == 0) return;
   
   else if(n % 2 == 0){
   	collatz(n / 2);
   }else{
   	collatz(3 * n + 1);
   }
}

int main(){
   int n;
   printf("Enter a number : ");
   scanf("%d", &n);
   
   pid_t pid = fork();
   if(pid < 0){
   	printf("pid failed!");
   	exit(1);
   }else if(pid == 0){
   	printf("Child Process....\n");
   	collatz(n);
   	printf("Child End.\n");
   }else{
   	printf("Parent Process....\n");
   	printf("Parent Process Waiting....\n");
   	wait(NULL);
   	printf("Parent End.\n");
   }
}
