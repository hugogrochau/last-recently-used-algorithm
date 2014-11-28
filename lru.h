#define MAX_FRAMES 4
#define MAX_FRAMES_GLOBAL 16


void load(float *tick_time,float *thread_time,float *page_time,float *mini_time);

void generateLogAge();

void clearLogAge();

void clearLogFrame();

void generateLogFrame();

void clearLogExec();

void addExecLog(char *txt);

void printConfig();