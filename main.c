#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN_NAME 15
#define MAX_LEN 1000

typedef struct __no
{
    char *palavra;
    char *significado;
    struct __no *esq;
    struct __no *dir;
    struct __no *pai;
    int fator_balanceamento;
} No;

typedef struct __arv
{
    No *raiz;
} Arv;

No *alocaNo()
{
    No *novo = (No *) malloc(sizeof(No));
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->fator_balanceamento = 0;
    return novo;
}

Arv *criaArv()
{
    Arv *nova = (Arv *) malloc(sizeof(Arv));
    nova->raiz = NULL;
    return nova;
}

int compara_strings(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) return -1;

    while (*str1 && *str2)
    {
        if (*str1 != *str2)
        {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

void remove_newline(char *str)
{
    size_t len = strcspn(str, "\n");
    if (str[len] == '\n')
    {
        str[len] = '\0';
    }
}

int alturaNo(No *no)
{
    if (no == NULL)
    {
        return -1;
    }

    if (no->esq == NULL && no->dir == NULL)
    {
        return 0;
    }

    int hEsq = 0;
    int hDir = 0;

    if (no->esq != NULL)
    {
        hEsq = alturaNo(no->esq);
    }
    if (no->dir != NULL)
    {
        hDir = alturaNo(no->dir);
    }

    return hEsq > hDir ? hEsq + 1 : hDir + 1;
}

int fatorBalanceamento(No *no)
{
    return alturaNo(no->esq) - alturaNo(no->dir);
}

void LL(Arv *arv, No *no)
{
    printf("LL(%s)\n", no->palavra);
    No *aux = no->dir;

    if (no == arv->raiz)
    {
        arv->raiz = no->dir;
    } else
    {
        if (no->pai->esq == no) no->pai->esq = aux;
        else if (no->pai->dir == no) no->pai->dir = aux;
    }
    aux->pai = no->pai;
    no->pai = aux;
    if (aux->esq != NULL)
    {
        aux->esq->pai = no;
    }
    no->dir = aux->esq;
    aux->esq = no;

    no->fator_balanceamento = fatorBalanceamento(no);
    aux->fator_balanceamento = fatorBalanceamento(aux);
}

void RR(Arv *arv, No *no)
{
    printf("RR(%s)\n", no->palavra);
    No *aux = no->esq;
    if (no == arv->raiz)
    {
        arv->raiz = no->esq;
    } else
    {
        if (no->pai->esq == no) no->pai->esq = aux;
        else if (no->pai->dir == no) no->pai->dir = aux;
    }
    aux->pai = no->pai;
    no->pai = aux;
    if (aux->dir != NULL)
    {
        aux->dir->pai = no;
    }
    no->esq = aux->dir;
    aux->dir = no;

    no->fator_balanceamento = fatorBalanceamento(no);
    aux->fator_balanceamento = fatorBalanceamento(aux);
}

void balanceamento(Arv *arv, No *no)
{
    if (no->fator_balanceamento == 2)
    {
        if (no->esq != NULL && no->esq->fator_balanceamento == -1)
        {
            LL(arv, no->esq);
        }
        RR(arv, no);
    } else if (no->fator_balanceamento == -2)
    {
        if (no->dir != NULL && no->dir->fator_balanceamento == 1)
        {
            RR(arv, no->dir);
        }
        LL(arv, no);
    }
}

void insereNo(Arv *arv, char *palavra, char *significado)
{
    No *novo = alocaNo();
    novo->palavra = strdup(palavra);
    novo->significado = strdup(significado);
    novo->fator_balanceamento = 0;

    No *y = NULL;
    No *x = arv->raiz;
    while (x != NULL)
    {
        y = x;
        if (compara_strings(palavra, x->palavra) == -1)
        {
            x = x->esq;
        } else
        {
            x = x->dir;
        }
    }

    novo->pai = y;
    if (y == NULL)
    {
        arv->raiz = novo;
    } else if (compara_strings(palavra, y->palavra) == -1)
    {
        y->esq = novo;
    } else
    {
        y->dir = novo;
    }

    while (y != NULL)
    {
        y->fator_balanceamento = fatorBalanceamento(y);
        balanceamento(arv, y);
        y = y->pai;
    }
    printf("Inserção de %s com sucesso.\n", palavra);
}

void percursoEmOrdem(No *no)
{
    if (no == NULL)
    {
        return;
    }
    percursoEmOrdem(no->esq);
    printf("%s  h=%d\n", no->palavra, alturaNo(no));
    percursoEmOrdem(no->dir);
}

No *buscaNo(Arv *arv, char *palavra)
{
    No *aux = arv->raiz;

    while (aux != NULL)
    {
        if (compara_strings(palavra, aux->palavra) == 0)
        {
            return aux;
        } else if (compara_strings(palavra, aux->palavra) < 0)
        {
            aux = aux->esq;
        } else if (compara_strings(palavra, aux->palavra) > 0)
        {
            aux = aux->dir;
        }
    }

    if (aux == NULL)
    {
        printf("%s nao encontrado\n", palavra);
        return aux;
    }
}

No *sucessor(No *no)
{
    No *aux = no->dir;

    while (aux->esq != NULL)
    {
        aux = aux->esq;
    }

    return aux;
}

void removeNo(Arv *arv, char *palavra)
{
    No *aux = buscaNo(arv, palavra);
    if (aux == NULL)
    {
        printf("Operação de remocão da palavra %s inválida\n", palavra);
        return;
    }

    printf("Removendo palavra: %s\n", palavra);

    if (aux->esq == NULL && aux->dir == NULL)
    {
        if (aux == arv->raiz)
        {
            arv->raiz = NULL;
        }
        if (aux == aux->pai->esq)
        {
            aux->pai->esq = NULL;
        } else
        {
            aux->pai->dir = NULL;
        }
    } else if (aux->esq != NULL && aux->dir != NULL)
    {
        No *suc = sucessor(aux);
        aux->palavra = suc->palavra;
        aux->significado = suc->significado;

        if (suc->dir != NULL)
        {
            suc->dir->pai = suc->pai;
            suc->pai->esq = suc->dir;
        } else if (suc->pai->esq == suc)
        {
            suc->pai->esq = NULL;
        } else
        {
            suc->pai->dir = NULL;
        }
    } else
    {
        No *filho = (aux->esq != NULL) ? aux->esq : aux->dir;

        if (aux == arv->raiz)
        {
            arv->raiz = filho;
        } else if (aux == aux->pai->esq)
        {
            aux->pai->esq = filho;
        } else
        {
            aux->pai->dir = filho;
        }

        filho->pai = aux->pai;
    }


    No *atual = aux->pai;
    while (atual != NULL)
    {
        atual->fator_balanceamento = fatorBalanceamento(atual);
        balanceamento(arv, atual);
        atual = atual->pai;
    }


    printf("%s removido com  sucesso\n", palavra);
}

int main()
{
    FILE * timing = fopen("timing.txt", "a");
    clock_t inicio, fim;
    double tempo_de_uso_cpu;
    inicio = clock();
    Arv *arv;
    char *palavra = (char *) malloc(sizeof(char) * MAX_LEN_NAME);
    char *significado = (char *) malloc(sizeof(char) * MAX_LEN);

    printf("+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n");
    printf("|Dicionário                                              |");
    printf("\n|Pressione 1  para inicializar a árvore                |");
    printf("\n|Pressione 2 para remover uma palavra                  |");
    printf("\n|Pressione 3 para inserir uma palavra                  |");
    printf("\n|Pressione 4 para buscar uma palavra                   |");
    printf("\n|Pressione 5 para  imprimir o percurso em ordem        |");
    printf("\n|Digite 6 para sair                                    |");
    printf("\n+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n\n");
    char opcao;
    while (1)
    {
        scanf("%c", &opcao);
        switch (opcao)
        {
            case '1':
                arv = criaArv();
                printf("Árvore criada com sucesso\n");
                break;

            case '2':
                scanf("%s", palavra);
                removeNo(arv, palavra);
                break;

            case '3':
                do
                {
                    fgets(palavra, MAX_LEN_NAME, stdin);
                    remove_newline(palavra);
                } while ((compara_strings(palavra, "") == 0) || (compara_strings(palavra, "\r") == 0));
                fgets(significado, MAX_LEN, stdin);
                remove_newline(significado);
                if (arv == NULL)
                {
                    printf("Inicialize a arvore antes de realizar uma insercao\n");
                } else
                {
                    insereNo(arv, palavra, significado);
                }
                break;

            case '4':
                do
                {
                    fgets(palavra, MAX_LEN_NAME, stdin);
                    remove_newline(palavra);
                } while (compara_strings(palavra, "") == 0);

                No *aux = buscaNo(arv, palavra);
                if (aux == NULL)
                {
                    printf("Busca sem sucesso\n");
                } else
                {
                    printf("%s: %s  h=%d\n", aux->palavra, aux->significado, alturaNo(aux));
                }
                break;

            case '5':
                percursoEmOrdem(arv->raiz);
                break;

            case '6':
                fim = clock();
                tempo_de_uso_cpu = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(timing,"%lf\n", tempo_de_uso_cpu);
                return 0;

            default:
                break;
        }
    }
    return 0;
}