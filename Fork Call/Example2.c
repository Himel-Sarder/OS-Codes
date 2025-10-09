#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	if(fork() || fork()){
		printf("Hello");
	}else{
		printf("\nNo Hello\n");
	}
	return 0;
}


/*
Process গঠন (fork() || fork()):

ধরি প্রথম fork():

Process	    fork() return	       Condition (fork() || fork())
------------------------------------------------------------
P1	        >0 (true)	           true → second fork short-circuits → prints "Hello"
C1	        0 (false)	           false → executes second fork

দ্বিতীয় fork (শুধু C1 এ হবে):

Process	    fork() return	       Condition (0 || fork())
------------------------------------------------------------
C1a (parent) >0 (true)	           0 || true → true → prints "Hello"
C1b (child)  0 (false)	           0 || 0 → false → prints "No Hello"

ASCII Diagram:

           ┌──────── fork() ─────────┐
           ↓                         ↓
         P1 (original)            C1 (child-1)
           │                        │
           │                        └─ second fork()
           │                           ┌────────────┐
           │                           ↓            ↓
           │                        C1a (parent)  C1b (child)
           │                           ↓            ↓
           │                        prints Hello   prints No Hello
           ↓
         prints Hello

Summary:
- Total processes: 3
- "Hello" printed: 2 times
- "No Hello" printed: 1 time
- Output order unpredictable (depends on scheduler)
*/
