#include <stdio.h>
#include <stdlib.h>

/* End of page definition */

/*********************** 
* THREAD INTERFACE 
***********************/


/*********************** 
* PAGE INTERFACE 
***********************/

TPage PAGE_createPage(int id);
/*
void PAGE_accessPage(unsigned char idx);
void PAGE_updateAgePages();
TPage PAGE_getOldestPage();
*/

/*********************** 
* FRAME INTERFACE 
***********************/

/*******************************************************************************************************************************************************************************************************
*  $FUN_NAME : FRAME_manipPage
*  UTILIZAR ESSA FUNCAO PARA ACESSAR AS PAGINAS 
*  CASO A PAGINA NAO ESTEJA NA LISTA DE FRAMES, ESSA PAGINA SERA INSERIDA NO LUGAR NA MAIS ANTIGA E UM ACESSO AUTOMATICO A ESSA PAGINA SERA FEITO
*  CASO ESSA PAGINA ESTEJA NA LISTA, APENAS UM ACESSO SERA FEITO
********************************************************************************************************************************************************************************************************/

/* Internal module interface */

/************************** 
* CONFIGS INTERFACE 
**************************/
void load(float *tick_time,float *thread_time,float *page_time,float *mini_time);
void generateLogAge();
void clearLogAge();
void clearLogFrame();
void generateLogFrame();
void clearLogExec();
void addExecLog(char *txt);
void printConfig();

/*********************** 
* GENERAL MEMORY 
***********************/
Frame frames[FRAME_COUNT];
int lstPos = 0;

/************************* 
* GLOBAL VARIABLES
*************************/

float tick_time, thread_time,page_time,time,mini_time;
TThread threads[THREAD_COUNT];
int numThreads = 0;

/************************* 
* MAIN FUNCTION
*************************/

int main(void)
{
	int i;

	// INICIALIZACAO DO PROGRAMA 
	load(&tick_time,&thread_time,&page_time,&mini_time);
	printConfig();
	clearLogAge();
	clearLogFrame();
	clearLogExec();
	FRAME_initFrames();
	addExecLog("[PROG] PROGRAMA INICIALIZADO\n");
	//  FIM DA INICIALIZAÃ‡ÃƒO
	
	addExecLog("[PROG] GENERATING INITIAL LOGS\n");
	generateLogAge();
	generateLogFrame();
	
	while (1)
	{
		time += mini_time;
		Sleep(mini_time * 1000);

	    // CRIA NOVA THREAD
		if (mini_time % 5 == 0)
		{
			if (numThreads < THREAD_COUNT)
			{
				threads[numThreads] = THREAD_createThread(numThreads);
				if (threads[numThreads] == NULL)
				{
					printf("Erro ao criar nova thread\n");
					exit(1);
				}
				numThreads++;
			}
			mini_time = 0.0;
		}
	
		//SE NAO HA THREADS SAI DO CONTINUA...
		if (numThreads == 0)
			continue;
		
		// CADA THREAD ACESSA 1 PAGINA RANDOMICA
		if (mini_time % 2 == 0)
		{
			//solicitaPagina();
		}
		
	}
	

	return 0;
}

/*
int main(void)
{
	load(&tick_time,&thread_time,&page_time);
	printConfig();
	clearLogAge();
	clearLogFrame();
	clearLogExec();
	FRAME_initFrames();
	
	while (numPages < 8)
	{
		pageTable[numPages] = PAGE_createPage(numPages);
		if (pageTable[numPages] == NULL)
		{
			printf("Error : Nao conseguiu criar uma pagina\n");
			exit(1);
		}
		printf("Uma nova pagina[%d] foi criada\n",numPages);
		numPages++;
		printf("Dormindo %.2f milisegundos...\n",page_time * 1000);
		Sleep(page_time * 1000); //Windows funciton
	}
	
	FRAME_manipPage(pageTable[0]);
	
	FRAME_manipPage(pageTable[2]);
	
	FRAME_manipPage(pageTable[4]);

	FRAME_manipPage(pageTable[5]);
	
	PAGE_updateAgePages();
	generateLogAge();
	generateLogFrame();

	FRAME_manipPage(pageTable[1]);
	PAGE_updateAgePages();
	generateLogFrame();
	
	FRAME_manipPage(pageTable[7]);
	PAGE_updateAgePages();
	generateLogFrame();

	FRAME_manipPage(pageTable[1]);
	PAGE_updateAgePages();
	generateLogFrame();

	FRAME_manipPage(pageTable[3]);	
	PAGE_updateAgePages();
	generateLogFrame();

	FRAME_manipPage(pageTable[3]);
	PAGE_updateAgePages();
	generateLogFrame();

	FRAME_manipPage(pageTable[3]);
	PAGE_updateAgePages();
	generateLogFrame();

	FRAME_manipPage(pageTable[0]);
	PAGE_updateAgePages();
	generateLogFrame();

	generateLogAge();
	
	return 0;
}*/

/*******************************
*  PAGE IMPLEMENTATION
*******************************/

