#include "lru.h";
#include "page.h";

Page pages[MAX_PAGES]
int pageCount = 0;
int activePages = 0;

void LRU_tick() {
	int i;
	Page *currentPage;
	for (i = 0; i < pageCount; i++) {
		currentPage = pages[i];
		if (PAGE_isActive(currentPage)) {
			PAGE_tick(currentPage);
		}
	}
}

int LRU_createPage(void *content) {
	pages[pageCount++] = PAGE_createPage();
	return pageCount - 1;
}

void *LRU_accessPage(int index) {
	Page *page = pages[index];
	if (page == NULL)
		return NULL;
	PAGE_setAccessed(page);
	return PAGE_getContent(page);
}