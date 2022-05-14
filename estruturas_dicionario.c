#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "estruturas_dicionario.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(__unix__)
#define clear_screen() system("clear")
#endif

// Funcoes ligadas ao balanceamento da arvore binaria.
int alturaNodoAVL(NoArvAVL *raiz);
int fatorBalanceamentoNodoAVL(NoArvAVL *raiz);
NoArvAVL* rotacaoEsquerdaAVL(NoArvAVL *raiz);
NoArvAVL* rotacaoDireitaAVL(NoArvAVL *raiz);
NoArvAVL* rotacaoDireitaEsquerdaAVL(NoArvAVL *raiz);
NoArvAVL* rotacaoEsquerdaDireitaAVL(NoArvAVL *raiz);

//Funcao que converte palavras de minusculo para maiusculo.
char *conversaoParaMaiuscula (char *palavra);

//Funcao que segmenta as definicoes em strings de tamanho 100 ou menos, buscando uma boa visualizacao no arquivo de saida txt.
void splitString(NoArvAVL *raiz, char letra, FILE* fp);

//Funcao que gera o efeito grafico de barra de carregamento ao se iniciar o programa.
void efeitoCarregaArquivo();

AVLPlus* criaAVL(){
    AVLPlus *arvore = (AVLPlus*)malloc(sizeof(AVLPlus)); //Cria dinamicamente o espaco necessario para uma AVL;
    arvore->raiz=NULL;
    arvore->nPalavras=0;
    return arvore;
}
//Funcao auxiliar para pesquisa de palavras na arvore.//
NoArvAVL *buscaPalavrasIguaisAux(NoArvAVL *nodo,char *palavra, NoArvAVL *temp){
    if (nodo!=NULL){
        if (strcmp(nodo->palavra,palavra)==0){
            temp = nodo;
            return temp;
            }
        else if (strcmp(palavra,nodo->palavra)==-1){
            return buscaPalavrasIguaisAux(nodo->esq, palavra, temp);
            }
        else if (strcmp(palavra,nodo->palavra)==1){
            return buscaPalavrasIguaisAux(nodo->dir,palavra,temp);
            }
        }
}

//Funcao para pesquisa de palavras na arvore.
NoArvAVL *buscaPalavrasIguais(AVLPlus *arvore, char *palavra){
    NoArvAVL *temp = (NoArvAVL*)malloc(sizeof(NoArvAVL));
    temp=NULL;
    palavra=conversaoParaMaiuscula(palavra);
    if (arvore->raiz==NULL){
        return temp; //retorna 'NULL' se a palavra nao foi encontrada e 'temp'!=NULL se a palavra foi encontrada.
    }
    else{
        temp = buscaPalavrasIguaisAux(arvore->raiz, palavra, temp);
        return temp;
    }
}

// Funcao que insere um elemento na AVL
NoArvAVL* insereNodoAVL(NoArvAVL *raiz, char *palavra, char *descricao){
   if(raiz == NULL){
      raiz = (NoArvAVL*)malloc(sizeof(NoArvAVL));
      strcpy(raiz->palavra,palavra);
      strcpy(raiz->descricao,descricao);
      raiz->alt = 1;
      raiz->esq = NULL;
      raiz->dir = NULL;
      return raiz;
   }
   else if(strcmp(palavra,raiz->palavra)==-1)
      raiz->esq = insereNodoAVL(raiz->esq, palavra, descricao);
   else if(strcmp(palavra,raiz->palavra)==1)
      raiz->dir = insereNodoAVL(raiz->dir, palavra, descricao);

   raiz->alt = alturaNodoAVL(raiz);
   int FB = fatorBalanceamentoNodoAVL(raiz);
   int FBEsq = fatorBalanceamentoNodoAVL(raiz->esq);
   int FBDir = fatorBalanceamentoNodoAVL(raiz->dir);

   if (FB == 2 && FBEsq == 1){
      raiz = rotacaoDireitaAVL(raiz);
   }
   else if (FB == -2 && FBDir == -1){
      raiz = rotacaoEsquerdaAVL(raiz);
   }
   else if (FB == -2 && FBDir == 1){
      raiz = rotacaoDireitaEsquerdaAVL(raiz);
   }
   else if (FB == 2 && FBEsq == -1){
      raiz = rotacaoEsquerdaDireitaAVL(raiz);
   }
   return raiz;
}