TPage PAGE_createPage(int id)
{
	TPage page = (TPage) malloc (sizeof(struct page));
	addExecLog("[PAGE] Criando uma pagina\n");	
	if (page == NULL)
		return NULL;
	page->status = FALSE;	
	page->counter = 0;
	page->frameNumber = -1;
	page->id = id;
	return page;
}
/*
void PAGE_accessPage(unsigned char idx)
{
	if (idx > numPages)
		return;
	addExecLog("[PAGE] Acessando uma pagina\n");
		
	R = R | (0x01 << (7-idx));	// Make the access to the page and update vector 	
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
}*/



void load(float *tick_time,float *thread_time,float *page_time, float *mini_time)
{
	FILE *fp = fopen(CONFIG_FILE,"r");
	addExecLog("[LOAD] Carregando arquivos de configuracao\n");
	if (fp == NULL)
	{
		printf("Could not load file %s\n",CONFIG_FILE);
		exit(1);
	}
	
	fscanf(fp,"tick_time=%f\n"
	                "thread_time=%f\n"
					"page_time=%f\n"
					"mini_time=%f\n",tick_time,thread_time,page_time,mini_time);
	fclose(fp);
}

void clearLogExec()
{
	FILE *fp = fopen(LOG_EXEC_FILE,"w");
	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo de log[EXEC]\n");
		exit(1);
	}
	printf("Arquivo de log[EXEC] limpado\n");
	fclose(fp);
}

void addExecLog(char *txt)
{
	FILE *fp = fopen(LOG_EXEC_FILE,"a");
	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo de log de execucao\n");
		exit(1);
	}
	
	fprintf(fp,"%s",txt);
	fclose(fp);
}

void clearLogFrame()
{
	FILE *fp = fopen(LOG_FRAME_FILE,"w");
	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo de log[FRAME]\n");
		exit(1);
	}
	printf("Arquivo de log[FRAME] limpado\n");
	fclose(fp);
}

void generateLogFrame()
{
	int i;
	FILE *fp = fopen(LOG_FRAME_FILE,"a");
	
	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo de log[FRAME]\n");
		exit(1);
	}
	
	fprintf(fp,"----MEMORY OVERVIEW----\n");
	
	for (i = 0; i < 16; i++)
	{
		if (frames[i].page == NULL)
		{
			fprintf(fp,"FRAME[%d] : NO PAGE IN THIS FRAME\n",i);
		}
		else
		{
			fprintf(fp,"FRAME[%d] : ID-PAGE (%d)\n",i,frames[i].page->id);
		}
	}
	fprintf(fp,"\n\n");
	fclose(fp);
}

void clearLogAge()
{
	FILE *fp = fopen(LOG_AGE_FILE,"w");
	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo de log[AGE]\n");
		exit(1);
	}
	
	printf("Arquivo de log[AGE] limpado\n");
	fclose(fp);
}

void generateLogAge()
{
	FILE *fp = fopen(LOG_AGE_FILE,"a");
	unsigned char tmp;
	int i, j,w;
	
	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo de log[AGE]\n");
		exit(1);
	}
	
	for (i = 0; i < numThreads; i++)
	{
		if (threads[i] == NULL)
			continue;
		fprintf(fp,"---THREAD [%d]---\n",threads[i]->thread_id);
		fprintf(fp,"NUM PAGES RUNNING : %d\n",threads[i]->numPages);
		fprintf(fp,"R VECTOR : ");
		for (j = 0; j < 8; j++)
		{
			tmp = threads[i]->R & ((1 << 7-j));
			tmp >>= 7-j;
			fprintf(fp,"%d ",tmp);
		}
		fprintf(fp,"\n");	

		for (j = 0; j < threads[i]->numPages; j++)
		{
			fprintf(fp,"PAGE[%d] : ",j);
			for (w = 0; w < 8; w++)
			{
				tmp = threads[i]->pageTable[w]->counter & ((1 << 7-w));
				tmp >>= 7-w;
				fprintf(fp,"%d ",tmp);
			}
			fprintf(fp,"\n");
		}
		fprintf(fp,"\n\n");
		threads[i]->R = 0;
	}
}

/*
void generateLogAge()
{
	FILE *fp = fopen(LOG_AGE_FILE,"a");
	unsigned char tmp;
	int i, j;
	
	if (fp == NULL)
	{
		printf("Erro ao abrir arquivo de log[AGE]\n");
		exit(1);
	}
	
	for (i = 0; i < numThread; i++)
	{
		
	}
	
	fprintf(fp,"NUM PAGES RUNNING = %d\n",numPages);
	fprintf(fp,"R VECTOR = ");
	// Imprime o vetor R  (BIT A BIT) 
	for (i = 0; i < 8; i++)
	{
		tmp = R & ((1 << 7-i));
		tmp >>= 7-i;
		fprintf(fp,"%d ",tmp);
	}
	fprintf(fp,"\n");
	
	for (i = 0; i < numPages; i++)
	{
		fprintf(fp,"PAGE[%d] = ",i);
		for (j = 0; j < 8; j++)
		{
			tmp = pageTable[i]->counter & ((1 << 7-j));
			tmp >>= 7-j;
			fprintf(fp,"%d ",tmp);
		}
		fprintf(fp,"\n");			
	}
	fprintf(fp,"\n\n");
	R = 0;
} */

void printConfig()
{
	printf("tick_time = %.5f\n"
	         "thread_time = %.5f\n"
			 "page_time = %.5f\n",tick_time,thread_time,page_time);
}
