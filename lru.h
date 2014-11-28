#define MAX_ACTIVE_PAGES 16
#define MAX_PAGES 16*8

void LRU_tick();

int LRU_createPage(void *content);

void *LRU_getPageContent(int index);

void LRU_accessPage(Page *page);

void LRU_inactivateOldestPage();