// Funcao que insere um elemento na AVL
int insereAVL(AVLPlus *arv, char *palavra, char *descricao){
   if (isdigit(palavra[0])){
    return 0;
   }else{
   arv->raiz = insereNodoAVL(arv->raiz, palavra, descricao);
   return 1;
   }
}

// Funcao que retorna a altura de um nodo
int alturaNodoAVL(NoArvAVL *raiz){
   if(raiz->esq != NULL && raiz->dir != NULL){
      if(raiz->esq->alt < raiz->dir->alt)
         return raiz->dir->alt + 1;
      else
         return raiz->esq->alt + 1;
   }
   else if(raiz->esq != NULL)
      return raiz->esq->alt + 1;
   else if(raiz->dir != NULL)
      return raiz->dir->alt + 1;
   else
      return 1;
}

// Funcao que retorna o fator de balanceamento de um nodo
int fatorBalanceamentoNodoAVL(NoArvAVL *raiz){
   if(raiz == NULL)
      return 0;
   if(raiz->esq != NULL && raiz->dir != NULL)
      return raiz->esq->alt - raiz->dir->alt;
   else if(raiz->esq != NULL)
      return raiz->esq->alt;
   else if(raiz->dir != NULL)
      return -raiz->dir->alt;
}



// Rotacoes
// Rotacao simples a esquerda
NoArvAVL * rotacaoEsquerdaAVL(NoArvAVL *raiz){
   NoArvAVL *tmp1;
   NoArvAVL *tmp2;

   tmp1 = raiz;
   tmp2 = tmp1->dir;

   tmp1->dir = tmp2->esq;
   tmp2->esq = tmp1;

   tmp1->alt = alturaNodoAVL(tmp1);
   tmp2->alt = alturaNodoAVL(tmp2);

   return tmp2;
}

// Rotacao simples a direita
NoArvAVL * rotacaoDireitaAVL(NoArvAVL *raiz){
   NoArvAVL *tmp1;
   NoArvAVL *tmp2;

   tmp1 = raiz;
   tmp2 = tmp1->esq;

   tmp1->esq = tmp2->dir;
   tmp2->dir = tmp1;

   tmp1->alt = alturaNodoAVL(tmp1);
   tmp2->alt = alturaNodoAVL(tmp2);

  return tmp2;
}

// Rotacao esquerda-direita
NoArvAVL * rotacaoEsquerdaDireitaAVL(NoArvAVL *raiz){
   NoArvAVL *tmp1;
   NoArvAVL *tmp2;
   NoArvAVL *tmp3;

   tmp1 = raiz;
   tmp2 = tmp1->esq;
   tmp3 = tmp1->esq->dir;

   tmp1->esq = tmp3->dir;
   tmp2->dir = tmp3->esq;
   tmp3->dir = tmp1;
   tmp3->esq = tmp2;

   tmp1->alt = alturaNodoAVL(tmp1);
   tmp2->alt = alturaNodoAVL(tmp2);
   tmp3->alt = alturaNodoAVL(tmp3);

   return tmp3;
}

// Rotacao direita-esquerda
NoArvAVL * rotacaoDireitaEsquerdaAVL(NoArvAVL *raiz){
   NoArvAVL *tmp1;
   NoArvAVL *tmp2;
   NoArvAVL *tmp3;

   tmp1 = raiz;
   tmp2 = tmp1->dir;
   tmp3 = tmp1->dir->esq;

   tmp1->dir = tmp3->esq;
   tmp2->esq = tmp3->dir;
   tmp3->esq = tmp1;
   tmp3->dir = tmp2;

   tmp1->alt = alturaNodoAVL(tmp1);
   tmp2->alt = alturaNodoAVL(tmp2);
   tmp3->alt = alturaNodoAVL(tmp3);

   return tmp3;
}


