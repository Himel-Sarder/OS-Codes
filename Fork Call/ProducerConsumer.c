#include <stdio.h>      // printf() ব্যবহার করতে লাগে
#include <stdlib.h>     // rand(), exit() ইত্যাদি ফাংশনের জন্য
#include <unistd.h>     // fork(), sleep() এর জন্য (Unix/Linux এর header)
#include <sys/mman.h>   // mmap() ব্যবহার করে shared memory তৈরি করার জন্য
#include <time.h>       // সময় অনুযায়ী random number তৈরি করতে srand(time(NULL))

#define SIZE 5          // buffer-এর সাইজ ৫ — ধরো ৫ সিটের বাস, ৫টির বেশি যাত্রী ওঠা যাবে না


int main() {
    // Shared memory for buffer and count
    int *buffer = mmap(NULL, SIZE * sizeof(int), PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);


/*
mmap() RAM এ একটা shared জায়গা তৈরি করে, যেটা parent আর child — দুজনেই একই address থেকে access করে।
ধরো দুজনের সামনে একটাই টেবিল আছে

Producer টেবিলে ফল রাখে
Consumer সেই একই টেবিল থেকেই তুলে খায়

এটাই হলো mmap() ব্যবহারের আসল কারণ।

এখন লাইনটি ভেঙে ব্যাখ্যা করি:
  
int *buffer = mmap(NULL, SIZE * sizeof(int),
SIZE * sizeof(int) → Example: যদি SIZE = 5 হয় → 5টি integer রাখার জায়গা মানে ২০ byte RAM রিজার্ভ করবে।
এটি একটা টেবিল বানালাম যেটায় ৫টি আইটেম রাখা যাবে।

PROT_READ | PROT_WRITE,
মানে — এই টেবিলে সবাই লিখতে এবং পড়তে পারবে।
শুধু পড়তে পারলে Producer result দিতে পারতো না

MAP_SHARED | MAP_ANONYMOUS,
MAP_SHARED → বলছে, "এই memory দুই process মিলে share করবে"
MAP_ANONYMOUS → এই memory কোনো file থেকে আসেনি, সরাসরি RAM থেকে নেওয়া।
মানে ফাইল কাউন্টার ছাড়াই সরাসরি টেবিল বানানো হয়েছে।

-1, 0
যেহেতু file নেই (ANONYMOUS) → file descriptor -1, offset 0।

মানে: "আমার ফাইল দরকার নেই, শুধু টেবিল দাও।"
*/
  
    int *count = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *count = 0; // initialize count -> শুরুতে টেবিলে (buffer) কোনো আইটেম নেই, তাই count = 0

  
    int in = 0, out = 0; // in → Producer কোথায় বসাবে। out → Consumer কোথা থেকে নেবে। ধরো in হলো যেখানে আপনি প্লেট রাখবেন আর out হলো যেখানে খাবেন।

  
    pid_t pid;
  
    srand(time(NULL)); // rand() যেন প্রতিবার ভিন্ন সংখ্যা দেয়, তাই srand() দিয়ে seed করলাম।

    pid = fork(); // একটা প্রোগ্রাম ছিল → fork() করলাম → এখন দুটি প্রক্রিয়া তৈরি হলো: মূলটা → Parent (Producer)    নতুনটা → Child (Consumer)

    if (pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    } 

      
    else if (pid == 0) {   // pid == 0 মানে → এই প্রক্রিয়াটি Child, তাই এই অংশ চলবে Consumer এর জন্য।
        // Child = Consumer
        while (1) {   // এটার মানে — Consumer কখনো থামে না, সে চিরকাল টেবিল চেক করতে থাকবে (Continuous loop = Infinite hungry consumer)
            if (*count > 0) { // এখানে Consumer বলছে — "দেখি টেবিলে কিছু আছে কিনা..."       count > 0 মানে টেবিলে খাবার আছে           count == 0 হলে কিছু করবে না → (খাবার না থাকলে অপেক্ষা করবে)
                int item = buffer[out];   // Consumer টেবিলের out ইন্ডেক্স থেকে একটি খাবার তুলে নিল         যেমন: "ঠিক আছে, index 2 তে একটা আপেল ছিল, আমি খেয়ে নিলাম"
                printf("Consumer consumed: %d from index %d\n", item, out);  // কনজিউমার বলল ➡ "আমি index %d থেকে %d নম্বর আইটেম খেয়েছি"  (এটা শুধু output দেখানোর জন্য)



              
                out = (out + 1) % SIZE;  
// ------------------------------------------------------------------------------------------------
// এই লাইনটা: out = (out + 1) % SIZE;
// এখানে % SIZE কেন ব্যবহার করা হয়েছে, সেটা বুঝলে তুমি circular buffer পুরোপুরি বুঝে যাবে
//
// Buffer কল্পনা করো একটা গোল টেবিল হিসেবে:
//
// ধরো, তোমার buffer এর SIZE = 5
// Index:   0   1   2   3   4
//          ↑
//          শুরু এখান থেকে (out pointer)
//
// Consumer যখন খায়, তখন out এক ধাপ সামনে যায়:
// প্রথমে  → out = 0
// খাওয়ার পর → out = 1
// তারপর   → out = 2
// এরপর    → out = 3
// তারপর   → out = 4
// এখান পর্যন্ত সব ঠিক আছে
//
// কিন্তু out++ করলে → out = 5 হয়,
//    কিন্তু buffer[5] বলে কিছু নেই, কারণ শেষ index হলো 4
//
// এখানেই % SIZE কাজ করে!
//
// out = (out + 1) % SIZE; মানে:
//
// আগে out ছিল | Then (out + 1) | (out + 1) % SIZE | Final out (Result)
// ------------|----------------|------------------|--------------------
//      0      |      1         |   1 % 5 = 1      |         1
//      1      |      2         |   2 % 5 = 2      |         2
//      2      |      3         |   3 % 5 = 3      |         3
//      3      |      4         |   4 % 5 = 4      |         4
//      4      |      5         |   5 % 5 = 0      |         0 ← ব্যস, আবার শুরুতে ফিরে এল 
//
// ----------------------------------------------------------------------------------------------------

                (*count)--;  // সে যেহেতু একটা খাবার খেয়ে ফেলেছে, তাই টেবিলে আইটেমের সংখ্যা ১টি কমল।
                sleep(1);  // একটু আরাম করে নেই
            }
        }
    } 

      
    else {
        // Parent = Producer
        while (1) {   // Producer কখনো থামে না — সে বারবার buffer এ data দিতে চেষ্টা করবে (infinite loop)।
            if (*count < SIZE) {  // Producer প্রথমে চেক করে ➡ buffer এ এখনও জায়গা আছে কিনা?   count < SIZE মানে — "টেবিলে এখনো খালি প্লেট আছে"     যদি buffer ফুল (count == SIZE) হয়, তবে Producer অপেক্ষা করবে (কিছু করবে না)।
                int item = rand() % 100;  // Producer random একটা সংখ্যা তৈরি করে (0 থেকে 99-এর মধ্যে)।    ভাবো — Producer একটা random খাবার রান্না করল
                // 3 Digit Random number -> int item = (rand() % 900) + 100;
                // 4 Digit -> int item = (rand() % 9000) + 1000;
                // 1 Digit -> int item = rand() % 10;
                buffer[in] = item; // Producer খাবারটা buffer[in] অবস্থানে রাখল।
                printf("Producer produced: %d at index %d\n", item, in);   // Producer বলছে ➡ আমি index %d তে %d আইটেম রাখলাম
                in = (in + 1) % SIZE; // Producer বলল ➡ "পরের বার পরের জায়গায় রাখবো।" (Circular Buffer Logic)     আবার 0 তে ফিরে আসবে (কারণ % SIZE ব্যবহার হয়েছে)
                (*count)++; // যেহেতু একটি নতুন item যোগ হয়েছে, তাই মোট count ১ বাড়ল
                sleep(1); // একটা খাবার দিলাম, এখন আরাম করে নিই, consumer খেতে পারবে
            }
        }
    }

    return 0;
}
