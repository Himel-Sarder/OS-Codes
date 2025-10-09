#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    if(fork() || fork() || fork()){
        printf("Hello");
    } else {
        printf("\nNo Hello\n");
    }
    return 0;
}

    /*
    Process গঠন (fork() || fork() || fork()):

    Step 1: প্রথম fork()
    --------------------------------
    Process	    fork() return	       Condition (fork() || fork() || fork())
    P1	        >0 (true)	           true → short-circuit → skips remaining forks → prints "Hello"
    C1	        0 (false)	           false → executes second fork

    Step 2: দ্বিতীয় fork() (শুধু C1 এ হবে)
    ----------------------------------------
    Process	    fork() return	       Condition (0 || fork() || fork())
    C1a (parent) >0 (true)	           0 || true → true → prints "Hello"
    C1b (child)  0 (false)	           0 || 0 → false → executes third fork

    Step 3: তৃতীয় fork() (শুধু C1b এ হবে)
    ---------------------------------------
    Process	    fork() return	       Condition (0 || 0 || fork())
    C1b parent    >0 (true)	           0 || 0 || true → prints "Hello"
    C1b child     0 (false)	           0 || 0 || 0 → false → prints "No Hello"

    ASCII Diagram:

    First fork:
               ┌──────── fork() ─────────┐
               ↓                         ↓
           P1 (original)               C1
               │                         │
               │                         └─ second fork()
               │                            ┌────────────┐
               │                            ↓            ↓
               │                         C1a (parent)  C1b (child)
               │                            ↓            ↓
               │                         prints Hello   third fork()
               │                                         ┌────────────┐
               │                                         ↓            ↓
               │                                     C1b parent    C1b child
               │                                         ↓            ↓
               │                                     prints Hello  prints No Hello
               ↓
           prints Hello

    Summary:
    - Total processes: 5
    - "Hello" printed: 3 times
    - "No Hello" printed: 1 time
    - Output order unpredictable (depends on scheduler)
    */


