#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    if(fork() && fork()) {
        printf("Hello");
    } else {
        printf("No Hello");
    }
    return 0;
}

/*
Process গঠন

ধরি প্রথম fork():

Process	    fork() return	      Condition (fork() && fork())
P1	        >0 (true)	          true → goes to second fork
C1	        0 (false)	          false → else → prints "No Hello"

C1 output: "No Hello"

দ্বিতীয় fork (শুধু P1 এ হবে):
Process	    fork() return	       Condition (true && fork())
P1	        >0 (true)	           true → prints "Hello"
C2	        0 (false)	           false → prints "No Hello"



           ┌──────── fork() ─────────┐
           ↓                         ↓
         P1 (parent)             C1 (child-1)
           │                        ↓
           │                        └─➤ else → "No Hello"
           │
           └── second fork()
                ┌────────────┐
                ↓            ↓
             P1 (still)     C2 (child-2)
                ↓            ↓
          if(true && true)   if(true && false)
              → "Hello"         → "No Hello"
*/
