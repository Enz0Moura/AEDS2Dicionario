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

No* aloca_avl(char* nome, char*significado) {
    No* novo = (No*)malloc(sizeof(No));
    novo->pai = novo;
    novo->palavra = nome;
    novo->significado = significado;
    novo->balanceamento = 0;
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
    printf("Rotacionou LL");
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

void percursoEmOrdem(No * no)
{
    if(no == NULL)
    {
        return;
    }
    percursoEmOrdem(no->esq);
    printf("%s", no->palavra);
    percursoEmOrdem(no->dir);
}

void balancear(No* p) {
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

    balancear(p);

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

    if (avl == NULL){
        avl = aloca_avl(palavra, significado);
    }
    else avl = insere_palavra(avl, palavra, significado);

    return avl;
}

No* busca_no(No* avl, char* nome) {
    No* aux = avl;
    while (aux != NULL) {
        if (compara_strings(aux->palavra, nome) == 0) return aux;
        else if (compara_strings(aux->palavra, nome) > 0) aux = aux->esq;
        else if (compara_strings(aux->palavra, nome) < 0) aux = aux->dir;
    }
    return aux;
}

No * sucessor(No* avl) {
    No* aux = avl->dir;
    while (aux->esq != NULL) {
        aux = aux->esq;
    }
    return aux;
}

void remove_palavra(No * avl, char * nome){

    No* aux = busca_no(avl, nome);
    if(aux == NULL){
      printf("Operação de remocão da palavra %s inválida\n", nome);
      return;
    }
    else if (compara_strings(aux->palavra, nome) == 0){

        if(aux->esq == NULL && aux->dir == NULL){
            if(aux == aux-> pai->esq){
                aux->pai->esq = NULL;
            }
            else{
                aux->pai->dir = NULL;
            }
        }

        else if(aux->esq != NULL && aux->pai->esq == aux){
            aux->pai->esq = aux->esq;
            aux->esq->pai = aux->pai;
        }

        else if(aux->dir != NULL && aux->pai->esq == aux){
            aux->pai->esq = aux->dir;
            aux->dir->pai = aux->pai;
        }

        else if(aux->esq != NULL && aux->pai->dir == aux){
            aux->pai->dir = aux->esq;
            aux->esq->pai = aux->pai;
        }

        else if(aux->dir != NULL && aux->pai->dir == aux){
            aux->pai->dir = aux->dir;
            aux->dir->pai = aux->pai;
        }

        else{
            No * suc = sucessor(aux);
            aux->palavra = suc->palavra;
            aux->significado = suc->significado;
            remove_palavra(avl, suc->palavra);
        }
    }

    else if (compara_strings(aux->palavra, nome) > 0) aux = aux->esq;
    else if (compara_strings(aux->palavra, nome) < 0) aux = aux->dir;


    while(aux != NULL){
        aux = aux->pai;
        aux->balanceamento = fb(aux);
        if(aux->balanceamento > 1 || aux->balanceamento < -1){
            balancear(aux);
        }
        else{
            return;
        }
    }

    printf("%s removido com  sucesso\n" nome);
}

/*
 * Comandos notáveis:
 * 1 - inicializa árvores
 * 2 - remove nós
 * 3 - insere nó
 * 4 - busca nó, retorna altura e definição.
 * 5 - busca nó e retorna altura
 * 6 - mostra todos os nós e suas alturas
 */


int main(void)
{
    No* avl = NULL;
    for (int i = 0; i < 3; i++) avl = le_palavras(avl);
    No* busca = busca_no(avl, "Ameba");
    if (busca != NULL ) printf("\n%s    h=%d",busca->palavra, altura(busca));

    return 0;
}
