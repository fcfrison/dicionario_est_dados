#ifndef ESTRUTURAS_DICIONARIO_H_INCLUDED
#define ESTRUTURAS_DICIONARIO_H_INCLUDED
#define MAX_PALAVRA 100
#define MAX_DEFINICAO 18000



typedef struct noArvAVL{
   char palavra[MAX_PALAVRA]; //Ao inves de ter uma estrutura de tamanho fixo, talvez seja interessante ter uma estrutura cujo tamanho de memoria eh alocado dinamicamente.
   char descricao[MAX_DEFINICAO];
   int alt;
   struct noArvAVL *esq;
   struct noArvAVL *dir;
} NoArvAVL;

typedef struct{
   struct noArvAVL *raiz;
   int nPalavras;
} AVLPlus;

//Funcao que aloca dinamicamente o espaco de memohria necessahrio para uma arvore do tipo AVL.
AVLPlus* criaAVL();

//Funcao que faz a busca dentro da AVL de palavras iguais.
NoArvAVL *buscaPalavrasIguais(AVLPlus *arvore, char *palavra);

//Funcao que insere uma palavra nova ao dicionahrio, bem como a sua definicao. Retorna 1, se possivel a insercao e 0 se nao for possivel.
int insereAVL(AVLPlus *arv, char *palavra, char *descricao);

//Funcao que permite a remocao de uma palavra e sua definicao do dicionario. Retorna 1 se possivel a remocao e 0 se nao possivel a remocao.
int removeInfoAVL(AVLPlus *arv, char *palavra);

//Funcao que faz a leitura de documentos externo.
void leDicionario(AVLPlus *arvore);

//Funcao que permite a edicao de palavra jah cadastrada. Retorna 1 se possivel a edicao e 0 se nao possivel.
int editarPalavra(AVLPlus *arvore, char *palavra, char *nova_palavra);

// Funcao que permite a edicao de definicao de palavra jah cadastrada. Retorna 1 se possivel a edicao e 0 se nao possivel.
int editaDefinicao(AVLPlus *arvore, char *palavra, char *descricao);

//Funcao que permite a impressao das palavras jah cadastradas em terminal, bem como faz com que arquivo de texto com as palavras seja gerado.
//Retorna 1 se possivel a impressao e a geracao do arquivo de texto salvo em disco e 0 caso contrario.
int salvaAVL(AVLPlus *arv, char letra);

//Funcao que permite a geracao arquivo de texto com as palavras e sua definicoes.
//Retorna 1 se possivel gerar e 0 do contrario.
int salvaAVL_definicoes(AVLPlus *arv, char letra);

//Funcao que destroi a AVL (libera os espacos de memohria alocados dinamicamente.
void destroiAVL(AVLPlus *arv);


#endif // ESTRUTURAS_DICIONARIO_H_INCLUDED
