#include <stdlib.h>
#include "page.h"

Page * PAGE_createPage(int owner) {
    Page *page = (Page *) malloc (sizeof(Page));
    if (page == NULL) {
        return NULL;
    }
    page->counter = 0;
    page->accessed = 0;
    page->active = 0;
    page->owner = owner;
    return page;
}

void PAGE_setActive(Page *page) {
    page->active = 1;
}

void PAGE_setInactive(Page *page) {
    page->active = 0;
}

void PAGE_setAccessed(Page *page) {
    page->accessed = 1;
}

int PAGE_getLastAccessAge(Page *page) {
    int i;
    for (i = 0; i < 8; i++) {
        if ((page->counter << i) & 0x80) {
            break;
        }
    }
    return i;
}
int PAGE_getOwner(Page *page) {
    return page->owner;
}

unsigned char PAGE_isActive(Page *page) {
    return page->active;
}

unsigned char PAGE_isAccessed(Page *page) {
    return page->accessed;
}

void PAGE_tick(Page *page, int RBit) {
    page->counter >>= 1;
    if (RBit)
        page->counter |= 0x80;
    page->accessed = 0;
}

void PAGE_destroyPage(Page *page) {
    free(page);
    page = NULL;
}
