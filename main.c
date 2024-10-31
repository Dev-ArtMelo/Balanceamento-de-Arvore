//Arthur Santos Melo 831540
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    int altura;
    struct No *esquerda;
    struct No *direita;
} No;

No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esquerda = novoNo->direita = NULL;
    novoNo->altura = 1;  
    return novoNo;
}

int altura(No* no) {
    if (no == NULL) return 0;
    return no->altura;
}

int fatorDeBalanceamento(No* no) {
    if (no == NULL) return 0;
    return altura(no->esquerda) - altura(no->direita);
}

No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));

    return y;
}

No* rotacaoDireitaEsquerda(No* raiz) {
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
}

No* rotacaoEsquerdaDireita(No* raiz) {
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
}

No* balancear(No* raiz) {
    int fb = fatorDeBalanceamento(raiz);

    if (fb > 1) { 
        if (fatorDeBalanceamento(raiz->esquerda) >= 0) {
            raiz = rotacaoDireita(raiz);
        } else {
            raiz = rotacaoEsquerdaDireita(raiz);
        }
    } else if (fb < -1) { 
        if (fatorDeBalanceamento(raiz->direita) <= 0) {
            raiz = rotacaoEsquerda(raiz);
        } else {
            raiz = rotacaoDireitaEsquerda(raiz);
        }
    }

    return raiz;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);

    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);
    else
        return raiz; 

    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    return balancear(raiz);
}

void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

int main() {
    No* raiz = NULL;

    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 7);

    printf("Arvore em ordem: ");
    emOrdem(raiz);
    printf("\n");

    return 0;
}
