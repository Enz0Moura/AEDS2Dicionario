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

typedef struct _no {
    struct _no *esq;
    struct _no *dir;
    struct _no *pai;
    int balanceamento;
    char* palavra;
    char* significado;

} No;

No* aloca_arvore() {
    No* avl = (No*)malloc(sizeof(No));
    avl->balanceamento = 0;
    avl->pai = NULL;
    avl->esq = NULL;
    avl->dir = NULL;
}

No* aloca_no(char* nome, char*significado) {
    No* novo = (No*)malloc(sizeof(No));
    novo->palavra = nome;
    novo->significado = significado;
    return novo;
}

No* insere_palavra(No* p, char* nome, char* significado) {
    No* novo = NULL;

    if (p == NULL) {
        novo = aloca_no(nome, significado);
        novo->esq = novo->dir = NULL;
        novo->pai = p;
        return novo;
    }
    if (!compara_strings(nome, p->palavra)) {
        p->esq = insere_palavra(p->esq, nome, significado);
    }
    else if (compara_strings(nome, p->palavra)) {
        p->dir = insere_palavra(p->dir, nome, significado);
    }
    return p;
}

No* cria_avl(char* nome, char* significado) {
    No* avl = aloca_arvore();
    avl->palavra = nome;
    avl->significado = significado;
    return avl;
}

No* le_palavras() {
    char* palavra = (char*)malloc(sizeof(char) * MAX_LEN_NAME);
    char* significado = (char*)malloc(sizeof(char) * MAX_LEN);

    printf("Digite a palavra: ");
    fgets(palavra, MAX_LEN_NAME, stdin);

    printf("Digite o significado: ");
    fgets(significado, MAX_LEN, stdin);

    No* novo = cria_avl(palavra, significado);

    return novo;
}

int main(void)
{
    No* avl = le_palavras();
    printf("%s",avl->palavra);
    return 0;
}
