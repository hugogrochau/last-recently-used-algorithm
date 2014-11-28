typedef struct page
{
    unsigned char counter;
    unsigned char accessed;
    unsigned char active;
    int content;
} Page;

Page* PAGE_createPage(int id);

void PAGE_setActive(Page *page);

void PAGE_setAccessed(Page *page);

void PAGE_setPageContent(Page *page, int content);

int PAGE_getPageContent(Page *page);

unsigned int PAGE_getLastAccessAge(Page *page);

void PAGE_isActive(Page *page);

void PAGE_isAccessed(Page *page);

void PAGE_resetPageAccessCount(Page *page);

void PAGE_tick(Page *page, unsigned char accessed);

void PAGE_destroyPage(Page *page);
