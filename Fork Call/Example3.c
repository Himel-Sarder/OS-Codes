#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	if(fork() && fork() && fork()){
		printf("Hello");
	}else{
		printf("\nNo Hello\n");
	}
	return 0;
}


/*
Process গঠন (fork() && fork() && fork()):

ধরি প্রথম fork():

Process	    fork() return	       Condition (fork() && fork() && fork())
----------------------------------------------------------------------
P1	        >0 (true)	           true → goes to second fork
C1	        0 (false)	           false → short-circuit → else → prints "No Hello"

দ্বিতীয় fork() (শুধু P1 এ হবে):

Process	    fork() return	       Condition (true && fork() && fork())
----------------------------------------------------------------------
P1	        >0 (true)	           true → goes to third fork
C2	        0 (false)	           false → else → prints "No Hello"

তৃতীয় fork() (শুধু P1 এ হবে):

Process	    fork() return	       Condition (true && true && fork())
----------------------------------------------------------------------
P1	        >0 (true)	           true → prints "Hello"
C3	        0 (false)	           false → else → prints "No Hello"

ASCII Diagram:

First fork:
           ┌──────── fork() ─────────┐
           ↓                         ↓
         P1 (parent)             C1 (child-1)
           │                        │
           │                        └─ else → "No Hello"

Second fork (P1 only):
           │
           └── fork()
                ┌────────────┐
                ↓            ↓
             P1 (still)     C2
                ↓            ↓
          goes to third fork else → "No Hello"

Third fork (P1 only):
                ↓
                ┌────────────┐
                ↓            ↓
             P1 (still)      C3
                ↓            ↓
             prints Hello   else → "No Hello"

Summary:
- Total processes: 4
- "Hello" printed: 1 time
- "No Hello" printed: 3 times
- Output order unpredictable (depends on scheduler)
*/