// Funcao auxiliar para remover uma informacao da ABPPlus
NoArvAVL* removeInfoNodoAVL(NoArvAVL *raiz, char *palavra, int *remocao){
   if (raiz == NULL)
      return NULL;
   else if (strcmp(palavra,raiz->palavra)==-1){
      raiz->esq = removeInfoNodoAVL(raiz->esq, palavra,remocao);
        }
   else if (strcmp(palavra,raiz->palavra)==1){
      raiz->dir = removeInfoNodoAVL(raiz->dir, palavra,remocao);
        }
   else if (strcmp(palavra,raiz->palavra)==0){
      *remocao=1;
      if (raiz->esq == NULL && raiz->dir == NULL){
         free(raiz);
         raiz = NULL;
      }else if (raiz->esq == NULL){
         NoArvAVL *tmp = raiz;
         raiz = raiz->dir;
         free(tmp);

      }else if (raiz->dir == NULL){
         NoArvAVL *tmp = raiz;
         raiz = raiz->esq;
         free(tmp);
      }else{
         NoArvAVL *tmp = raiz->esq;
         while(tmp->dir != NULL){

            tmp = tmp->dir;
         }
         strcpy(raiz->palavra,tmp->palavra);
         strcpy(tmp->palavra,palavra);
         raiz->esq = removeInfoNodoAVL(raiz->esq, palavra,remocao);
      }
   }
    if (raiz!=NULL){
      raiz->alt = alturaNodoAVL(raiz); //Ajuste do campo altura//

    int FB = fatorBalanceamentoNodoAVL(raiz);
    int FBEsq = fatorBalanceamentoNodoAVL(raiz->esq);
    int FBDir = fatorBalanceamentoNodoAVL(raiz->dir);
    //É aqui que eu devo inserir os casos de rotações buscando o balanceamento após a remoção//
    if (FB == 2 && FBEsq == 1){
      raiz = rotacaoDireitaAVL(raiz);
   }
   else if (FB == -2 && FBDir == -1){
      raiz = rotacaoEsquerdaAVL(raiz);
   }
   else if (FB == -2 && FBDir == 1){
      raiz = rotacaoDireitaEsquerdaAVL(raiz);
   }

   else if (FB == 2 && FBEsq == -1){
      raiz = rotacaoEsquerdaDireitaAVL(raiz);
   }

   //Inserir os casos "aplicar uma rotac¸ao˜ a direita quando o FB do nodo desbalanceado ` ´e positivo e o FB da raiz de sua SAE ´e 0;"
   else if (FB == 2 && FBEsq == 0){
      raiz = rotacaoDireitaAVL(raiz);
   }

   else if (FB == -2 && FBDir == 0){
      raiz = rotacaoEsquerdaAVL(raiz);
   }
    }
   return raiz;
}

// Funcao que remove uma informacao da ABPPlus
int removeInfoAVL(AVLPlus *arv, char *palavra){
    int *remocao;
    int remove=0;
    remocao=&remove;
    palavra=conversaoParaMaiuscula(palavra);
    arv->raiz = removeInfoNodoAVL(arv->raiz, palavra, remocao);
    if (remove==0){
        return 0;
    }
    else{
        return 1;
    }
}

//Funcao que permite editar uma palvra existente no dicionario.
int editarPalavra(AVLPlus *arvore, char *palavra, char *nova_palavra){
    NoArvAVL *varAux, *varAux_1;
    varAux = buscaPalavrasIguais(arvore, palavra); //Verificando se a palavra foi cadastrada no dicionario.//
    varAux_1 = buscaPalavrasIguais(arvore, nova_palavra); //Verificando se a palavra que se deseja inserir no local da anterior ja nao foi cadastrada.

    if (!isdigit(palavra[0])){ //Se o primeiro caracter da nova palavra nao for numerico, entao o programa executa as instrucoes da prohxima linha.
        if (varAux == NULL || varAux_1!=NULL) {//Se varAux == NULL, entao a palavra a ser editada nao foi encontrada. Se varAux_1!=NULL, entao a nova_palavra jah foi cadastrada.
            return 0;
        }else {
            insereAVL(arvore, nova_palavra,varAux->descricao);
            removeInfoAVL(arvore, palavra);
            return 1;
        }
    }else{
        return 0;
    }
}

//Funcao que converte palavras de minusculo para maiusculo.
char *conversaoParaMaiuscula (char *palavra) {
    char *aux=palavra;
    int i=0;
    while (palavra[i]!='\0'){
        aux[i] = toupper((unsigned char) palavra[i]);
        i+=1;
    }
    palavra=aux;
    return palavra;
}

