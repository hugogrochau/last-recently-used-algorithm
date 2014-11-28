#include <stdlib.h>
#include "thread.h"

Thread *THREAD_createThread() {
    int i;
    Thread *thread = (Thread *) malloc(sizeof(Thread));
    if (thread == NULL) {
        return NULL;
    }
    thread->numPages = 0;
    thread->ticks = 0;

    return thread;
}