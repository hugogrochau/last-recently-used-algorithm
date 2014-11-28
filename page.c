#include "page.h";

Page * PAGE_createPage)
{
	Page *page = (Page *) malloc (sizeof(Page));
	printf("{PAGE} - Pagina criada\n");	
	if (page == NULL) {
		printf("{PAGE} - Erro a criar pagina")
		return NULL;
	}
	page->accesses = 0;
	page->active = 0;	
	return page;
}


void *PAGE_getPageContent(Page *page){
	if (page == NULL) {
		printf("{PAGE} - Pagina nao existe");
		return NULL;
	}
	return page->content; 
}

void PAGE_resetPageAccessCount(Page *page) {
	page->acesses = 0;
}

void PAGE_destroyPage(Page *page) {
	free(page);
	page = NULL;
}