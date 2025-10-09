#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;
    pid = fork();

    if(pid > 0){
        printf("Parent : %d\n", pid);
    } else if(pid == 0){
        printf("Child : %d\n", pid);
    } else {
        printf("Fork failed!\n");
    }
    return 0;
}


/*
---------------------------------------------------------------------------------------------------------
If we coded :
int main(){
    pid_t pid;
    pid = fork();

    if(pid > 0){
        printf("Parent : %d", pid);
    } else if(pid == 0){
        printf("Child : %d", pid);
    } else {
        printf("Fork failed!\n");
    }
    return 0;
}

If we don't use \n
Then we can see output :
Parent : 1378

কেন কখনও Child দেখাচ্ছে না

এখানে দুটি সম্ভাবনা:
Child process শেষ হওয়ার আগেই Parent শেষ হয়ে গেছে
এবং টার্মিনাল তা দেখানোর আগেই prompt দেখাচ্ছে।

Buffering behavior — যখন stdout টার্মিনালে না লিখে বাফারে জমা থাকে (বিশেষ করে কোনো redirect থাকলে)।
তাহলে child-এর আউটপুট দেখা না-ও যেতে পারে।
----------------------------------------------------------------------------------------------------------

কেন Parent-এ "র‍্যান্ডম সংখ্যা" আসে?

কারণ Parent Process-এ fork() Child Process-এর PID রিটার্ন করে।
অর্থাৎ OS যেটা নতুন করে তৈরি করলো, সেই child-এর process number (PID)।

তাই Parent সবসময় একটা Positive সংখ্যা পায় — যা Child-এর PID।
আর যেহেতু প্রতিবার নতুন Child তৈরি হয়, তাই প্রতিবার PID আলাদা (তোমার টার্মিনালে যেমন 1364, 1378, 1390 ইত্যাদি)।

কেন Child সবসময় 0 পায়?
কারণ OS জানাতে চায়:
“তুমি এখন Child process।”
তাই Child process-এর ভিতর fork() সবসময় 0 রিটার্ন করে।
এটাই একমাত্র উপায় যেটা দেখে আমরা বুঝতে পারি —
এটা Parent নাকি Child কোড চলছে।

-----------------------------------------------------------------------------------------------------------
*/
