#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN_NAME 15
#define MAX_LEN 1000

int compara_strings(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

void remove_newline(char* str) {
    size_t len = strcspn(str, "\n");
    if (str[len] == '\n') {
        str[len] = '\0';
    }
}


typedef struct _no {
    struct _no *esq;
    struct _no *dir;
    struct _no *pai;
    int balanceamento;
    char* palavra;
    char* significado;

} No;

No* aloca_no(char* nome, char*significado) {
    No* novo = (No*)malloc(sizeof(No));
    novo->palavra = nome;
    novo->significado = significado;
    novo->balanceamento = 0;
    return novo;
}

No* aloca_avl() {
    No* novo = (No*)malloc(sizeof(No));
    novo->pai = novo;
    novo->balanceamento = 0;
    novo->palavra = NULL;
    novo->significado = NULL;
    return novo;
}

int altura(No* p) {
    if (p == NULL) {
        return -1;
    }
    int altura_esq = altura(p->esq);
    int altura_dir = altura(p->dir);
    return 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
}

int fb(No* p) {
    if (p == NULL) {
        return 0;
    }
    return altura(p->esq) - altura(p->dir);
}

No* rotacionarLL(No* p) {
    printf("Rotacionou LL\n");
    No* pesq = p->esq;
    No* pesqdir = pesq->dir;

    pesq->dir = p;

    if (p->pai == p) pesq->pai = pesq;
    else pesq->pai = p->pai;

    p->pai = pesq;
    p->esq = pesqdir;

    if (pesqdir != NULL) pesqdir->pai = p;

    p->balanceamento = fb(p);
    pesq->balanceamento = fb(pesq);

    return pesq;
}

No* rotacionarRR(No* p) {
    printf("Rotacionou RR");
    No* pdir = p->dir;
    No* pdiresq = pdir->esq;

    pdir->esq = p;

    if (p->pai == p) pdir->pai = pdir;
    else pdir->pai = p->pai;

    p->pai = pdir;
    p->dir = pdiresq;

    if (pdiresq != NULL) pdiresq->pai = p;

    p->balanceamento = fb(p);
    pdir->balanceamento = fb(pdir);

    return pdir;
}

No* rotacionarRL(No* p) {
    printf("Rotacionou RL\n");
    p->dir = rotacionarLL(p->dir);
    return rotacionarRR(p);
}

No* rotacionarLR(No* p) {
    printf("Rotacionou LR\n");
    p->esq = rotacionarRR(p->esq);
    return rotacionarLL(p);
}

No* busca_no(No* avl, char* nome, int printar) {
    No* aux = avl;
    while (aux != NULL) {
        if (compara_strings(aux->palavra, nome) == 0) {
            if (printar == 1) printf("\nBusca com sucesso.\n");
            return aux;
        }
        else if (compara_strings(aux->palavra, nome) > 0) aux = aux->esq;
        else if (compara_strings(aux->palavra, nome) < 0) aux = aux->dir;
    }
    if (printar == 1) printf("\nBusca sem sucesso.\n");
    return aux;
}


No* insere_palavra(No* p, char* nome, char* significado) {
    No* novo = NULL;

    if (p == NULL) {
        novo = aloca_no(nome, significado);
        novo->esq = novo->dir = NULL;
        novo->pai = p;
        return novo;
    }
    if (compara_strings(nome, p->palavra) < 0) {
        p->esq = insere_palavra(p->esq, nome, significado);
        p->esq->pai = p;
    }
    else if (compara_strings(nome, p->palavra) > 0) {
        p->dir = insere_palavra(p->dir, nome, significado);
        p->dir->pai = p;
    }
    p->balanceamento = fb(p);

    if (p->balanceamento == 2) {
        if (p->esq->balanceamento >= 0)
            return rotacionarLL(p);
        else
            return rotacionarLR(p);
    }
    else if (p->balanceamento == -2) {
        if (p->dir->balanceamento <= 0)
            return rotacionarRR(p);
        else
            return rotacionarRL(p);
    }

    printf("\nInserção de %s com sucesso!\n", nome);
    return p;
}

No* le_palavras(No* avl) {
    char* palavra = (char*)malloc(sizeof(char) * MAX_LEN_NAME);
    char* significado = (char*)malloc(sizeof(char) * MAX_LEN);

    printf("Digite a palavra: ");
    fgets(palavra, MAX_LEN_NAME, stdin);
    remove_newline(palavra);

    printf("Digite o significado: ");
    fgets(significado, MAX_LEN, stdin);
    remove_newline(significado);

    if (avl->palavra == NULL && avl->significado == NULL){
        avl->palavra = palavra;
        avl->significado = significado;
        printf("\nInserção de %s com sucesso!\n", palavra);
        return avl;
    }
    else {
        if( busca_no(avl, palavra, 0) == NULL) avl = insere_palavra(avl, palavra, significado);
        else {
            printf("Palavra %s já existe no dicionário! Operação de inserção sem sucesso\n", palavra);
        }
    }

    return avl;
}



/*
 * Comandos notáveis:
 * 1. Criar uma árvore vazia
 * 2. Remover uma palavra
 * 3. Inserir uma palavra
 * 4. Buscar palavra
 * 5. Imprimir a árvore (em ordem)
*/


int main(void)
{
    No* avl = aloca_avl();
    for (int i = 0; i < 4; i++) avl = le_palavras(avl);
    No* busca = busca_no(avl, "Ameba", 1);
    if (busca != NULL ) printf("\n%s    h=%d",busca->palavra, altura(busca));

    return 0;
}
