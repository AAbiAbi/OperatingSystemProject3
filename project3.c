#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define TURNS 10

// Initialize a mutex
pthread_mutex_t lock;
int CurrentID = 1;
int not_my_turn_count[NUM_THREADS] = {0};

void* thread_function(void* arg) {
    int threadId = *((int*) arg);
    int my_turn_count = 0;

    while(my_turn_count < TURNS) {
        // Acquire the mutex lock
        pthread_mutex_lock(&lock);

        if(CurrentID == threadId) {
            printf("My turn! Thread ID: %d\n", threadId);
            my_turn_count++;
            CurrentID++;
            if(CurrentID == 6) {
                CurrentID = 1;
            }
        } else {
            printf("Not My Turn! Thread ID: %d\n", threadId);
            not_my_turn_count[threadId - 1]++;
        }

        // Release the mutex lock
        pthread_mutex_unlock(&lock);
        // Give other threads a chance to acquire the lock
        usleep(100);
    }
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS];
    int i;

    // Initialize the mutex
    if(pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init has failed\n");
        return 1;
    }

    // Create threads
    for(i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = i + 1;
        if(pthread_create(&threads[i], NULL, thread_function, &threadIds[i]) != 0) {
            printf("Thread creation failed\n");
            return 1;
        }
    }

    // Join threads
    for(i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    // Print the "Not My Turn!" count for each thread
    for(i = 0; i < NUM_THREADS; i++) {
        printf("Thread %d printed 'Not My Turn!' %d times\n", i + 1, not_my_turn_count[i]);
    }

    return 0;
}
