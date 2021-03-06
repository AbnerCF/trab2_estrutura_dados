/*
 * Árvores binárias de busca.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "avl.h"

#define MAX 15000

int retorneBalanceamento(No *n) {
    return n == NULL ? 0 : n->fatorBalanceamento;
}
int maior(int a, int b) {
    return (a > b)? a : b;
}

void cria_arvore(Arvore *p) {
    *p = NULL;
}

struct No* novoNo(elem_t valor) {
    struct No* noh = (struct No*) malloc(sizeof(struct No));
    noh->info = valor;
    noh->esq = NULL;
    noh->dir = NULL;
    noh->fatorBalanceamento = 1; //noh folha, fator balanceamento = 0
    return noh;
}

void inorder(Arvore p) {
    if (p != NULL) {
        inorder(p->esq);
        printf("%d ", p->info);
        inorder(p->dir);
    }
}

/* Retorna 1 se a chave for encontrada */
int busca (Arvore p, int chave) {
    if (p == NULL)
        return 0;

    if (p->info > chave)
        return busca(p->esq, chave);
    else if (p->info < chave)
        return busca(p->dir, chave);

    return 1; // achou
}


/* Retorna 0 se a chave for repetida */
No* _insere(No *p, int chave);
int insere(Arvore *p, int chave) {
	if(*p == NULL) {
		//printf("arvore vazia, iniciando arvore...\n");
		No* noh = novoNo(chave);
		*p = noh;
	} else {
		//printf("adicionando novo noh\n");
		No* result = _insere(*p, chave);
		if(result == NULL) {
			return 0; 
		} else {
			*p = result;
		}
	}
	return 1;
}

No* _insere(No *p, int chave) {

	//funcao auxiliar
	struct No *rotacaoEsquerda(struct No *pB) {
		struct No *pA = pB->dir;
		struct No *aux = pA->esq;
	 
		//Rotacionando
		pA->esq = pB;
		pB->dir = aux;
	 
		//Atualizando fatores de balanceamento
		pB->fatorBalanceamento = maior(retorneBalanceamento(pB->esq), retorneBalanceamento(pB->dir))+1;
		pA->fatorBalanceamento = maior(retorneBalanceamento(pA->esq), retorneBalanceamento(pA->dir))+1;
	 
		return pA;
	}
	//funcoes auxiliar
	No *rotacaoDireita(struct No *pA) {
		struct No *pB = pA->esq;
		struct No *aux = pB->dir;

		//Rotacionando
		pB->dir = pA;
		pA->esq = aux;

		//Atualizando fatores de balanceamento
		pA->fatorBalanceamento = maior(retorneBalanceamento(pA->esq), retorneBalanceamento(pA->dir))+1;
		pB->fatorBalanceamento = maior(retorneBalanceamento(pB->esq), retorneBalanceamento(pB->dir))+1;

		return pB;
	}

    if (p == NULL)
		return novoNo(chave);
 
    if (chave < p->info) {
		p->esq  = _insere(p->esq, chave);
    } else if (chave > p->info) {
		p->dir = _insere(p->dir, chave);
    } else { //chave ja existe
		return NULL;
	}
    //atualiza balanceamento do pai do no inserido
	p->fatorBalanceamento = 1 + maior(retorneBalanceamento(p->esq), retorneBalanceamento(p->dir));
 
	//verifica balanceamento
    int balanceamento = (p == NULL ? 0 : (retorneBalanceamento(p->esq) - retorneBalanceamento(p->dir)));
	if (balanceamento > 1 && chave < p->esq->info) { // Left Left Case
        return rotacaoDireita(p);
	} else if (balanceamento < -1 && chave > p->dir->info) { // Right Right Case
        return rotacaoEsquerda(p);
	} else if (balanceamento > 1 && chave > p->esq->info) { // Left Right Case
        p->esq =  rotacaoEsquerda(p->esq);
        return rotacaoDireita(p);
    } else if (balanceamento < -1 && chave < p->dir->info) { // Right Left Case
        p->dir = rotacaoDireita(p->dir);
        return rotacaoEsquerda(p);
    } else {
		//não precisa balancear
	}
 
	/*
		obs.: implementação atual usa noh folha como 1 ao invés de 0
		para mudar isso precisaria testar mudando as seguintes linhas:
		
		24:  return n == NULL ? -1 : n->fatorBalanceamento;
		39:  noh->fatorBalanceamento = 0;
		113: int balanceamento = p->fatorBalanceamento;
	*/
    return p;
}


/* Retorna 0 se a chave não for encontrada */
int remove_arv(Arvore *p, int chave) {

}

/* Verifica se p é uma árvore de busca */
int _verifica(Arvore p, int min, int max);
int verifica(Arvore p) {
	return _verifica(p, INT_MIN, INT_MAX);
}
 
int _verifica(Arvore p, int min, int max) { 
	if (p == NULL) 
		return 1;
	if (p->info < min || p->info > max) 
		return 0; 

	return _verifica(p->esq, min, p->info-1) && _verifica(p->dir, p->info+1, max);
} 

int busca_por_intervalo(Arvore p, int min, int max) {
	if (p != NULL) {
		busca_por_intervalo(p->esq, min, max);
		if(p->info >= min && p->info <= max) {
			printf("%d ", p->info);
			//return p->info; //encontrar uma forma de retornar para o main ao invez de apenas printar os valores (armazenar em uma pilha ou fila)
		}
		busca_por_intervalo(p->dir, min, max);
	}
	return 0;
}
