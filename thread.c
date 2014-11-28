#include "thread.h";

Thread * THREAD_createThread(int id)
{
	int i;
	Thread *thread = (Thread *) malloc (sizeof(struct thread));
	if (thread == NULL) {
		printf("{ERRO} {THREAD} - Problema criando thread");
		return NULL;
	}
	printf("{THREAD} - Thread criada\n");
	thread->R = 0;
	thread->thread_id = id;
	thread->activePages = 0;
	thread->numPages = MAX_PAGES;
	addExecLog("[THREAD] Criando todas as paginas da nova thread\n");
	for (i = 0; i < thread->numPages; i++)
	{
		thread->pageTable[i] = PAGE_createPage(i);
		if (thread->pageTable[i] == NULL)
		{
			printf("Erro ao criar nova pagina\n");
			exit(1);
		}
	}	
	return thread;
}

void THREAD_createPage(TThread thread)
{	
	thread->pageTable[thread->numPages] = PAGE_createPage(thread->numPages);
	addExecLog("[THREAD] Criando uma nova pagina\n");
	if (thread->pageTable[thread->numPages] == NULL)
	{
		printf("Error : Nao conseguiu criar uma pagina\n");
		exit(1);
	}
	printf("Uma nova pagina[%d] foi criada\n",thread->numPages);
	thread->numPages++;
}

void THREAD_accessPage(TThread thread, unsigned char idx)
{
	if (idx > thread->numPages)
		return;
	addExecLog("[THREAD] Acessando uma pagina\n");
	thread->R = thread->R | (0x01 << (7-idx));	// Make the access to the page and update vector 	
}

void THREAD_updateAgePages(TThread thread)
{
	int i = 0;
	addExecLog("[THREAD] Atualizando TP(tabela de processos) de acordo com o vetor R(indica acesso)\n");	
	for (i = 0; i < thread->numPages; i++)
	{
		if (thread->pageTable[i]->counter)
			thread->pageTable[i]->counter >>= 1;
			
		if ( thread->R & (0x01 << (7 - i)) )
			thread->pageTable[i]->counter = thread->pageTable[i]->counter | (0x01 << 7);			
	}
}

TPage THREAD_getOldestPage(TThread thread)
{
	int i=0;
	unsigned char old = 0xFF;
	int oldId = -1;
	addExecLog("[THREAD] Procurando por pagina mais velha na TP(tabela de processos)\n");
	for (i = 0; i < thread->numPages; i++)
	{
		if (thread->pageTable[i]->counter < old && thread->pageTable[i]->status == TRUE)
		{
			old = thread->pageTable[i]->counter;
			oldId = i;
		}
	}
	
	if (oldId == -1)
		return NULL;
	return thread->pageTable[oldId];
}

