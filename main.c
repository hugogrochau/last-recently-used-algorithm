#include <stdio.h>
#include <stdlib.h>
#include "lru.h"
#include "thread.h"

#define THREADS 16
#define THREAD_CREATION_INTERVAL 5
#define PAGE_ACCESS_INTERVAL 2

Thread *threads[THREADS];
int numThreads = 0;

int main(void) {
    int i, j;
    int randomIndex;
    int newThreadIndex;
    srand(time(NULL));

    for (i = 0; i < THREADS * THREAD_CREATION_INTERVAL; i++) {
        printf("Tick %d - ", i);
        LRU_tick();
        
        if (i % THREAD_CREATION_INTERVAL == 0) {
            newThreadIndex = numThreads;
            printf("Thread %d criada\n", newThreadIndex);
            threads[newThreadIndex] = (Thread *) THREAD_createThread();
            for (j = 0; j < THREAD_MAX_PAGES; j++) {
                threads[newThreadIndex]->pageIndexes[j] = LRU_createPage(newThreadIndex);
                threads[newThreadIndex]->numPages++;
            }
            numThreads++;
        }

        for (j = 0; j < numThreads; j++) {
            if (threads[j]->ticks % PAGE_ACCESS_INTERVAL == 0) {
                randomIndex = rand() % THREAD_MAX_PAGES;
                LRU_accessPage(threads[j]->pageIndexes[randomIndex], j);
            }
            threads[j]->ticks++;
        }

        sleep(1);
    }

    return 0;
}