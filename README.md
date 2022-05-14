# dicionario_est_dados
Essa aplicação foi desenvolvida como projeto final da disciplina 'INF01126 - Estruturas De Dados I' ministrada pela Universidade Federal do Rio Grande do Sul, semetre 2021/1.
Uma descrição completa da mesma pode ser encontrada em:

https://www.youtube.com/watch?v=fdenZ0zXhGQ

## OBSERVAÇÕES SOBRE A IMPLEMENTAÇÃO DO ALGORITMO

•	1) Os testes realizados no algoritmo foram executados em um computador que possui o sistema operacional “Windows 10 Home Single Language”, em que o tipo de sistema é classificado como “Sistema operacional de 64 bits, processador baseado em x64”.

•	2) O documento “retorno.txt” é de onde foram retirados as palavras/definições. Tal documento foi gerado a partir de acesso ao GitHub do seguinte usuário: https://github.com/matthewreagan/WebstersEnglishDictionary#dictionary_compactjson .
O arquivo propriamente dito foi extraído de:
https://github.com/matthewreagan/WebstersEnglishDictionary/blob/master/dictionary_compact.json. 
O arquivo está em formato JSON e precisou de tratamento, para que pudesse ser conver-tido para ‘.txt’. Como tenho muito mais familiaridade com a linguagem de programação Python do que a linguagem C, de forma que para trabalhar facilmente com arquivos no formato JSON eu teria que importar um módulo que não é padrão (como é o caso de <stdio.h>, <stdlib.h>, etc.) da linguagem C, optei por fazer essa transformação em Python. O arquivo “programa_auxiliar_extracao_JSON.py” contém o script que faz essa transformação. 

•	3) As palavras inseridas devem ter caracteres que pertençam à tabela ASCII (https://www.ime.usp.br/~pf/algoritmos/apend/ascii.html). O algoritmo não foi pensado para palavras que contenham caracteres fora dessa tabela. Afinal de contas, a ideia central do trabalho é demonstrar uma aplicação que contenha alguma estrutura de dados estudada no semestre, de forma que questões ligadas à codificação de caracteres me parecem ser secundárias. 

•	4) Não consegui implementar um tratamento adequado para a questão de espaços ao final de palavras. Assim, palavras com a mesma grafia, mas que tenham uma quantidade diferente de espaços serão consideradas como distintas (ainda que do ponto de vista do senso comum, elas sejam iguais). 

•	5) É feita uma verificação de palavras iniciadas por caracteres numéricos, de forma que não é possível inseri-las. Porém, não foi feita uma verificação no sentido de se verificarem todos os caracteres inseridos para checar se há números no meio da palavra. Isso foi feito por arbítrio (me pareceu mais razoável ter palavras com números no meio, mas não no começo). 

•	6) Ao se escolher a opção “7.Imprimir lista de palavras no terminal e salvá-la em arquivo de texto.”, será gerado um arquivo de texto que terá nome “lis-ta_palavras_inciadas_por_CARACTERE_DIGITADO.txt”, em que onde se lê “CARACTERE_DIGITADO”, aparecerá o caractere escolhido. 

•	7) Ao se escolher a opção “8.Salvar em arquivo de texto lista de palavras iniciadas por de-terminada letra e a sua definicao.”, será gerado um arquivo cujo nome possui o seguinte modelo “lista_definicao_palavras_inciadas_por_ CARACTERE_DIGITADO.txt”, em que é válida a mesma explicação dada acima. 

