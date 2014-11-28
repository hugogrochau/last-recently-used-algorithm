typedef struct page
{
    unsigned char counter;
    unsigned char accessed;
    unsigned char active;
} Page;

Page* PAGE_createPage();

void PAGE_setActive(Page *page);

void PAGE_setAccessed(Page *page);

int PAGE_getLastAccessAge(Page *page);

unsigned char PAGE_isActive(Page *page);

unsigned char PAGE_isAccessed(Page *page);

void PAGE_resetPageAccessCount(Page *page);

void PAGE_tick(Page *page);

void PAGE_destroyPage(Page *page);
