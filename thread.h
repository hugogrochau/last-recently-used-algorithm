typedef struct thread
{
	int thread_id;
	unsigned char R; //R vector indicating access 0
	TPage pageTable[8]; //page table with 8 pages
	int numPages; //Number of pages in the page table 0 
	int activePages; //Number of the active pages in the table MAX 4 0
} Thread;

TThread THREAD_createThread(int id);

void THREAD_createPage(TThread thread);

void THREAD_accessPage(TThread thread, unsigned char idx);

void THREAD_updateAgePages(TThread thread);

TPage THREAD_getOldestPage(TThread thread);