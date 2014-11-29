O algoritmo de substitui��o de p�ginas por LRU foi implementado usando uma struct chamada thread para simular o comportamento dos processos na CPU. A struct usa vetor de inteiros para indexar as p�ginas.

As p�ginas s�o outra struct, com chars para fazer as marca��es de acesso e de posi��o.

No m�dulo LRU se encontram as fun��es de manipula��o das p�ginas, como de acesso e cria��o, e a fun��o tick, que � chamada a cada itera��o para fazer update das p�ginas. Se uma p�gina � acessada e j� tiverem 16 p�ginas n� mem�ria principal, o LRU simula um "swapping" da p�gina que ficou mais tempo sem ser acessada.

Quando alguma thread tem mais de quatro p�ginas, o limite do working set, a mais antiga � "swapped" e a nova � botada na mem�ria principal.

A fun��o main faz o papel de criar as threads a cada 5 segundos e de acessar p�ginas aleat�rias para cada thread cada 2 segundos.