//Funcao que faz a leitura do arquivo de texto que contem as definicoes previamente carregadas.
void leDicionario(AVLPlus *arvore){
    FILE* fp = fopen("retorno.txt","rt");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    int n = 0;
    char linha[MAX_DEFINICAO];
    while (fgets(linha ,MAX_DEFINICAO, fp) != NULL) {
        n++;
        char *token = strtok(linha, "@");//Selecionando a palavra.
        char palavra[MAX_PALAVRA], definicao[MAX_DEFINICAO];
        strcpy(palavra,token);
        token = strtok(NULL, "@");//Selecionando a definicao da palavra.
        strcpy(definicao,token);
        definicao[strlen(token)]='\0';
        NoArvAVL *varAux;
        varAux = buscaPalavrasIguais(arvore,palavra);
        //printf("varAux->palavra=%s",varAux->palavra);
        if (varAux == NULL){
            insereAVL(arvore, palavra,definicao);
            arvore->nPalavras+=1;
        }else{
            printf("NAO FOI POSSIVEL INSERIR A PALAVRA NO DICIONARIO.\n");
        }
        if (arvore->nPalavras%25000==0){//O efeito grafico da barra de carregamento eh gerado apos a importacao de 25.000 palavras.
            efeitoCarregaArquivo();
        }
    }
}

//Funcao que permite a edicao da definicao de uma palavra cadastrada.
int editaDefinicao(AVLPlus *arvore, char *palavra, char *descricao){
    NoArvAVL *varAux = buscaPalavrasIguais(arvore,palavra);
    if (varAux == NULL){
        return 0;
        }
    else{
        strcpy(varAux->descricao,descricao);
        return 1;
        }
}

void efeitoCarregaArquivo(){
    for (int i=0; i<18; i++){
    Sleep(20);
    printf("%c",219);
    }
}

//Funcao auxiliar para imprimir uma ABP em ordem decrescente###
void salvaAVLAux(NoArvAVL *raiz, char letra, FILE* fp){
    if (raiz!=NULL){    //Se o nodo passado nao for nulo, a prohxima linha eh executada. Do contrario, nada eh feito.
        if(raiz->esq == NULL && raiz->dir == NULL){
            if (raiz->palavra[0]==letra){
            printf("%s\n",raiz->palavra);
            fprintf(fp,"%s\n",raiz->palavra);   //Essa instrucao faz com que a string raiz->palavra seja registrada no espaco da memohria do ponteiro fp.
            }
        }
        else if (raiz->esq != NULL && raiz->dir==NULL){
            if (raiz->palavra[0]==letra){
            printf("%s\n",raiz->palavra);
            fprintf(fp,"%s\n",raiz->palavra);
            }
            salvaAVLAux(raiz->esq, letra, fp);

        }
        else if (raiz->esq == NULL && raiz->dir!=NULL){
            if (raiz->palavra[0]==letra){
            printf("%s\n",raiz->palavra);
            fprintf(fp,"%s\n",raiz->palavra);
            }
        }
        else if (raiz->esq != NULL && raiz->dir!=NULL){
            salvaAVLAux(raiz->esq,letra,fp);
            if (raiz->palavra[0]==letra){
            printf("%s\n",raiz->palavra);
            fprintf(fp,"%s\n",raiz->palavra);
            }
            salvaAVLAux(raiz->dir, letra, fp);
        }
    }
}
//Funcao principal para imprimir no terminal a lista de palavras iniciadas por "letra" e para salvar arquivo de texto em disco.
int salvaAVL(AVLPlus *arv, char letra){
    if (arv->raiz!=NULL){ //Verifica se algum elemento da jah foi cadastrado na arvore.
        if (!isdigit(letra)){ //Se o caracter inserido nao for numerico, entao o programa executa as instrucoes da prohxima linha.
            char titulo[50] = "lista_palavras_inciadas_por_";
            strncat(titulo,&letra,1);
            strcat(titulo,".txt");
            FILE* fp = fopen(titulo,"w"); //Criando ponteiro do tipo FILE para a permitir a gravacao de arquivo de texto.
            if (fp == NULL) {
                return 0;
            }else {
                letra = putchar(toupper(letra));    //Transforma o caractere de minusculo para maisculo.
                clear_screen();
                printf("--------------------------------------\n");
                printf("AS PALAVRAS INICIADAS POR %c SAO:\n",letra);
                printf("--------------------------------------\n");
                salvaAVLAux(arv->raiz, letra,fp);
                fclose(fp);
                return 1;
                }
            }
        else {
            return 0;
        }
    }else {
        return 0;
    }
}




