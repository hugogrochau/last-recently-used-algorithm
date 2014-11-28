#define THREAD_MAX_PAGES 8

typedef struct thread {
    int pageIndexes[8];
    int numPages;
    int ticks;
} Thread;

Thread *THREAD_createThread();