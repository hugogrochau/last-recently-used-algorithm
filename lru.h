#define MAX_ACTIVE_PAGES 16
#define MAX_PAGES 16*8

void LRU_tick();

int LRU_createPage();

void LRU_accessPage(int index);
