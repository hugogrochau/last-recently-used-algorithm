#include <stdio.h>
#include "lru.h"
#include "page.h"

/* private interface */

void LRU_deactivateOldestPage();

void LRU_deactivateOldestPageByOwner(int owner);

int LRU_getNumberOfOwnedPages(int owner);

Page *pages[MAX_PAGES];
int pageCount = 0;
int activePages = 0;

/* public functions */

void LRU_tick() {
    int i;
    Page *currentPage;
    printf("Paginas ativas (total:%d):", activePages);
    for (i = 0; i < pageCount; i++) {
        currentPage = pages[i];
        if (PAGE_isActive(currentPage)) {
            printf(" %d ", i);
            PAGE_tick(currentPage, 0);
        }
    }
    printf("\n");
}

int LRU_createPage(int owner) {
    if (pageCount < MAX_PAGES) {
        pages[pageCount++] = PAGE_createPage(owner);
        return pageCount - 1;
    } else {
        printf("[ERRO] Nao pode mais criar paginas\n");
        return -1;
    }
}

void LRU_accessPage(int index, int owner) {
    Page *page = pages[index];
    if (page != NULL) {
        
        if (!PAGE_isActive(pages[index])) {
            PAGE_setActive(page);
            activePages++;
            printf("Pagina %d da thread %d foi ativada\n",  index, owner);
        }

        PAGE_tick(page, 1);
        PAGE_setAccessed(page);
        printf("Pagina %d da thread %d foi acessada\n", index, owner);

        if (LRU_getNumberOfActiveOwnedPages(owner) > MAX_ACTIVE_PAGES_PER_OWNER) {
            LRU_deactivateOldestPageByOwner(owner);
        } else if (activePages > MAX_ACTIVE_PAGES) {
            LRU_deactivateOldestPage();
        }

    } else {
        printf("[ERRO] Tentando acessar pagina nula\n");
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
    printf("Pagina %d da thread %d com idade %d foi desativada por exceder o limite de paginas por usuario\n",  oldestPage, PAGE_getOwner(pages[oldestPage]), oldestPageAge);
    PAGE_setInactive(pages[oldestPage]);
    activePages--;
}

void LRU_deactivateOldestPageByOwner(int owner) {
    int i;
    Page *currentPage;
    int oldestPage = -1;
    int oldestPageAge = -1;
    for (i = 0; i < pageCount; i++) {
        if (PAGE_getLastAccessAge(pages[i]) > oldestPageAge && PAGE_isActive(pages[i]) && PAGE_getOwner(pages[i]) == owner) {
            oldestPage = i;
            oldestPageAge = PAGE_getLastAccessAge(pages[i]);
        }
    }
    printf("Pagina %d da thread %d com idade %d foi desativada por exceder o limite de paginas por thread\n",  oldestPage, owner, oldestPageAge);
    PAGE_setInactive(pages[oldestPage]);
    activePages--;
}

int LRU_getNumberOfActiveOwnedPages(int owner) {
    int i, count = 0;
    Page *currentPage;
    for (i = 0; i < pageCount; i++) {
        currentPage = pages[i];
        if (PAGE_getOwner(currentPage) == owner && PAGE_isActive(currentPage)) {
            count++;
        }
    }
    return count;
}