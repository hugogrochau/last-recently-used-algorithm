#include "page.h";

TPage PAGE_createPage(int id)
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


void *PAGE_getPageContent(Page *page)
{
	if (page == NULL) {
		printf("{PAGE} - Pagina nao existe");
		return NULL;
	}
	return page->content; 
}

void PAGE_updateAgePages()
{
	int i = 0;
	addExecLog("[PAGE] Atualizando TP(tabela de processos) de acordo com o vetor R(indica acesso)\n");	
	for (i = 0; i < numPages; i++)
	{
		if (pageTable[i]->counter)
			pageTable[i]->counter >>= 1;
			
		if (R & (0x01 << (7 - i)) )
			pageTable[i]->counter = pageTable[i]->counter | (0x01 << 7);			
	}
}

TPage PAGE_getOldestPage()
{
	int i=0;
	unsigned char old = 0xFF;
	int oldId = -1;
	addExecLog("[PAGE] Procurando por pagina mais velha na TP(tabela de processos)\n");
	for (i = 0; i < numPages; i++)
	{
		if (pageTable[i]->counter < old && pageTable[i]->status == TRUE)
		{
			old = pageTable[i]->counter;
			oldId = i;
		}
	}
	
	
	if (oldId == -1)
		return NULL;
	return pageTable[oldId];
}

void FRAME_initFrames()
{
	int i;
	addExecLog("[FRAME] Inicializando lista de frames\n");	
	lstPos = 0;
	for (i = 0; i < FRAME_COUNT; i++)
		frames[i].page = NULL;
}

void FRAME_manipPage(TThread thread, unsigned char idx)
{
	if ( (idx < 0 || idx > 7) || (thread == NULL) || (thread->pageTable[idx] == NULL) )
		return;
	if (thread->pageTable[idx]->status == TRUE)
	{
		addExecLog("[FRAME] Pagina ja esta na lista de frames\n");
		THREAD_accessPage(thread,idx);
	}
	else
	{
		addExecLog("[FRAME] Pagina nao estava na lista de frames\n");
		FRAME_insertPage(thread, thread->pageTable[idx]);
	}
}

void FRAME_insertPage(TThread thread, TPage page)
{
	TPage oldPage;
	int oldPos = -1;		
	addExecLog("[FRAME] Inserindo pagina na lista de frames\n");
	if (thread->activePages >= WS)
	{
		addExecLog("[FRAME] Numero de paginas para determinada thread eh maior ou igual ao working set\n");

		oldPage = THREAD_getOldestPage(thread);
		
		if (oldPage != NULL)
		{
			oldPos = oldPage->frameNumber;
			FRAME_removePage(oldPage);			
		}
		else
		  printf("[FRAME] PAGINA FOI NULA\n");
	}
	else
	{
		thread->activePages++;
	}
	if (oldPos != -1)
	{
		frames[oldPos].page = page;
    	page->frameNumber = oldPos; 
	}
	else
	{
 		frames[lstPos].page = page;
    	page->frameNumber = lstPos; 
		lstPos++;
	}
	addExecLog("[FRAME] Pagina inserida com sucesso na lista de frames\n");

	page->status = TRUE;
	THREAD_accessPage(thread,page->id);
	if (lstPos == 16)
		lstPos = 0;
}


int FRAME_checkPageInMemory(TPage page)
{
	addExecLog("[FRAME] Checando se pagina esta na memoria...\n");
	return page->status;
}

void FRAME_removePage(TPage page)
{		
	int numFrame = page->frameNumber;
	addExecLog("[FRAME] Removendo pagina\n");
	if (numFrame < 0 || numFrame > 15)
		return;
	
	frames[numFrame].page = NULL;
	page->status = FALSE;
	page->counter = 0;
	lstPos--;
}
