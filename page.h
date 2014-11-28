typedef struct page
{
	unsigned int accesses;
	void * content;
	unsigned char active;
} Page;


Page* PAGE_createPage(int id);

void* PAGE_getPageContent(Page *page);

void PAGE_resetPageAccessCount(Page *page);

void PAGE_destroyPage(Page *page);