#include "page.h";

Page * PAGE_createPage() {
    Page *page = (Page *) malloc (sizeof(Page));
    printf("{PAGE} - Pagina criada\n"); 
    if (page == NULL) {
        printf("{PAGE} - Erro a criar pagina")
        return NULL;
    }
    page->counter = 0;
    page->accessed = 0;
    page->active = 0;
    return page;
}

void PAGE_setActive(Page *page) {
    page->active = 1;
}

void PAGE_setInactive(Page *page) {
    page->active = 1;
}

void PAGE_setAccessed(Page *page) {
    page->accessed = 1;
}

void PAGE_setPageContent(Page *page, int content);
    if (page == NULL) {
        printf("{PAGE} - Pagina nao existe");
        return NULL;
    }
    page->content = content;
}

int PAGE_getPageContent(Page *page){
    if (page == NULL) {
        printf("{PAGE} - Pagina nao existe");
        return NULL;
    }
    return page->content; 
}

unsigned int PAGE_getLastAccessAge(Page *page) {
    unsigned int i;
    for (i = 0; i < 8; i++) {
        if ((page->counter << i) & 0x80))
            break;
    }
    return i;
}

void PAGE_isActive(Page *page) {
    return page->active;
}

void PAGE_isAccessed(Page *page) {
    return page->acessed;
}

void PAGE_resetPageAccessCount(Page *page) {
    page->counter = 0;
}

void PAGE_tick(Page *page) {
    page->counter >>= 1;
    if (PAGE_isActive(page))
        page->counter |= 0x80;
}
void PAGE_destroyPage(Page *page) {
    free(page);
    page = NULL;
}
