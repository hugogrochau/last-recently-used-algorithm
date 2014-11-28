#include "lru.h";
#include "page.h";

/* private interface */

void LRU_accessPage(Page *page);

void LRU_inactivateOldestPage();

Page pages[MAX_PAGES]
int pageCount = 0;
int activePages = 0;

/* public functions */

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
    if (pageCount < MAX_PAGES) {
        pages[pageCount++] = PAGE_createPage();
        return pageCount - 1;
    } else {
        return -1;
    }
}

void *LRU_getPageContent(int index) {
    Page *page = pages[index];
    LRU_accessPage(page);
    return PAGE_getContent(page);
}

void LRU_setPageContent(int index, int content) {
    Page *page = pages[index];
    LRU_accessPage(page);
    PAGE_setContent(page, content);
}

/* private functions */

void LRU_accessPage(Page *page) {
    if (page != NULL) {
        if (!PAGE_isActive(page) && activePages > MAX_ACTIVE_PAGES) {
            LRU_inactivateOldestPage();
        } else if (activePages < MAX_ACTIVE_PAGES) {
            activePages++;
        }
        PAGE_setAccessed(page);
        PAGE_setActive(page);
    }
}

void LRU_inactivateOldestPage() {
    int i;
    Page *currentPage;
    Page *oldestPage = NULL;
    int oldestPageAge = -1;
    for (i = 0; i < pageCount; i++) {
        currentPage = pages[i];
        currentPageAge = PAGE_getLastAccessAge(currentPage);
        if (currentPageAge > oldestPageAge) {
            oldestPage = currentPage;
            oldestPageAge = currentPageAge;
        }
    }
    PAGE_setInactive(oldestPage);
}