//Funcao auxiliar para imprimir uma ABP em ordem decrescente###
void salvaAVL_definicoesAux(NoArvAVL *raiz, char letra, FILE* fp){
    if (raiz!=NULL){    //Se o nodo passado nao for nulo, a prohxima linha eh executada. Do contrario, nada eh feito.
        if(raiz->esq == NULL && raiz->dir == NULL){
            if (raiz->palavra[0]==letra){
            fprintf(fp,"PALAVRA:  %s\n",raiz->palavra);
            splitString(raiz,letra,fp);
            }
        }
        else if (raiz->esq != NULL && raiz->dir==NULL){
            if (raiz->palavra[0]==letra){
            fprintf(fp,"PALAVRA:  %s\n",raiz->palavra);
            splitString(raiz,letra,fp);
            }
            salvaAVL_definicoesAux(raiz->esq, letra, fp);

        }
        else if (raiz->esq == NULL && raiz->dir!=NULL){
            if (raiz->palavra[0]==letra){
            fprintf(fp,"PALAVRA:  %s\n",raiz->palavra);
            splitString(raiz,letra,fp);
            }
        }
        else if (raiz->esq != NULL && raiz->dir!=NULL){
            salvaAVL_definicoesAux(raiz->esq,letra,fp);
            if (raiz->palavra[0]==letra){
            fprintf(fp,"PALAVRA:  %s\n",raiz->palavra);
            splitString(raiz,letra,fp);
            }
            salvaAVL_definicoesAux(raiz->dir, letra, fp);
        }
    }
}


int salvaAVL_definicoes(AVLPlus *arv, char letra){
    if (arv->raiz!=NULL){ //Verifica se algum elemento da jah foi cadastrado na arvore.
        if (!isdigit(letra)){ //Se o caracter inserido nao for numerico, entao o programa executa as instrucoes da prohxima linha.
            char titulo[50] = "lista_definicao_palavras_inciadas_por_";
            strncat(titulo,&letra,1);
            strcat(titulo,".txt");
            FILE* fp = fopen(titulo,"w"); //Criando ponteiro do tipo FILE para a permitir a gravacao de arquivo de texto.
            if (fp == NULL) {
                return 0;
            }else {
                letra = putchar(toupper(letra));    //Transforma o caractere de minusculo para maisculo.
                clear_screen();
                salvaAVL_definicoesAux(arv->raiz, letra,fp);
                fclose(fp);
                return 1;
                }
            }
        else {
            return 0;
        }
    }else {
        return 0;
    }
}

//Funcao que segmenta as definicoes em strings de tamanho 100 ou menos, buscando uma boa visualizacao no arquivo de saida txt.
void splitString(NoArvAVL *raiz, char letra, FILE* fp){
    char aux[105];
    int i,j=0;
    for (i=0; i<strlen(raiz->descricao);i++){ //Aqui, eh realizado um ciclo for por todos os caracteres da descricao.
        if (i==0 && strlen(raiz->descricao)-100>=0){ //Se i==0 && strlen(raiz->descricao)-100>=0, entao descricao tem mais de 100 caracteres.
            strncpy(aux, &raiz->descricao[0],100);
            aux[100] = '\0';
            fprintf(fp,"DEFINICAO:\n%s\n",aux);
            }
        else if(i==0 && strlen(raiz->descricao)-100<0){//Se i==0 && strlen(raiz->descricao)-100<0 entao a descricao tem menos de 100 caracteres.
            strncpy(aux, &raiz->descricao[0],strlen(raiz->descricao));
            aux[strlen(raiz->descricao)]='\0';
            fprintf(fp,"DEFINICAO:\n%s",aux);
            }
        else if(i!=0 && i%100 == 0 && strlen(raiz->descricao)-i>100 ){//Se i!=0 && i%100 == 0 && strlen(raiz->descricao)-i>100, entao no ciclo i, restam mais de 100 caracteres na descricao.
            strncpy(aux, &raiz->descricao[i], 100);
            aux[100]='\0';
            fprintf(fp,"%s\n",aux);
            }
        if (i!=0 && i%100==0){//Sempre que o i for multiplo de 100, 'j' iguala 'i'. Isso eh util para a ultima rodada de descricoes em que strlen(aux)>=100.
            j=i;
            }
        }
        if (strlen(aux)>=100 && i-j>0){
            strncpy(aux, &raiz->descricao[j], i-j);
            aux[i-j]='\0';
            fprintf(fp,"%s\n",aux);
        }
}

// Funcao auxiliar para destroir uma AVL
void destroiNodoAVL(NoArvAVL *raiz){
   if(raiz != NULL){
      destroiNodoAVL(raiz->esq);
      destroiNodoAVL(raiz->dir);
      free(raiz);
   }
}

// Funcao que destroi uma AVL
void destroiAVL(AVLPlus *arv){
   destroiNodoAVL(arv->raiz);
   free(arv);
}
