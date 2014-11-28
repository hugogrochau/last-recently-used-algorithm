#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;

	load(&tick_time,&thread_time,&page_time,&mini_time);
	printConfig();
	clearLogAge();
	clearLogFrame();
	clearLogExec();
	FRAME_initFrames();
	addExecLog("[PROG] PROGRAMA INICIALIZADO\n");
	
	addExecLog("[PROG] GENERATING INITIAL LOGS\n");
	generateLogAge();
	generateLogFrame();
	
	while (1)
	{
		time += mini_time;
		Sleep(mini_time * 1000);

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
	
		if (numThreads == 0)
			continue;
		
		if (mini_time % 2 == 0)
		{
			//solicitaPagina();
		}
		
	}
	

	return 0;
}