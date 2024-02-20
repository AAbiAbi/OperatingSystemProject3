
## The project3.c program
 starts by defining constants for the number of threads and the number of times each thread should get its turn. It declares a mutex for synchronization and a shared variable CurrentID initialized to 1, along with an array to count "Not My Turn!" events for each thread.

Each thread runs thread_function, where it enters a loop that continues until the thread has printed "My Turn!" 10 times. Inside the loop, the thread locks the mutex to safely access CurrentID. If CurrentID matches the thread's ID, it prints "My Turn!", increments CurrentID, resets CurrentID to 1 if it reaches 6, and counts a successful turn. Otherwise, it prints "Not My Turn!", along with its ID, and increments the count for "Not My Turn!" events.

In the main function, the mutex is initialized, threads are created with unique IDs, and then the program waits for all threads to complete using pthread_join. After all threads are done, the mutex is destroyed, and the program prints the count of "Not My Turn!" events for each thread before exiting.

The line #define TURNS 10 defines a symbolic constant named TURNS with the value 10. This means wherever TURNS appears in the code, the preprocessor will replace it with 10 before the code is compiled. In the context of the provided code, TURNS is used to specify the number of times each thread should print "My Turn!" before it terminates.

The line not_my_turn_count[threadId - 1]++; in the code is incrementing the count of "Not My Turn!" messages for the corresponding thread. Each thread has an ID between 1 and 5, and the not_my_turn_count array has indices from 0 to 4, matching threads 1 to 5 respectively. When the thread with a particular ID finds that CurrentID does not match its ID, it increments its corresponding counter in the not_my_turn_count array to keep track of how many times it could not enter the critical section.

## result
```bash
abi@abi-virtual-machine:~/Desktop/project3$ gcc -o project3 project3.c -lpthread
abi@abi-virtual-machine:~/Desktop/project3$ 
abi@abi-virtual-machine:~/Desktop/project3$ ./project3 
My turn! Thread ID: 1
My turn! Thread ID: 2
Not My Turn! Thread ID: 1
My turn! Thread ID: 3
Not My Turn! Thread ID: 2
Not My Turn! Thread ID: 1
Not My Turn! Thread ID: 2
Not My Turn! Thread ID: 3
Not My Turn! Thread ID: 1
Not My Turn! Thread ID: 3
Not My Turn! Thread ID: 2
Not My Turn! Thread ID: 1
My turn! Thread ID: 4
Not My Turn! Thread ID: 2
Not My Turn! Thread ID: 3
Not My Turn! Thread ID: 1
Not My Turn! Thread ID: 4
My turn! Thread ID: 5
My turn! Thread ID: 1
My turn! Thread ID: 2
My turn! Thread ID: 3
My turn! Thread ID: 4
My turn! Thread ID: 5
My turn! Thread ID: 1
My turn! Thread ID: 2
My turn! Thread ID: 3
My turn! Thread ID: 4
My turn! Thread ID: 5
Not My Turn! Thread ID: 3
My turn! Thread ID: 1
My turn! Thread ID: 2
Not My Turn! Thread ID: 4
Not My Turn! Thread ID: 5
My turn! Thread ID: 3
Not My Turn! Thread ID: 1
Not My Turn! Thread ID: 2
My turn! Thread ID: 4
My turn! Thread ID: 5
Not My Turn! Thread ID: 3
Not My Turn! Thread ID: 2
My turn! Thread ID: 1
Not My Turn! Thread ID: 4
Not My Turn! Thread ID: 5
Not My Turn! Thread ID: 3
My turn! Thread ID: 2
Not My Turn! Thread ID: 1
Not My Turn! Thread ID: 4
Not My Turn! Thread ID: 5
Not My Turn! Thread ID: 1
Not My Turn! Thread ID: 2
My turn! Thread ID: 3
My turn! Thread ID: 4
My turn! Thread ID: 5
My turn! Thread ID: 1
My turn! Thread ID: 2
My turn! Thread ID: 3
My turn! Thread ID: 4
My turn! Thread ID: 5
My turn! Thread ID: 1
Not My Turn! Thread ID: 3
My turn! Thread ID: 2
Not My Turn! Thread ID: 4
Not My Turn! Thread ID: 5
Not My Turn! Thread ID: 1
My turn! Thread ID: 3
My turn! Thread ID: 4
Not My Turn! Thread ID: 2
My turn! Thread ID: 5
My turn! Thread ID: 1
Not My Turn! Thread ID: 3
My turn! Thread ID: 2
Not My Turn! Thread ID: 4
Not My Turn! Thread ID: 5
Not My Turn! Thread ID: 1
My turn! Thread ID: 3
Not My Turn! Thread ID: 2
My turn! Thread ID: 4
My turn! Thread ID: 5
My turn! Thread ID: 1
My turn! Thread ID: 2
My turn! Thread ID: 3
My turn! Thread ID: 4
My turn! Thread ID: 5
My turn! Thread ID: 1
Not My Turn! Thread ID: 5
My turn! Thread ID: 2
My turn! Thread ID: 3
My turn! Thread ID: 4
My turn! Thread ID: 5
Thread 1 printed 'Not My Turn!' 10 times
Thread 2 printed 'Not My Turn!' 9 times
Thread 3 printed 'Not My Turn!' 8 times
Thread 4 printed 'Not My Turn!' 6 times
Thread 5 printed 'Not My Turn!' 6 times


```

Each thread is attempting to access the CurrentID variable, and when it gets its turn (i.e., when CurrentID matches the thread's ID), it prints "My turn!" followed by its ID, increments the CurrentID, and checks for a reset condition. If CurrentID is not equal to the thread's ID, it prints "Not My Turn!" along with its ID.

The final part of the output shows the count of "Not My Turn!" prints for each thread. These counts provide a measure of how many times each thread had to wait for its turn, which is reflective of the thread scheduling and synchronization behavior of your system.

This output demonstrates that mutual exclusion is being enforced correctly, as "My turn!" is printed in a mutually exclusive manner and the CurrentID is being managed properly by each thread. The threads are working in a round-robin fashion according to the CurrentID, and the mutex is ensuring that only one thread can enter its critical section at a time.