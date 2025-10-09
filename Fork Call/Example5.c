#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    if(fork() || fork() && fork()){
        printf("Hello");
    } else {
        printf("\nNo Hello\n");
    }
    return 0;
}
    /*
    Process গঠন (fork() || fork() && fork()):

    Operator precedence: && আগে evaluate হয়, তারপর ||  
    অর্থাৎ:
        fork() || (fork() && fork())

    Step 1: প্রথম fork()
    --------------------------------
    Process	    fork() return	       Condition Evaluation
    P1	        >0 (true)	           true → short-circuit → skips (fork() && fork()) → prints "Hello"
    C1	        0 (false)	           false → evaluates (fork() && fork())

    Step 2: দ্বিতীয় fork() (শুধু C1 এ হবে)
    ----------------------------------------
    Process	    fork() return	       Condition Evaluation
    C1a (parent) >0 (true)	           true && third fork() → evaluates third fork()
    C1b (child)  0 (false)	           false && ... → false → else → prints "No Hello"

    Step 3: তৃতীয় fork() (শুধু C1a এ হবে)
    ----------------------------------------
    Process	    fork() return	       Condition Evaluation
    C1a	        >0 (true)	           true && true → true → prints "Hello"
    C1c	        0 (false)	           true && false → false → else → prints "No Hello"

    ASCII Diagram:

    First fork:
               ┌──────── fork() ─────────┐
               ↓                         ↓
           P1 (original)               C1
               │                         │
               │                         └─ evaluates fork() && fork()
               │                               ┌────────────┐
               │                               ↓            ↓
               │                           C1a (parent)  C1b (child)
               │                               ↓            ↓
               │                         evaluates 3rd fork  No Hello
               │                               ↓
               │                           third fork
               │                               ┌────────────┐
               │                               ↓            ↓
               │                           C1a (still)    C1c
               │                               ↓            ↓
               │                             Hello        No Hello
               ↓
           Hello (P1)

    Summary:
    - Total processes: 4
    - "Hello" printed: 2 times
    - "No Hello" printed: 2 times
    - Output order unpredictable (depends on scheduler)
    */

