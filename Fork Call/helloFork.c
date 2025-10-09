#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
int main(){
	fork();
	printf("Hello Linux");
}

// Output : Hello LinuxHello Linux
