#include <stdio.h>
#include <stdlib.h>
#include "estruturas_dicionario.h"
#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(__unix__)
#define clear_screen() system("clear")
#endif
/*
OBJETIVO DO ALGORITMO: CRIAR UM DICIONARIO INTERATIVO.
VERSÃO FINAL
*/

//Funcao que imprime um string de tracejados//
void imprimeTracejado();

int main()
{
    AVLPlus *arvore;
    arvore = criaAVL();         //Aloca dinamicamente o espaco de memoria necessario para criar uma AVL.
    int escolha,retorno;
    char palavra[MAX_PALAVRA], definicao[MAX_DEFINICAO], aux[MAX_PALAVRA];
    NoArvAVL *varAux;
    char letra;

    //## EFETUANDO CARREGAMENTO DE ARQUIVOS EXTERNOS ##//
    printf("CARREGANDO ARQUIVO...\n");
    leDicionario(arvore);               //Funcao que faz a importacao das palavras do dicionario.
    printf("\nCARREGAMENTO COMPLETO.\nFORAM CADASTRADAS %d PALAVRAS.\n\n",arvore->nPalavras);

    //### MENU PRINCIPAL ###//
    do{
    printf("================\n MENU PRINCIPAL \n================\n");
    printf("1.Inserir nova palavra/definicao.\n");
    printf("2.Remover uma palavra.\n");
    printf("3.Pesquisa palavra.\n");
    printf("4.Editar palavra.\n");
    printf("5.Editar a definicao de uma palavra.\n");
    printf("6.Verificar quantidade de palavras cadastradas.\n");
    printf("7.Imprimir lista de palavras no terminal e salva-lah em arquivo de texto.\n");
    printf("8.Salvar em arquivo de texto lista de palavras iniciadas por determinada letra e a sua definicao.\n");
    printf("9.Sair.\n");

    scanf("%d", &escolha);
    fflush(stdin);
    switch(escolha){
        case 1:{
            clear_screen();
            printf("DIGITE A PALAVRA QUE VOCE DESEJA INSERIR NO DICIONARIO:\n");
            scanf(" %100[^\n]", palavra);
            fflush(stdin);
            printf("DIGITE A DEFINICAO DA PALAVRA QUE INSERIU NO DICIONARIO:\n");
            fgets(definicao, MAX_DEFINICAO,stdin);
            fflush(stdin);
            varAux = buscaPalavrasIguais(arvore,palavra);       //Verifica a existencia de palavras semelhantes. Se retornar nulo, entao palavra semelhante nao foi encontrada.
            if (varAux == NULL){                                //Se nao tiverem sido cadastradas palavras semelhantes, entao eh possivel cadastrar palavra nova.
                retorno = insereAVL(arvore,palavra,definicao);  //Se retorno==1, entao foi possivel cadastrar palavra nova. Do contrario, nao foi possivel.
                if (retorno==1){
                arvore->nPalavras+=1;                           //Atualiza o numero de palavras cadastradas no dicionario.
                clear_screen();                                 // Limpa o terminal.
                printf("A PALAVRA %s E A SUA DEFINICAO FORAM INSERIDAS NO DICIONARIO.\n", palavra);
                break;
                }else {
                    clear_screen();
                    printf("NAO FOI POSSIVEL INSERIR A PALAVRA NO DICIONARIO.\n");
                    break;
                }

            }else{
                printf("NAO FOI POSSIVEL INSERIR A PALAVRA NO DICIONARIO.\n");
                break;
                }
            }
        case 2:{
            printf("DIGITE A PALAVRA QUE VOCE DESEJA REMOVER: \n");
            scanf(" %100[^\n]", palavra);
            fflush(stdin);
            retorno = removeInfoAVL(arvore, palavra);       //Se retorno == 0, nao foi possivel a remocao. Do contrario, foi possivel.
            if (retorno == 1){
                clear_screen();
                arvore->nPalavras-=1;                       //Atualiza o numero de palavras carregadas no dicionario.
                printf("A REMOCAO FOI REALIZADA CORRETAMENTE.\n");
                break;
                }
            else{
                clear_screen();
                printf("A REMOCAO NAO FOI REALIZADA CORRETAMENTE.\n");
                break;
                }
            }
        case 3:{
            clear_screen();
            printf("DIGITE A PALAVRA QUE VOCE DESEJA PESQUISAR: \n");
            scanf(" %100[^\n]", palavra);
            fflush(stdin);
            varAux = buscaPalavrasIguais(arvore, palavra);      //Verifica se a palavra buscada foi cadastrada. Se varAux==NULL, nao foi. Se Se varAux!=NULL, entao foi.
            clear_screen();
            if (varAux != NULL){
                imprimeTracejado();
                printf("PALAVRA: %s\n",varAux->palavra);
                printf("DEFINICAO: %s\n",varAux->descricao);
                break;
                }
            else if (varAux==NULL) {
                printf("A PALAVRA NAO FOI ENCONTRADA.\n");
                break;
                }
            }
        case 4:{
            clear_screen();
            printf("DIGITE A PALAVRA QUE VOCE DESEJA EDITAR: \n");
            scanf(" %100[^\n]", palavra);
            fflush(stdin);
            printf("DIGITE O NOVO TEXTO: \n");
            scanf(" %100[^\n]", aux);
            fflush(stdin);
            retorno = editarPalavra(arvore, palavra, aux);   //Se retorno ==0, entao nao eh possihvel editar a palavra. Do contrario, eh possihvel.
            if (retorno == 1){
                clear_screen();
                printf("A EDICAO DA PALAVRA FOI REALIZADA CORRETAMENTE.\n\n");
                break;
                }
                else {
                clear_screen();
                printf("A EDICAO DA PALAVRA NAO PODE SER REALIZADA.\n\n");
                break;
                }
            }
        case 5:{
                clear_screen();
                printf("DIGITE A PALAVRA CUJA DEFINICAO VOCE DESEJA EDITAR:\n");
                scanf(" %20[^\n]", palavra);
                fflush(stdin);
                printf("DIGITE A DEFINICAO DA PALAVRA:\n");
                fgets(definicao, MAX_DEFINICAO,stdin);
                retorno = editaDefinicao(arvore,palavra,definicao); //Se retorno==0, entao nao eh possihvel editar a definicao. Do contrario, eh possivel.
                clear_screen();
                if (retorno == 0){
                    printf("A NOVA DEFINICAO DA PALAVRA %s NAO PODE SER INSERIDA.\n", palavra);
                    break;
                }else {
                    printf("A NOVA DEFINICAO DA PALAVRA %s FOI INSERIDA.\n", palavra);
                    break;
                }
        }
        case 6:{
            clear_screen();
            printf("FORAM CADASTRADAS %d PALAVRAS ATEH O MOMENTO.\n\n\n",arvore->nPalavras);
            break;
            }
        case 7: {
            clear_screen();
            printf("DIGITE A PRIMEIRA LETRA DAS PALAVRAS CUJA LISTA SERAH SALVA EM ARQUIVO DE TEXTO:\n");
            scanf("%c",&letra);
            fflush(stdin);
            clear_screen();
            retorno = salvaAVL(arvore,letra);    //Se retorno == 1, entao foi possihvel a impressao em tela e a geracao de arquivo de texto. Do contrahrio, nao foi possivel.
            if (retorno==1){
                printf("FOI SALVO EM DISCO UM ARQUIVO DE TEXTO COM A LISTA DE PALAVRAS INICIADAS POR %c.\n", letra);
                break;
            }else {
                printf("NAO FOI POSSIVEL SALVAR EM DISCO UM ARQUIVO DE TEXTO COM A LISTA DE PALAVRAS INICIADAS POR %c.\n",letra);
                break;
                    }
                }
        case 8: {
                clear_screen();
                printf("DIGITE A PRIMEIRA LETRA DAS PALAVRAS CUJA LISTA SERAH SALVA EM ARQUIVO DE TEXTO:\n");
                scanf("%c",&letra);
                fflush(stdin);
                clear_screen();
                retorno = salvaAVL_definicoes(arvore,letra); //Se retorno == 1, foi possivel a geracao de arquivo de texto. Do contrahrio, nao.
                if (retorno==1){
                    printf("FOI SALVO EM DISCO UM ARQUIVO DE TEXTO COM A LISTA DE PALAVRAS INICIADAS POR %c E SUAS DEFINICOES.\n", letra);
                    break;
                }else {
                    printf("NAO FOI POSSIVEL SALVAR EM DISCO UM ARQUIVO DE TEXTO COM A LISTA DE PALAVRAS INICIADAS POR %c. E SUAS DEFINICOES",letra);
                    break;
                    }
                }
        case 9:{
                printf("SAINDO DA APLICACAO.\n");
                break;
        }
        default:{
            clear_screen();
            printf ("OPCAO INVALIDA.\n\n\n");
            }
        }
    }
    while (escolha!=9);
    destroiAVL(arvore); //Chama a funcao que destroi a AVL.
    return 0;
}


void imprimeTracejado(){
    printf("-----------------------\n");
}




