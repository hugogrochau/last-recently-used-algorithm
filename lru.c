#include <stdio.h>
#include "lru.h"
#include "page.h"

/* private interface */

void LRU_accessPage(int index);

void LRU_deactivateOldestPage();

Page *pages[MAX_PAGES];
int pageCount = 0;
int activePages = 0;

/* public functions */

void LRU_tick() {
    int i;
    Page *currentPage;
    printf("[LRU] tick\n");
    for (i = 0; i < pageCount; i++) {
        currentPage = pages[i];
        if (PAGE_isActive(currentPage)) {
            PAGE_tick(currentPage);
        }
    }
}

int LRU_createPage() {
    if (pageCount < MAX_PAGES) {
        pages[pageCount++] = PAGE_createPage();
        return pageCount - 1;
    } else {
        printf("[LRU] [ERRO] Nao pode mais criar paginas\n");
        return -1;
    }
}

void LRU_accessPage(int index) {
    Page *page = pages[index];
    if (page != NULL) {
        if (!PAGE_isActive(page) && activePages >= MAX_ACTIVE_PAGES) {
            LRU_deactivateOldestPage();
        } else if (activePages < MAX_ACTIVE_PAGES) {
            activePages++;
        }
        if (!PAGE_isActive(page)) {
            PAGE_resetPageAccessCount(page);
            PAGE_setActive(page);
            printf("[LRU] pagina (indice:%d) foi ativada (%d paginas ativas)\n", index, activePages);
        }
        PAGE_setAccessed(page);
        printf("[LRU] pagina (indice:%d) foi acessada\n", index);
    } else {
        printf("[LRU] [ERRO] Tentando acessar pagina nula\n");

    }
}

/* private functions */

void LRU_deactivateOldestPage() {
    int i;
    Page *currentPage;
    int oldestPage = -1;
    int oldestPageAge = -1;
    for (i = 0; i < pageCount; i++) {
        if (PAGE_getLastAccessAge(pages[i]) > oldestPageAge && PAGE_isActive(pages[i])) {
            oldestPage = i;
            oldestPageAge = PAGE_getLastAccessAge(pages[i]);
        }
    }
    printf("[LRU] pagina (indice:%d) foi desativada\n",  oldestPage);
    PAGE_setInactive(pages[oldestPage]);
}
