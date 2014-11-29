typedef struct page
{
    unsigned char counter;
    unsigned char accessed;
    unsigned char active;
    int owner;
} Page;

Page* PAGE_createPage(int owner);

void PAGE_setActive(Page *page);

void PAGE_setAccessed(Page *page);

int PAGE_getLastAccessAge(Page *page);

int PAGE_getOwner(Page *page);

unsigned char PAGE_isActive(Page *page);

unsigned char PAGE_isAccessed(Page *page);

void PAGE_tick(Page *page, int Rbit);

void PAGE_destroyPage(Page *page);
