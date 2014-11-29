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
    for (i = 0; i < THREADS * THREAD_CREATION_INTERVAL; i++) {
        if (i % THREAD_CREATION_INTERVAL == 0) {
            printf("Thread (indice:%d) criada\n", numThreads);
            threads[numThreads] = (Thread *) THREAD_createThread();
            for (j = 0; j < THREAD_MAX_PAGES; j++) {
                threads[numThreads]->pageIndexes[j] = LRU_createPage();
                threads[numThreads]->numPages++;
            }
            numThreads++;
        }
        if (i % PAGE_ACCESS_INTERVAL == 0) {
            for (j = 0; j < numThreads; j++) {
                if (threads[j]->ticks % PAGE_ACCESS_INTERVAL == 0) {
                    randomIndex = rand() % THREAD_MAX_PAGES;
                    LRU_accessPage(threads[j]->pageIndexes[randomIndex]);
                }
                threads[j]->ticks++;
            }
        }
        LRU_tick();
        sleep(1);
    }

    return 0;
}